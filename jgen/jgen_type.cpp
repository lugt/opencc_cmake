//
// Created by xc5 on 27/7/2018.
//

#include "jgen_type.h"
#include <string>
#include <map>
using std::string;

namespace JGEN
{

TY_IDX JGEN_TY::getExistTypeIdx(U32U jTypeIndex) {
    if(generatedType.find(jTypeIndex) != generatedType.end()){
        return generatedType.find(jTypeIndex)->second;
    }
    return 0;
}

TY_IDX JGEN_TY::createFunction(U32U typenode) {


  FmtAssert(typetree != nullptr, ("-- [JGEN_TY] Reading from some nullptr (typetree)."));

  vector<U32U> args = typetree->getArgs(typenode);
  U32U retval = typetree->getRetVal(typenode);
  TY_IDX idx = getExistTypeIdx(typenode);

  TY &ty = (idx == TY_IDX_ZERO) ? New_TY (idx) : Ty_Table[idx];
  Clear_TY_is_incomplete (idx);
  TY_Init (ty, 0, KIND_FUNCTION, MTYPE_UNKNOWN, 0);
  Set_TY_align (idx, 1);

  TY_IDX ret_ty_idx;
  TY_IDX arg_ty_idx;
  TYLIST tylist_idx;

  // allocate TYs for return as well as parameters
  // this is needed to avoid mixing TYLISTs if one
  // of the parameters is a pointer to a function

  U32U ret_jIndex = typetree->getRetVal(typenode);
  if(ret_jIndex != 0){
    ret_ty_idx = Get_TY(ret_jIndex);
  }

  for (vector<U32U>::iterator it = args.begin ();
       it != args.end ();
       it++)
  {
    arg_ty_idx = Get_TY(*it);
    if (TY_is_incomplete (arg_ty_idx) ||
        (TY_kind (arg_ty_idx) == KIND_POINTER &&
            TY_is_incomplete (TY_pointed (arg_ty_idx))))
      Set_TY_is_incomplete (idx);
  }

  // if return type is pointer to a zero length struct
  // convert it to void
  if (!JGEN::Config::Keep_Zero_length_structs &&
      TY_mtype (ret_ty_idx) == MTYPE_M &&
      TY_size (ret_ty_idx) == 0)
  {
    // zero length struct being returned
    DevWarn ("function returning zero length struct at line ([lineno])");
    ret_ty_idx = Be_Type_Tbl (MTYPE_V);
  }

  // If the front-end adds the fake first param, then convert the
  // function to return void.

  if (TY_return_in_mem (ret_ty_idx))
  {
    ret_ty_idx = Be_Type_Tbl (MTYPE_V);
    Set_TY_return_to_param (idx);        // bugs 2423 2424
  }

  Set_TYLIST_type (New_TYLIST (tylist_idx), ret_ty_idx);
  Set_TY_tylist (ty, tylist_idx);

  for (vector<U32U>::iterator it = args.begin ();
       it != args.end ();
       it++)
  {
    arg_ty_idx = Get_TY(*it);
    Is_True (!TY_is_incomplete (arg_ty_idx) ||
        TY_is_incomplete (idx),
             ("Create_TY_For_Tree: unexpected TY flag"));
    if (!JGEN::Config::Keep_Zero_length_structs &&
        TY_mtype (arg_ty_idx) == MTYPE_M &&
        TY_size (arg_ty_idx) == 0)
    {
      // zero length struct passed as parameter
      DevWarn ("zero length struct encountered in function prototype at line (unknown)");
    }
    else
      Set_TYLIST_type (New_TYLIST (tylist_idx), arg_ty_idx);
  }
  if (typetree->get_args_count(typenode))
  {
    Set_TY_has_prototype (idx);
    if (arg_ty_idx != Be_Type_Tbl(MTYPE_V))
    {
      Set_TYLIST_type (New_TYLIST (tylist_idx), 0);
      Set_TY_is_varargs (idx);
    }
    else
      Set_TYLIST_type (Tylist_Table[tylist_idx], 0);
  }
  else
    Set_TYLIST_type (New_TYLIST (tylist_idx), 0);

  // TODO: TARGET X8664 SSE Specification Ignored
}

}