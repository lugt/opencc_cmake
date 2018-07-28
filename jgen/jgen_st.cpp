//
// Created by xc5 on 27/7/2018.
//

#include <string>
#include "jgen_st.h"

namespace JGEN
{

    BOOL JGEN_processing_function_prototypes = FALSE;
    BOOL JGEN_Keep_Zero_Length_Structs = FALSE;

    TY_IDX JGEN_ST::ty_idx;
    ST *JGEN_ST::st;
    char *JGEN_ST::name;
    char JGEN_ST::tempname[32];
    ST_SCLASS JGEN_ST::sclass;
    ST_EXPORT JGEN_ST::eclass;
    SYMTAB_IDX JGEN_ST::level;
    INT JGEN_ST::anon_count;
    void *JGEN_ST::context;
    void *JGEN_ST::node;
    int JGEN_ST::flag;

    void JGEN_ST::get_ST (void *node_, int kind, int flag_, std::string name, void *parent)
    {
      node = node_;
      context = parent;
      flag = flag_;
      int a = JGEN_FUNC;
      a = JGEN_METHOD;
      if ((kind == JGEN_FUNC) || (kind == JGEN_METHOD))
        {
          create_func (flag_, name, (kind == JGEN_METHOD));
        }
      else if (kind == JGEN_VAR)
        {
          createVar (kind, flag_);
        }
      else if (kind == JGEN_CLASS)
        {
          createClass ();
        }
    }

