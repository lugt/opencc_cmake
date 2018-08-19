#include "B2w_common.h"

void  B2W_create_block(){
   WN_CreateBlock();
}


void B2W_map_tab_create(void * pool){
  Is_True(pool != NULL, ("%s\n","**** Error in B2W_map_tab_create : %s",
                          "Null Pool Pointer"));
  WN_MAP_TAB_Create((mem_pool *) pool);
}

UINT64 B2W_wn_int_const(UINT const_value){
  // 
}

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    jniWnCreateBlock
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_jniWnCreateBlock
  (JNIEnv *, jclass){
  Is_Trace(Tracing(),
           (TFile, "[jniWnCreateBlock] entry "));
    B2W_create_block();
}

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    jniWnMapTabCreate
 * Signature: (mempool * J)J
 */
JNIEXPORT jlong JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_jniWnMapTabCreate
  (JNIEnv *, jclass, jlong pool){
  Is_Trace(Tracing(),
           (TFile, "[jniWnMapTabCreate] entry "));
  B2W_map_tab_create((void *) pool);
}


/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    wnIntConst
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_wnIntConst
(JNIEnv *, jclass, jint const_value){
  Is_Trace(Tracing(),
           (TFile, "[WnIntConst] entry "));
  return (jlong) B2W_wn_int_const(const_value);
}
