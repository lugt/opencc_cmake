#include <vector>
#include <string>
#include "jgen_include.h"

// Return Params

using std::cout;
using std::cerr;
using std::endl;

BOOL JGEN_processing_function_prototype = FALSE;
BOOL JGEN_Keep_Zero_Length_Structs = FALSE;

class JGEN_ST {

    static TY_IDX ty_idx;
    static ST *st;
    static char *name;
    static char tempname[32];
    static ST_SCLASS sclass;
    static ST_EXPORT eclass;
    static SYMTAB_IDX level;
    static INT anon_count;
    static void * context;
    static void * node;
    static int flag;


    JGEN_ST() {
        anon_count = 0;
    }

    static void get_ST(void *node_, int kind, int flag_, std::string name, void *parent) {
        node = node_;
        context = parent;
        flag = flag_;
        int a = JGEN_FUNC;
        a = JGEN_METHOD;
        if ((kind == JGEN_FUNC) || (kind == JGEN_METHOD)) {
            create_func(flag_, name, (kind == JGEN_METHOD));
        } else if (kind == JGEN_VAR) {
            createVar(kind, flag_);
        } else if (kind == JGEN_CLASS) {
            // createClass();
        }
    }

    static bool isPublic(int flag) {
        return 0;
    }

    static bool isWeak(int flag) {
        return 0;
    }

    static bool isConstructor(int flag) {
        return 0;
    }

    static bool isPureVFunc(int flag) {
        return 0;
    }

    static bool isMethodOfClass(int flag) {
        return 0;
    }

    static int get_method_base_type(){
        return 0;
    }

    static bool isContextNamespace(void *context) {
        return false;
    }

    static bool isContextRecord(void *context) {
        return false;
    }

    static bool isLangSpecific(){
        return false;
    }

    static bool isReallyExtern(){
        return false;
    }

    static bool isNoThrow(){
        return false;
    }

    static TY_IDX get_related_TY(){
        return 0;
    }

