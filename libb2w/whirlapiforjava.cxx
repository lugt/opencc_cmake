#include "io_xc5_decompiler_CommonJNI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Output file Info
const char * OutputFileNameStr;

/*
 * Class:     io_xc5_decompiler_CommonJNI
 * Method:    whirlInitialize
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_xc5_decompiler_CommonJNI_whirlInitialize
(JNIEnv * env_, jobject obj_, jstring str_){

  printf();
  char wwstr[5000] = {};
  const char * translatedStr = (const char *) jstringToChar(env_,str_);

  // Please Check in advance!
  // Which Is Extremely Dangerous!
  strncpy(wwstr, translatedStr, strlen(translatedStr));
  
  JGEN_Init(wwstr);
  JGEN_File_Init(wwstr);
}

/*
 * Class:     io_xc5_decompiler_CommonJNI
 * Method:    whirlFinish
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_io_xc5_decompiler_CommonJNI_whirlFinish
(JNIEnv *, jobject obj_){
  JGEN_File_Finish();
  JGEN_Finish();
}


