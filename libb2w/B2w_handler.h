/*****************************************************************************************************
 **   
 **  File: B2w_handler.h
 **
 **  A common decl for handlers inside B2w.
 ** 
 ** Call Graph:
 ** Java -> JNI -> Handler(*) -> WHIRL API
 *****************************************************************************************************/

#include <jni.h>

//------------------------------------------
// JNI Related Utilities
//------------------------------------------


extern INT B2W_extract_int(jint j);
extern INT B2W_extract_string(jstring str_);


//=---------------------------------------------  
// WN API  Handler
//----------------------------------------------
  
extern void B2W_map_tab_create(void *);
extern void B2W_create_block();
extern UINT64 B2W_wn_int_const(UINT const_value);

//----------------------------------------------
// ST API Handler
//----------------------------------------------


//----------------------------------------------
// TY API Handler
//----------------------------------------------

TY_IDX B2W_get_primitive_type(UINT kind);
