#include "B2w_common.h"

/**
 * 
 *  Create A Primitive Type 
 *  @param    UINT             kind
 *  @return   TY_IDX           the generated/previously_generated idx
 * 
*/
TY_IDX B2W_get_primitive_type(UINT kind){
  switch( kind ){
    default:
      Is_Trace(Tracing(), (TFile, "%s\n", "**** Creating Primitive Type for kind -- failed"));
  }
}

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    getPrimitiveType
 * Signature: (ILjava/lang/String;)J
 */
jlong JNICALL
Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_getPrimitiveType
(JNIEnv * env_, jclass class_, jint kind_){

  Is_Trace(Tracing(),
	   (TFile, "%s%d\n"," *[getPrimitiveType] JNI entry. kind :" ,
        	    kind_));

  B2W_get_primitive_type((UINT) kind_);

  Is_Trace(Tracing(),
	   (TFile, "%s\n"," *[getPrimitiveType] JNI finished.  "));
}


/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    createFunctionType
v * Signature: (Ljava/lang/String;J[JI)J
 */
jlong JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_createFunctionType
(JNIEnv *, jclass, jstring, jlong, jlongArray, jint){
    Is_Trace(Tracing(),
             (TFile, "%s\n","[createFunctionType] JNI entry "));
}

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    createClassType
 * Signature: (Ljava/lang/String;III)J
 */
jlong JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_createClassType
(JNIEnv * env_, jclass class_, jstring name_, jint kind_, jint isXXX_, jint isYYY_)
{
    Is_Trace(Tracing(),
             (TFile, "%s\n", "[createClassType] JNI entry "));
}