    static void create_func(int flag, std::string funcName, bool isMethod) {

        JGEN_processing_function_prototype = TRUE;
        TY_IDX func_ty_idx = get_related_TY();
        JGEN_processing_function_prototype = FALSE;

        sclass = SCLASS_EXTERN;
        eclass = isPublic(flag) || isWeak(flag) ?
                 EXPORT_PREEMPTIBLE :
                 EXPORT_LOCAL;

        level = GLOBAL_SYMTAB + 1;
        PU_IDX pu_idx;
        PU &pu = New_PU(pu_idx);
        PU_Init(pu, func_ty_idx, level);

        st = New_ST(level - 1);
        ST_Init(st, Save_Str(funcName.c_str()),
                CLASS_FUNC, sclass, eclass, TY_IDX(pu_idx));

        if (isConstructor(flag)) {
            Set_PU_is_constructor(pu);
        }

        if (isPureVFunc(flag)) {
            Set_ST_is_pure_vfunc(st);
        }

        if (isMethodOfClass(flag)) {
            TY_IDX base = get_method_base_type();
            Set_PU_base_class(pu, base);
        }

        if (isContextNamespace(context) &&
            eclass != EXPORT_LOCAL &&
            eclass != EXPORT_LOCAL_INTERNAL) {
            Set_ST_is_weak_symbol(st);
        }

        if (isMethod) {
            TY_IDX base = get_method_base_type();
            Set_PU_base_class(pu, base);
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

        if (isNoThrow()) {
            Set_PU_nothrow(pu);
        }
    }

    static void createParam() {
        if (isExternal()) {
            sclass = SCLASS_EXTERN;
        } else if (isInitial(flag)) {
            sclass = SCLASS_UGLOBAL;
        }
    }

    static void createVar(int kind, int flag) {

        if (kind == JGEN_PARM) {
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
        } else {
            if (context == 0 || isContextNamespace(context) ||
                isContextRecord(context)) {
                if (isPublic(flag)) {

                    if (isExternal() ||
                        (isLangSpecific() &&
                         isReallyExtern()))
                        sclass = SCLASS_EXTERN;
                    else if (isInitial(flag))
                        sclass = SCLASS_UGLOBAL;
                    else if (isStatic()) {
                        if (flag_no_common || !isCommon() ||
                            (!lang_cplus && hasName(flag)))
                            sclass = SCLASS_UGLOBAL;
                        else
                            sclass = SCLASS_COMMON;
                    } else
                        sclass = SCLASS_EXTERN;
                    eclass = EXPORT_PREEMPTIBLE;
                } else {
                    sclass = SCLASS_FSTATIC;
                    eclass = EXPORT_LOCAL;
                }
                level = GLOBAL_SYMTAB;
            } else {
                // .gnu.linkonce.b is .bss with DECL_ONE_ONLY set.  Bug 10876.
                std::string section_name = ".gnu";
                if (section_name.size() > 0 &&
                    !startsWith(".gnu.linkonce.")) {
                    if (!startsWith(".gnu.linkonce.b.")
                        // bug 13054
                        || ! startsWith(".gnu.linkonce.sb.")) {
                        sclass = SCLASS_UGLOBAL;
                        level = GLOBAL_SYMTAB;
                        eclass = EXPORT_PREEMPTIBLE;
                    } else {
                        // Add support as needed.
                        Fail_FmtAssertion("Create_ST_For_Tree: %s section NYI", section_name.c_str());
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
                else if (isExternal () || isWeak(flag)) {
                    // OSP_255
                    // Not all weak symbols are EXTERN: COMMON&WEAK, STATIC&WEAK
                    if (!flag_no_common && isCommon()) {
                        // COMMON & WEAK:
                        //   static vars in exported inline/template functions(IA64)
                        sclass = SCLASS_COMMON;
                    } else if (isStatic()) {
                        // STATIC & WEAK:
                        //   static vars in exported inline/template function(X8664)
                        sclass = SCLASS_UGLOBAL;
                    } else {
                        // OTHERS:
                        //   treat it EXTERN ( will not allocate space )
                        sclass = SCLASS_EXTERN;
                    }
                    level = GLOBAL_SYMTAB;
                    eclass = EXPORT_PREEMPTIBLE;
                }
                    // Bug 8652: If GNU marks it as COMMON, we should the same.
                else if (!flag_no_common && isStatic() && isCommon() && isPublic(flag)) {
                    sclass = SCLASS_COMMON;
                    level = GLOBAL_SYMTAB;
                    eclass = EXPORT_PREEMPTIBLE;
                }
                else {
                    if (isStatic()) {
                        sclass = SCLASS_PSTATIC;
                        if (pstatic_as_global
                            && !(isInitial(flag) &&
                                 !isExternal() && isInitial(flag)))
                            level = GLOBAL_SYMTAB;
                        else
                            level = CURRENT_SYMTAB;
                    } else {
                        sclass = SCLASS_AUTO;
                        level = getCurrentSymtab() ? getCurrentSymtab() : CURRENT_SYMTAB;
                    }
                    eclass = EXPORT_LOCAL;
                }
            }
        }
        if (is_guard_var()) {
            // This is a guard variable created by the g++ front-end to protect
            // against multiple initializations (and destruction) of symbols
            // with static storage class. Make it local unless it's weak.
            level = GLOBAL_SYMTAB;
            if (isWeak(flag)) {
                sclass = SCLASS_UGLOBAL;
                eclass = EXPORT_PREEMPTIBLE;
            } else {
                sclass = SCLASS_PSTATIC;
                eclass = EXPORT_LOCAL;
            }
        } else if (gv_cond_expr) {
            //Make guard variable for condtional expressions a local stack
            //variable to avoid being over-written when evaluating nested
            //conditional expressions.
            //See comments for WGEN_add_guard_var in wgen_expr.cxx
            //for information on conditional expressions.
            level = getCurrentSymtab() ?
                    getCurrentSymtab() : CURRENT_SYMTAB;
            sclass = SCLASS_AUTO;
            eclass = EXPORT_LOCAL;
        }

        sclass = SCLASS_FORMAL;
        eclass = EXPORT_LOCAL;
        level = CURRENT_SYMTAB;
        st = New_ST(level);

        ty_idx = get_related_TY();

        // Set line number where define sym in source file
        //if (isO)
        //   Set_ST_Line(*st, gs_decl_source_line(decl_node));
        //else  TODO: Set Line Number
        Set_ST_Line(*st, getLineNumber());

        ST_Init(st, Save_Str(name), CLASS_VAR, sclass, eclass, ty_idx);

        Set_ST_is_thread_private(st);

        if (kind == JGEN_VAR && sclass == SCLASS_AUTO)
            JGEN_add_pragma_to_location(WN_PRAGMA_LOCAL, st);

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

        if (kind == JGEN_PARM) {
            Set_ST_is_value_parm(st);
        }
    }

    static void JGEN_add_pragma_to_location(WN_PRAGMA_ID id, ST * st){

    }

    static int getCurrentSymtab(){
        return 0;
    }

    static bool isInitial(int flag){
        return true;
    }

    static bool isCommon(){
        return true;
    }

    static bool isExternal(){
        return true;
    }

    static bool isStatic(){
        return true;
    }

    static void createRetVal() {

    }

    static bool hasName(int flag){
        return true;
    }

    static bool is_guard_var(){
        return false;
    }

    static bool startsWith(const char * starter){

    }

    static void createNameSpace() {
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

    static int getLineNumber(){
        return 1;
    }
};


class JGEN_TY {
public:
    static std::string type_str;
    static long long kind;
    static long long flag;
    static TY_IDX idx;
    static TYPE_ID mtype;
    static INT64 tsize;
    static BOOL variable_size;
    static std::string kname;
    static JGEN_TY return_val;
    static vector<JGEN_TY> args;


    static void createFunction() {

        TY &ty = (idx == TY_IDX_ZERO) ? New_TY(idx) : Ty_Table[idx];
        Clear_TY_is_incomplete(idx);
        TY_Init(ty, 0, KIND_FUNCTION, MTYPE_UNKNOWN, 0);
        Set_TY_align(idx, 1);
        TY_IDX ret_ty_idx;
        TY_IDX arg_ty_idx;
        TYLIST tylist_idx;

        // allocate TYs for return as well as parameters
        // this is needed to avoid mixing TYLISTs if one
        // of the parameters is a pointer to a function

        ret_ty_idx = return_val.idx;


        for (auto it = args.begin();
             it != args.end();
             it++) {
            arg_ty_idx = it->idx;
            if (TY_is_incomplete(arg_ty_idx) ||
                (TY_kind(arg_ty_idx) == KIND_POINTER &&
                 TY_is_incomplete(TY_pointed(arg_ty_idx))))
                Set_TY_is_incomplete(idx);
        }

        // if return type is pointer to a zero length struct
        // convert it to void
        if (!JGEN_Keep_Zero_Length_Structs &&
            TY_mtype(ret_ty_idx) == MTYPE_M &&
            TY_size(ret_ty_idx) == 0) {
            // zero length struct being returned
            DevWarn("function returning zero length struct at line %d", lineno);
            ret_ty_idx = Be_Type_Tbl (MTYPE_V);
        }

        // If the front-end adds the fake first param, then convert the
        // function to return void.
        if (TY_return_in_mem(ret_ty_idx)) {
            ret_ty_idx = Be_Type_Tbl (MTYPE_V);
            Set_TY_return_to_param(idx);        // bugs 2423 2424
        }
        Set_TYLIST_type(New_TYLIST(tylist_idx), ret_ty_idx);
        Set_TY_tylist(ty, tylist_idx);
        for (auto it = args.begin();
             it != args.end();
             it++) {
            arg_ty_idx = it->idx;
                    Is_True (!TY_is_incomplete(arg_ty_idx) ||
                             TY_is_incomplete(idx),
                             ("Create_TY_For_Tree: unexpected TY flag"));
            if (!JGEN_Keep_Zero_Length_Structs &&
                TY_mtype(arg_ty_idx) == MTYPE_M &&
                TY_size(arg_ty_idx) == 0) {
                // zero length struct passed as parameter
                DevWarn("zero length struct encountered in function prototype at line %d", lineno);
            } else
                Set_TYLIST_type(New_TYLIST(tylist_idx), arg_ty_idx);
        }
        if (get_num_args()) {
            Set_TY_has_prototype(idx);
            if (arg_ty_idx != Be_Type_Tbl(MTYPE_V)) {
                Set_TYLIST_type(New_TYLIST(tylist_idx), 0);
                Set_TY_is_varargs(idx);
            } else
                Set_TYLIST_type(Tylist_Table[tylist_idx], 0);
        } else
            Set_TYLIST_type(New_TYLIST(tylist_idx), 0);

        // TODO: TARGET X8664 SSE Specification Ignored
    }


    static void get_TY(long long _kind, std::string kindName, long long flag) {
        tsize = 0; /// Variable Length Array check? Variable Length Structure Check?
        mtype = 0;
        variable_size = FALSE;
        kname = kindName;
        kind = _kind;
        idx = 0;
        _getTY(_kind, flag);
    }

    static void _getTY(long long TY_KIND, long long flag) {

        cout << " -- Getting TY for " << kname;
        switch (TY_KIND) {
            case JGEN_TYPE_VOID: {
                idx = MTYPE_To_TY (MTYPE_V);
                break;
            }
            case JGEN_TYPE_BOOLEAN:
            case JGEN_TYPE_INTEGER:
            case JGEN_TYPE_OFFSET: {
                create_integer();
                break;
            }
            case JGEN_TYPE_ENUMERATION:
                create_enumeration();
                break;
            case JGEN_TYPE_CHAR:
            case JGEN_TYPE_BYTE: {
                create_char();
                break;
            }
            case JGEN_TYPE_FLOAT:
            case JGEN_TYPE_DOUBLE:
            case JGEN_TYPE_NUMBER: {
                create_floating();
                break;
            }
            case JGEN_TYPE_HANDLE:
            case JGEN_TYPE_POINTER: {
                idx = Be_Type_Tbl(Pointer_Size == 8 ? MTYPE_I8 : MTYPE_I4);
                break;
            }
            case JGEN_TYPE_ARRAY: {
                createArray();
                break;
            }
            case JGEN_TYPE_RECORD:
            case JGEN_TYPE_UNION:
                /** TOOD RECORD, UNION **/
                cerr << "Unfinished Type : Union";
                break;
            case JGEN_TYPE_METHOD:
            case JGEN_TYPE_FUNCTION:
                createFunction();
                break;
            default:
                cerr << "Unexpected Type KIND : " << kind;

        }
        if (isConst())
            Set_TY_is_const(idx);
        if (isVolatile())
            Set_TY_is_volatile(idx);
        if (isRestrict())
            Set_TY_is_restrict(idx);

    }

    static void create_char(){
        mtype = (isUnsigned(flag) ? MTYPE_U1 : MTYPE_I1);
        idx = MTYPE_To_TY (mtype);    // use predefined type
    }

    static void create_floating(){
        switch (tsize) {
            case 4:
                mtype = MTYPE_F4;
                break;
            case 8:
                mtype = MTYPE_F8;
                break;
        }
        idx = MTYPE_To_TY (mtype);
    }

    static void create_enumeration(){
        switch (tsize) {
            case 1: // bug 14445
                mtype = (isUnsigned(flag) ? MTYPE_U1 :
                         MTYPE_I1);
                break;
            case 2: // bug 14445
                mtype = (isUnsigned(flag) ? MTYPE_U2 :
                         MTYPE_I2);
                break;
            case 8: // bug 500
                mtype = (isUnsigned(flag) ? MTYPE_U8 :
                         MTYPE_I8);
                break;
            default:
                mtype = (isUnsigned(flag) ? MTYPE_U4 :
                         MTYPE_I4);
        }
        idx = MTYPE_To_TY (mtype);
    }

    static void create_integer(){
        switch (tsize) {
            case 1:
                mtype = MTYPE_I1;
                break;
            case 2:
                mtype = MTYPE_I2;
                break;
            case 4:
                mtype = MTYPE_I4;
                break;
            case 8:
                mtype = MTYPE_I8;
                break;
        }
        if (isUnsigned(flag)) {
            mtype = MTYPE_complement(mtype);
        }
        idx = MTYPE_To_TY (mtype);
        if (TARGET_64BIT) {

        // TODO:Change back to align
            Set_TY_align(idx, 1);
            //    Set_TY_align(idx, align);
        }
    }

    static void createArray() {

        TY &ty = (idx == TY_IDX_ZERO) ? New_TY(idx) : Ty_Table[idx];
        Clear_TY_is_incomplete(idx);
        TY_Init(ty, tsize, KIND_ARRAY, MTYPE_M,
                Save_Str(type_str.c_str()));

        // for the anonymoust array
        if (type_str == "NULL")
            Set_TY_anonymous(ty);

        Set_TY_etype(ty, get_element_type());
        Set_TY_align(idx, TY_align(TY_etype(ty)));

        // For GNU VLS (Variable length array in struct),
        // the size and upper boundary is expression.
        // If the TYPE_TY_IDX(type_tree) is not set, when
        // expanding the TY's size, it will fall into a infinite
        // recursion if the type_tree is referenced in the
        // size expression. So we set the TYPE_TY_IDX here.
        if (isReadonly())
            Set_TY_is_const(idx);
        if (isVolatile())
            Set_TY_is_volatile(idx);
        if (isRestrict())
            Set_TY_is_restrict(idx);

        // assumes 1 dimension
        // nested arrays are treated as arrays of arrays
        ARB_HANDLE arb = New_ARB();
        ARB_Init(arb, 0, 0, 0);
        Set_TY_arb(ty, arb);
        Set_ARB_first_dimen(arb);
        Set_ARB_last_dimen(arb);
        Set_ARB_dimension(arb, 1);


        if (get_type_size(get_element_type()) == 0)
            return; // anomaly:  type will never be needed

        // =================== Array stride ======================
        if (!isVariableSize()) {
            Set_ARB_const_stride(arb);
            Set_ARB_stride_val(arb,get_element_size_unit()/*gs_get_integer_value(gs_type_size_unit(gs_tree_type(type_tree)))*/);
        } else if (!JGEN_expanding_function_definition &&
                   JGEN_processing_function_prototype) {
            Set_ARB_const_stride(arb);
            // dummy stride val 4
            Set_ARB_stride_val(arb, 4);
            Set_TY_is_incomplete(idx);
        } else {
            /* TODO:Make this available
            WN *swn;
            swn = WGEN_Expand_Expr(gs_type_size_unit(gs_tree_type(type_tree)));
            if (WN_opcode(swn) == OPC_U4I4CVT ||
                WN_opcode(swn) == OPC_U8I8CVT) {
                swn = WN_kid0(swn);
            }
            // In the event that swn operator is not
            // OPR_LDID, save expr node swn
            // and use LDID of that stored address as swn.
            // Copied from Wfe_Save_Expr in wfe_expr.cxx
            if (WN_operator(swn) != OPR_LDID) {
                TYPE_ID mtype = WN_rtype(swn);
                TY_IDX ty_idx = MTYPE_To_TY(mtype);
                ST *st;
                st = Gen_Temp_Symbol(ty_idx, "__save_expr");
                WGEN_add_pragma_to_enclosing_regions(WN_PRAGMA_LOCAL, st);
                WGEN_Set_ST_Addr_Saved(swn);
                swn = WN_Stid(mtype, 0, st, ty_idx, swn);
                WGEN_Stmt_Append(swn, Get_Srcpos());
                swn = WN_Ldid(mtype, 0, st, ty_idx);
            }
            FmtAssert (WN_operator(swn) == OPR_LDID,
                       ("stride operator for VLA not LDID"));
            ST *st = WN_st(swn);
            TY_IDX ty_idx = ST_type(st);
            WN *wn = WN_CreateXpragma (WN_PRAGMA_COPYIN_BOUND,
                                       (ST_IDX) NULL, 1);
            WN_kid0(wn) = WN_Ldid(TY_mtype(ty_idx), 0, st, ty_idx);
            WGEN_Stmt_Append(wn, Get_Srcpos());
            Clear_ARB_const_stride(arb);
            Set_ARB_stride_var(arb, (ST_IDX) ST_st_idx(st));
            Clear_TY_is_incomplete(idx);*/
        }

        // ================= Array lower bound =================
        Set_ARB_const_lbnd(arb);
        Set_ARB_lbnd_val(arb, 0);

        // ================= Array upper bound =================
        if (get_type_size(get_element_type()) != 0) {
            // For Zero-length arrays, TYPE_MAX_VALUE tree is NULL
            if (!isZeroMaxValue(get_element_type())) {
                Set_ARB_const_ubnd(arb);
                Set_ARB_ubnd_val(arb, 0xffffffff);
            } else if (isSizeMaxValueConstant()) {
                Set_ARB_const_ubnd(arb);
                Set_ARB_ubnd_val(arb, get_max_value(get_element_type()));
            } else if (!JGEN_expanding_function_definition &&
                       JGEN_processing_function_prototype) {
                Set_ARB_const_ubnd(arb);
                // dummy upper bound 8
                Set_ARB_ubnd_val(arb, 8);
                Set_TY_is_incomplete(idx);
            } else {
                // Get WN <- Expr
                /* TODO:Make this available
                WN *uwn = WGEN_Expand_Expr();
                if (WN_opcode(uwn) == OPC_U4I4CVT ||
                    WN_opcode(uwn) == OPC_U8I8CVT) {
                    uwn = WN_kid0(uwn);
                }
                ST *st;
                TY_IDX ty_idx;
                WN *wn;
                if (WN_operator(uwn) != OPR_LDID) {
                    ty_idx = MTYPE_To_TY(WN_rtype(uwn));
                    st = Gen_Temp_Symbol(ty_idx, "__vla_bound");
                    WGEN_add_pragma_to_enclosing_regions(WN_PRAGMA_LOCAL, st);
                    wn = WN_Stid(TY_mtype(ty_idx), 0, st, ty_idx, uwn);
                    WGEN_Stmt_Append(wn, Get_Srcpos());
                } else {
                    st = WN_st(uwn);
                    ty_idx = ST_type(st);
                }

                wn = WN_CreateXpragma (WN_PRAGMA_COPYIN_BOUND, (ST_IDX) NULL, 1);
                // Create An Ldid for the array bound to check for sizes.
                WN_kid0(wn) = WN_Ldid(TY_mtype(ty_idx), 0, st, ty_idx);
                WGEN_Stmt_Append(wn, Get_Srcpos());

                Clear_ARB_const_ubnd(arb);
                Set_ARB_ubnd_var(arb, ST_st_idx(st));
                Clear_TY_is_incomplete(idx);*/
            }
        } else { /* situation : type size == 0 */
            Clear_ARB_const_ubnd(arb);
            Set_ARB_ubnd_val(arb, 0);
        }

        /** TODO Array **/
        cerr << "Unfinished Type : Array";
    }

    static bool isZeroMaxValue(TY_IDX ty){
        return false;
    }

    static bool isSizeMaxValueConstant(){
        return true;
    }

    static bool isVariableSize(){
        return false;
    }

    static int get_type_size(TY_IDX type){
        return 0;
    }

    static int get_num_args(){
        return 0;
    }

    static bool isUnsigned(long long flag){
        return true;
    }

    static int get_element_type(){
        return 0;
    }

    static bool isConst(){
        return 0;
    }

    static int get_element_size_unit(){
        return 0;
    }

    static long get_max_value(TY_IDX ty){
        return 1;
    }

    static bool isReadonly(){
        return false;
    }
    static bool isVolatile(){
        return false;
    }
    static bool isRestrict(){
        return false;
    }
};
