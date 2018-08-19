#include "B2w_common.h"
#include "B2w_handler.h"
#include <string.h>
//
// Created by lu.gt@163.com Jason on 10/8/2018.
//

void
B2W_init (char * fn)
{
  //Initialize_Java_Int_Model();
  Initialize_C_Int_Model ();
  MEM_Initialize (); /// init memory
  //  Handle_Signals (); //// handle signals
  /* Perform preliminary command line processing: */
  Set_Error_Line (ERROR_LINE_UNKNOWN);
  Set_Error_Phase ("Front End Driver"); //end driver
  Preconfigure (); /// what to configure

  if (TARGET_64BIT)
    ABI_Name = (char *) "n64"; // TARGET_64BIT should be defined somewhere
  else ABI_Name = (char *) "n32";

  Init_Controls_Tbl ();


  int argc = 1;
  const char *str = "jwtest";
  char **argv = new char *[2];
  argv[0] = (char *) str;


  printf("%s", "POSITION 1M REACHED \n");
  
  Configure ();
  IR_reader_init ();

  
  printf("%s", "POSITION 2A REACHED \n");
  // Initialize ST/TY/PU
  Initialize_Symbol_Tables (TRUE);

  //WGEN_Stmt_Stack_Init ();
  //WGEN_Stmt_Init ();

  //WGEN_Omp_Init ();

  //WGEN_Expr_Init ();
  WHIRL_Mldid_Mstid_On = TRUE;
  WN_Simp_Fold_LDA = TRUE;  // fold (LDA offset) + const to LDA (offset+const)
  // since the static initialization code relies on it
  WHIRL_Keep_Cvt_On = TRUE; // so simplifier won't I8I4CVT

  //WGEN_Guard_Var_Init ();
  //WGEN_Guard_Block_Stack_Init();

  printf("%s", "POSITION 3E REACHED \n");
  // Defered
  //  Init_Deferred_Function_Stack();
  //Init_Deferred_Decl_Init_Stack();
  Div_Split_Allowed = FALSE;
  Recip_Allowed = FALSE;
  printf("%s", "POSITION 4J REACHED \n");
} /* B2W_init */

void
B2W_file_init (char *fn)
{
  /* Process each source file: */
  PPrepare_Source (fn);
  MEM_POOL_Push (&MEM_src_pool);
  //Restore_Cmd_Line_Ctrls ();
  /* open output file */
  Open_Output_Info (Irb_File_Name);

  DST_Init (NULL, 0);
  //DST_build(Argc, Argv); // do initial setup of dst
}

void
B2W_file_finish (void)
{
  Verify_SYMTAB (GLOBAL_SYMTAB);

  Write_Global_Info (PU_Tree_Root);
  
  Close_Output_Info ();
  IR_reader_finish ();

  MEM_POOL_Pop (&MEM_src_pool);
}

void
B2W_finish ()
{
  // WGEN_Stmt_Stack_Free ();
}

void
B2W_Check_Errors (int *error_count, int *warning_count, BOOL *need_inliner)
{

  /* If we've seen errors, note them and terminate: */
  Get_Error_Count (error_count, warning_count);
  //*need_inliner = B2W::Config::need_inliner;
}

/******************************************************************************
  *
  *  Starts the JNI/Java Wrapped part
  *
  ****************************************************************************/


/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    bgenInit
 * Signature: ()V
 */
void JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_bgenInit
(JNIEnv *env, jclass clazz, jstring output, jint trace_level) {

    Tracing_Enabled = TRUE;
  
    Is_True(output != NULL, ("JNI B2W bgenInit failed because null string"));

    const char *p = env->GetStringUTFChars(output, JNI_FALSE);	
    
    const char *dup = strdup(p);
      
 Is_Trace(Tracing(),
	     (TFile, "%s\n%s\n", "####### B2W init entry #######\n", dup));

     
    B2W_init((char *) dup);
    B2W_file_init((char *) dup);

    Is_Trace(Tracing(),
     (TFile, "%s %s \n", "####### B2W init 10% ####### \n output file path : ", dup));

     
    env->ReleaseStringUTFChars(output, p);
}

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    bgenFinish
 * Signature: ()V
 */
void JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_bgenFinish
  (JNIEnv *env, jclass clazz) {
  Is_Trace(Tracing(),
	   (TFile, "%s\n", "####### B2W finishing 90% #######"));
  B2W_finish();
  B2W_file_finish();
  Is_Trace(Tracing(),
      	   (TFile, "%s\n", "####### B2W all finished 100% #######"));
}


/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    outputTrace
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_outputTrace
(JNIEnv * env, jclass, jstring trace_output){
   const char *p = env->GetStringUTFChars(trace_output, JNI_FALSE);	
    Is_Trace(Tracing(),
    (TFile, "%s %s \n", "###", p));
    env->ReleaseStringUTFChars(trace_output, p);
}
