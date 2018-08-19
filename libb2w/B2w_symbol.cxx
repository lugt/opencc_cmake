#include "B2w_common.h"

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    createVarSymbol
 * Signature: (Ljava/lang/String;JIII)J
 */
jlong JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_createVarSymbol
(JNIEnv * env_, jclass class_, jstring name_, jlong typeId_, jint, jint, jint){
  Is_Trace(Tracing(),
	   (TFile, "[createVarSymbol] entry : %llx \n" ,
          	    typeId_));

}


/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    createFunctionSymbol
 * Signature: (Ljava/lang/String;IIIIJI)J
 */
jlong JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_createFunctionSymbol
(JNIEnv * env_, jclass myclass_, jstring name_, jint isXXX_, jint isYYY_, jint isZZZ_, jint isRRR_, jlong typeId_, jint isPPP_){
    Is_Trace(Tracing(),
	     (TFile, "%s\n", "[createFunctionSymbol] entry "));
}