    void JGEN_ST::create_func (int flag, std::string funcName, bool isMethod)
    {

      JGEN_processing_function_prototypes = TRUE;
      TY_IDX func_ty_idx = get_related_TY ();
      JGEN_processing_function_prototypes = FALSE;

      sclass = SCLASS_EXTERN;
      eclass = isPublic (flag) || isWeak (flag) ?
               EXPORT_PREEMPTIBLE :
               EXPORT_LOCAL;

      level = GLOBAL_SYMTAB + 1;
      PU_IDX pu_idx;
      PU &pu = New_PU (pu_idx);
      PU_Init (pu, func_ty_idx, level);

      st = New_ST (level - 1);
      ST_Init (st, Save_Str (funcName.c_str ()),
               CLASS_FUNC, sclass, eclass, TY_IDX (pu_idx));

      if (isConstructor (flag))
        {
          Set_PU_is_constructor (pu);
        }

      if (isPureVFunc (flag))
        {
          Set_ST_is_pure_vfunc (st);
        }

      if (isMethodOfClass (flag))
        {
          TY_IDX base = get_method_base_type ();
          Set_PU_base_class (pu, base);
        }

      if (isContextNamespace (context) &&
          eclass != EXPORT_LOCAL &&
          eclass != EXPORT_LOCAL_INTERNAL)
        {
          Set_ST_is_weak_symbol (st);
        }

      if (isMethod)
        {
          TY_IDX base = get_method_base_type ();
          Set_PU_base_class (pu, base);
        }

      // process attributes for FUNCTION_DECL  TODO: Function
      /**
       * gs_t attr_list = gs_decl_attributes(decl_node);
      for ( ; attr_list != NULL; attr_list = gs_tree_chain(attr_list) ) {
                  Is_True(gs_tree_code(attr_list) == GS_TREE_LIST,
                          ("lookup_attributes: TREE_LIST node not found"));
          gs_t attr = gs_tree_purpose(attr_list);
          if ( is_attribute("noreturn", attr) ) // __attribute__((noreturn))
              Set_PU_has_attr_noreturn (pu);
      }
       */

      if (isNoThrow ())
        {
          Set_PU_nothrow (pu);
        }
    }
    void JGEN_ST::createParam ()
    {
      if (isExternal ())
        {
          sclass = SCLASS_EXTERN;
        }
      else if (isInitial (flag))
        {
          sclass = SCLASS_UGLOBAL;
        }
    }
    void JGEN_ST::createVar (int kind, int flag)
    {

      if (kind == JGEN_PARM)
        {
          // wgen fix for C++ and also for C, as in bug 8346.
          /*if (decl_arguments) {
              st = Search_decl_arguments(gs_decl_name(decl_node) ? name : NULL);
              if (st) {
                  set_DECL_ST(decl_node, st); // created now
                  return st;
              }
          }
          */
          sclass = SCLASS_FORMAL;
          eclass = EXPORT_LOCAL;
          level = CURRENT_SYMTAB;
        }
      else
        {
          if (context == 0 || isContextNamespace (context) ||
              isContextRecord (context))
            {
              if (isPublic (flag))
                {

                  if (isExternal () ||
                      (isLangSpecific () &&
                       isReallyExtern ()))
                    sclass = SCLASS_EXTERN;
                  else if (isInitial (flag))
                    sclass = SCLASS_UGLOBAL;
                  else if (isStatic ())
                    {
                      if (flag_no_common || !isCommon () ||
                          (!lang_cplus && hasName (flag)))
                        sclass = SCLASS_UGLOBAL;
                      else
                        sclass = SCLASS_COMMON;
                    }
                  else
                    sclass = SCLASS_EXTERN;
                  eclass = EXPORT_PREEMPTIBLE;
                }
              else
                {
                  sclass = SCLASS_FSTATIC;
                  eclass = EXPORT_LOCAL;
                }
              level = GLOBAL_SYMTAB;
            }
          else
            {
              // .gnu.linkonce.b is .bss with DECL_ONE_ONLY set.  Bug 10876.
              std::string section_name = ".gnu";
              if (section_name.size () > 0 &&
                  !startsWith (".gnu.linkonce."))
                {
                  if (!startsWith (".gnu.linkonce.b.")
                      // bug 13054
                      || !startsWith (".gnu.linkonce.sb."))
                    {
                      sclass = SCLASS_UGLOBAL;
                      level = GLOBAL_SYMTAB;
                      eclass = EXPORT_PREEMPTIBLE;
                    }
                  else
                    {
                      // Add support as needed.
                      Fail_FmtAssertion ("Create_ST_For_Tree: %s section NYI", section_name.c_str ());
                    }
                }
                /*    // bug 13090 and 13245
                    // Bug 13047 shows that the gnu42 front-end (specifically
                    // the gcc/g++ part) behaves differently when built on a gnu3
                    // system, than when built on a gnu4 system. If the compiler
                    // is built on a gnu4 system, default_unique_section() in
                    // varasm.c will never generate a linkonce section because
                    // starting GNU42, this also depends on whether the host
                    // compiling system has COMDAT groups.
                else if (section_name &&
                         (!strncmp(gs_tree_string_pointer(section_name),
                                   ".sbss.", 6) ||
                          !strncmp(gs_tree_string_pointer(section_name),
                                   ".bss.", 5))) {
                    sclass = SCLASS_UGLOBAL;
                    level = GLOBAL_SYMTAB;
                    eclass = EXPORT_PREEMPTIBLE;
                }*/
              else if (isExternal () || isWeak (flag))
                {
                  // OSP_255
                  // Not all weak symbols are EXTERN: COMMON&WEAK, STATIC&WEAK
                  if (!flag_no_common && isCommon ())
                    {
                      // COMMON & WEAK:
                      //   static vars in exported inline/template functions(IA64)
                      sclass = SCLASS_COMMON;
                    }
                  else if (isStatic ())
                    {
                      // STATIC & WEAK:
                      //   static vars in exported inline/template function(X8664)
                      sclass = SCLASS_UGLOBAL;
                    }
                  else
                    {
                      // OTHERS:
                      //   treat it EXTERN ( will not allocate space )
                      sclass = SCLASS_EXTERN;
                    }
                  level = GLOBAL_SYMTAB;
                  eclass = EXPORT_PREEMPTIBLE;
                }
                // Bug 8652: If GNU marks it as COMMON, we should the same.
              else if (!flag_no_common && isStatic () && isCommon () && isPublic (flag))
                {
                  sclass = SCLASS_COMMON;
                  level = GLOBAL_SYMTAB;
                  eclass = EXPORT_PREEMPTIBLE;
                }
              else
                {
                  if (isStatic ())
                    {
                      sclass = SCLASS_PSTATIC;
                      if (pstatic_as_global
                          && !(isInitial (flag) &&
                               !isExternal () && isInitial (flag)))
                        level = GLOBAL_SYMTAB;
                      else
                        level = CURRENT_SYMTAB;
                    }
                  else
                    {
                      sclass = SCLASS_AUTO;
                      level = getCurrentSymtab () ? getCurrentSymtab () : CURRENT_SYMTAB;
                    }
                  eclass = EXPORT_LOCAL;
                }
            }
        }
      if (is_guard_var ())
        {
          // This is a guard variable created by the g++ front-end to protect
          // against multiple initializations (and destruction) of symbols
          // with static storage class. Make it local unless it's weak.
          level = GLOBAL_SYMTAB;
          if (isWeak (flag))
            {
              sclass = SCLASS_UGLOBAL;
              eclass = EXPORT_PREEMPTIBLE;
            }
          else
            {
              sclass = SCLASS_PSTATIC;
              eclass = EXPORT_LOCAL;
            }
        }
      else if (TRUE /* gv_cond_expr */) //TODO : Missing Statement
        {
          //Make guard variable for condtional expressions a local stack
          //variable to avoid being over-written when evaluating nested
          //conditional expressions.
          //See comments for WGEN_add_guard_var in wgen_expr.cxx
          //for information on conditional expressions.
          level = getCurrentSymtab () ?
                  getCurrentSymtab () : CURRENT_SYMTAB;
          sclass = SCLASS_AUTO;
          eclass = EXPORT_LOCAL;
        }

      sclass = SCLASS_FORMAL;
      eclass = EXPORT_LOCAL;
      level = CURRENT_SYMTAB;
      st = New_ST (level);

      ty_idx = get_related_TY ();

      // Set line number where define sym in source file
      //if (isO)
      //   Set_ST_Line(*st, gs_decl_source_line(decl_node));
      //else  TODO: Set Line Number
      Set_ST_Line (*st, getLineNumber ());

      ST_Init (st, Save_Str (name), CLASS_VAR, sclass, eclass, ty_idx);

      Set_ST_is_thread_private (st);

      if (kind == JGEN_VAR && sclass == SCLASS_AUTO)
        JGEN_add_pragma_to_location (WN_PRAGMA_LOCAL, st);

      /*
       * Variable Length Stuff
       *
      if (gs_decl_size_unit (decl_node) &&
          gs_tree_code (gs_decl_size_unit (decl_node)) != GS_INTEGER_CST)
      {
          // if this is the first alloca, save sp.
          int idx;
          if (!Set_Current_Scope_Has_Alloca (idx))
          {
              ST * save_st = WGEN_Alloca_0 ();
              Set_Current_Scope_Alloca_St (save_st, idx);
          }
          WN * size = WGEN_Expand_Expr (gs_decl_size_unit (decl_node));
          // mimic WGEN_Alloca_ST
          ST * alloca_st = New_ST (CURRENT_SYMTAB);
          ST_Init (alloca_st, Save_Str (name),
                   CLASS_VAR, SCLASS_AUTO, EXPORT_LOCAL,
                   Make_Pointer_Type (ty_idx, FALSE));
          Set_ST_is_temp_var (alloca_st);
          Set_ST_pt_to_unique_mem (alloca_st);
          Set_ST_base_idx (st, ST_st_idx (alloca_st));
          WN *wn  = WN_CreateAlloca (size);
          wn = WN_Stid (Pointer_Mtype, 0, alloca_st, ST_type (alloca_st), wn);
          WGEN_Stmt_Append (wn, Get_Srcpos());
          Set_PU_has_alloca (Get_Current_PU());
          // For kids 1..n of DEALLOCA
          Add_Current_Scope_Alloca_St (alloca_st, idx);
      }*/

      if (kind == JGEN_PARM)
        {
          Set_ST_is_value_parm (st);
        }
    }
    void JGEN_ST::createNameSpace ()
    {
      /* - local -->.      sclass = SCLASS_FSTATIC;
      - 		eclass = EXPORT_LOCAL;
      - initial --> global
      - static --> uglobal, common
      - else ---> SCLASS_EXTERN , EXPORT_PREEMPTIBLE*/
      // link once ?
      sclass = SCLASS_UGLOBAL;
      level = GLOBAL_SYMTAB;
      eclass = EXPORT_PREEMPTIBLE;
    }
    void JGEN_ST::createClass ()
    {
      sclass = SCLASS_UGLOBAL;
      level = GLOBAL_SYMTAB;
      eclass = EXPORT_PREEMPTIBLE;
      st = New_ST (level);
      ty_idx = get_related_TY ();
      // Set line number where define sym in source file
      //if (isO)
      //   Set_ST_Line(*st, gs_decl_source_line(decl_node));
      //else  TODO: Set Line Number
      Set_ST_Line (*st, static_cast<mUINT32>(getLineNumber ()));
      ST_Init (st, Save_Str (name), CLASS_VAR, sclass, eclass, ty_idx);

    }

}
