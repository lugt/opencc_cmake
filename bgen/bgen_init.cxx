
//******************************************************
// the driver for pathgcc front end
//  -- transform spin to whirl through libspin
//******************************************************
#include "org_jetbrains_java_decompiler_modules_bgen_BGenDriver.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cmplrs/rcodes.h>
#include "defs.h"
#include "glob.h"
#include "erglob.h"

//#include "err_host.tab"

#include "errors.h"
#include "symtab.h"
#include "const.h"
#include "pu_info.h"
#include "config.h"
#include "file_util.h" // for Last_Pathname_Component
#include "wn.h"
#include "wn_util.h"
#include "wn_simp.h"
#include "ir_reader.h"
#include "ir_bwrite.h"
//#include "wgen_decl.h"
#include "c_int_model.h"
#include "dwarf_DST_dump.h"
#include "targ_sim.h" // PUSH_RETURN_ADDRESS_ON_STACK
// #include "wgen_omp_directives.h"

/***  Wgen _ Misc Header Start    **/
#include "config.h"
#include "config_opt.h"	// for Div_Split_Allowed
#include "config_debug.h"
#include "config_list.h"
#include "config_targ_opt.h"
#include "controls.h"
#include "erglob.h"
#include "erlib.h"
#include "file_util.h"
#include "flags.h"
#include "glob.h"
#include "mempool.h"
#include "tracing.h"
#include "util.h"
#include "errors.h"
#include <stdarg.h>

#include "wn.h"
#include "wn_util.h"
#include "wn_simp.h"
#include "symtab.h"
#include "pu_info.h"
#include "ir_reader.h"
#include "ir_bwrite.h"
#include "c_int_model.h"
#include <unordered_map>


extern "C" {
  //#include "gspin-wgen-interface.h"
}

#if defined(BUILD_OS_DARWIN)
#include <limits.h>
#else /* defined(BUILD_OS_DARWIN) */
#include <values.h>
#endif /* defined(BUILD_OS_DARWIN) */
#include <sys/types.h>
#if defined(BUILD_OS_DARWIN)
#include <darwin_elf.h>
#else /* defined(BUILD_OS_DARWIN) */
#include <elf.h>
#endif /* defined(BUILD_OS_DARWIN) */


extern BOOL List_Enabled;
extern INT Opt_Level;
extern BOOL Enable_WFE_DFE;
extern BOOL Disable_Simplification_For_FE;

extern BOOL TARGET_64BIT;
//extern BOOL wgen_invoke_inliner;
//extern int lineno ;
//extern char *Spin_File_Name ;
//extern FILE *Spin_File ;
//extern BOOL flag_no_common ;
//extern int pstatic_as_global ;
//extern int emit_exceptions;
//extern BOOL opt_regions ;
//extern BOOL lang_cplus ;
//extern BOOL c_omit_external ;
//extern BOOL keep_inline_function;
//extern BOOL gen_pic_code ;
//extern BOOL tls_stress_test ;
extern void Process_TLS_Stress_Model(const char *p);
//extern BOOL enable_cxx_openmp ;
//extern gs_t program;
#ifndef TARG_MIPS
BOOL TARGET_64BIT = TRUE;
#else
BOOL TARGET_64BIT = FALSE;  // 11953: On MIPS, n32 is default abi
#endif

int Debug_Level = 1;
// an_error_severity error_threshold = es_warning;

/* Static data:	command	line information: */
 char Dash [] = "-";

/* Internal flags: */
// BOOL Echo_Flag =	FALSE;	/* Echo command	lines */
 BOOL Delete_IR_File = FALSE;	/* Delete SGIR file when d
				 */
int trace_verbose = 0;

INT func_decl_stack_size = 0;
INT func_decl_stack_top = -1;


int  WGEN_Keep_Zero_Length_Structs = TRUE;
PU_Info *PU_Tree_Root = NULL;
int Reg_Parm_Count = 0;
BOOL SSE_Reg_Parm = FALSE;


void Cleanup_Files(BOOL a, BOOL dotofile){

}




















/***

   Starting the wgen_decl variable(wgen_misc.h)

 ***/

extern void Initialize_IRB (void);	/* In lieu of irbutil.h */
// When region optimization is enabled using -foptimize-regions, we try not
// to close a region as soon as a call stmt finishes. We try to keep it open
// and include as many calls as possible.
// If we got an opportunity but did not close a region in WGEN_Stmt_Append,
// we set the following flag.


/* Specify how much debugging info to generate.  */
//extern enum debug_info_level;
// End gnu/flags.h data decl

extern BOOL gv_cond_expr;

extern BOOL JGEN_expanding_function_definition;


/* ====================================================================
 *
 * Local data.
 *
 * ====================================================================
 */

# define MAX_MSG_LEVEL 2
# define DEF_MSG_LEVEL 2

#ifdef MONGOOSE_CIF

extern mUINT32 Cif_Level;       	/* CIF level */

#define MAX_CIF_LEVEL 3
#define DEF_CIF_LEVEL 2
#endif /* MONGOOSE_CIF */

/* Default file	extensions: */
#define	IRB_FILE_EXTENSION ".B"	/* ACIR file */
#define	IRD_FILE_EXTENSION ".D"	/* Intermediate data file */
#define	ERR_FILE_EXTENSION ".e"	/* Error file */
#define	LST_FILE_EXTENSION ".l"	/* Listing file */
#define	TRC_FILE_EXTENSION ".t"	/* Trace file */
#define DSTDUMP_FILE_EXTENSION ".fe.dst" /* DST dump-file extension */

// Created by lu.gt@163.com Jason on 10/8/2018

/* ====================================================================
 *
 * Prepare_Source
 *
 * Process the next source argument and	associated file	control	flags
 * from	the command line.  Pre-process the source file unless
 * suppressed, and initialize output files as required.	 Return	TRUE
 * iff we have a successfully pre-processed source file	left to


 * compile.
 *
 * ====================================================================
 */

void
PPrepare_Source ( char * Src_File_Name )
{

  INT16	i;
  char *cp;
  char *fname;
  INT16 len;
  BOOL  dashdash_flag = FALSE;

  /* Initialize error handler: */
  Init_Error_Handler ( 100 );
  Set_Error_Line ( ERROR_LINE_UNKNOWN );
  Set_Error_File ( NULL );
  Set_Error_Phase ( "Front End Driver" );

  /* Clear file names: */
  Err_File_Name = Dash;	/* Error file */
  DSTdump_File_Name = NULL; /* DST dump */

  //  Delete_IR_File = FALSE;

  /* We've got a source file name -- open other files.
   * We want them to be created in the current directory, so we
   * strip off the filename only from Src_File_Name for use:
   */
  fname = Last_Pathname_Component ( Src_File_Name );

  /* Error file first to get error reports: */
  if ( Err_File_Name == NULL ) {
      /* Replace source file extension to get error file: */
      Err_File_Name = New_Extension
          ( fname, ERR_FILE_EXTENSION	);
    } else if ( *Err_File_Name == '-' ) {
      /* Disable separate error file: */
      Err_File_Name = NULL;
    }
  Set_Error_File ( Err_File_Name );

  /* Trace file next: */
  if ( Trc_File_Name == NULL ) {
      if ( Tracing_Enabled ) {
          /* Replace source file extension to get trace file: */
          Trc_File_Name = New_Extension
              ( fname, TRC_FILE_EXTENSION	);
        }
    } else if ( *Trc_File_Name == '-' ) {
      /* Leave trace file on stdout: */
      Trc_File_Name = NULL;
    }
  Set_Trace_File ( Trc_File_Name );
  if ( Get_Trace (TKIND_INFO, TINFO_TIME) ) Tim_File = TFile;

  /* We're ready to pre-process: */
  IR_File_Name = Src_File_Name;

  /* Open the IR file for compilation: */
  if ( Irb_File_Name == NULL ) {
      /* Replace source file extension to get listing file: */
      Irb_File_Name = New_Extension (	fname, IRB_FILE_EXTENSION );
    }

  if ( (Irb_File = fopen ( Irb_File_Name, "w" )) == NULL ) {
      ErrMsg ( EC_IR_Open, IR_File_Name, errno );
      Cleanup_Files ( TRUE, FALSE );	/* close opened files */
      return;
    } else {
      if ( Get_Trace ( TP_MISC, 1) ) {
          fprintf ( TFile,
                    "\n%sControl Values: Open_Dot_B_File\n%s\n", DBar, DBar );
          Print_Controls ( TFile, "", TRUE );
        }
    }
  /* Configure internal options for this source file */
  Configure_Source ( Src_File_Name );
}

// *****  Misc Extra End
extern BOOL c_omit_external; // for C programs, omit generating functions with
// gs_decl_external = TRUE, which is the default

/***

    Wgen_Decl Prefix ended.

**/

extern char *ABI_Name;



//
// Created by lu.gt@163.com Jason on 10/8/2018.
//

void
JGEN_Init (char * fn)
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
} /* JGEN_Init */

extern void set_sigv_random();

void
JGEN_File_Init (char *fn)
{
  /* Process each source file: */
  PPrepare_Source (fn);
  MEM_POOL_Push (&MEM_src_pool);
  //Restore_Cmd_Line_Ctrls ();
  set_sigv_random();
  
  /* open output file */
  Open_Output_Info (Irb_File_Name);

  DST_Init (NULL, 0);
  //DST_build(Argc, Argv); // do initial setup of dst
}

void
JGEN_File_Finish (void)
{
  Verify_SYMTAB (GLOBAL_SYMTAB);

  Write_Global_Info (PU_Tree_Root);
  
  Close_Output_Info ();
  IR_reader_finish ();

  MEM_POOL_Pop (&MEM_src_pool);
}

void
JGEN_Finish ()
{
  // WGEN_Stmt_Stack_Free ();
}

void
JGEN_Check_Errors (int *error_count, int *warning_count, BOOL *need_inliner)
{

  /* If we've seen errors, note them and terminate: */
  Get_Error_Count (error_count, warning_count);
  //*need_inliner = JGEN::Config::need_inliner;
}


/**
 * 
 *  Create A Primitive Type 
 *  @param    typeInternalId   bGEN
 *  @return   TY_IDX           the generated/previously_generated idx
 * 
*/
TY_IDX bGenCreateTypePrimitive(int typeInternalId){
  switch( typeInternalId ){
    mType_Idx_Table
  }
}

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    bgenInit
 * Signature: ()V
 */
void JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_bgenInit
  (JNIEnv *env, jclass clazz, jstring outputFilePath) {
  //printf("%s", "####### Initiliazing ! ");
    const char *p = env->GetStringUTFChars(outputFilePath, JNI_FALSE);
    char *cpy = (char *) malloc(5000);
    if(cpy == NULL || strlen(p) > 4800) {
      printf("%s","####### Error in init : cannot malloc ! ");
      return;
    }
    memset(cpy, 0, 5000);
    strncpy(cpy, p, strlen(p));
    printf("%s : %s .\n","######## start init, output file path", cpy);
    JGEN_Init(cpy);
    JGEN_File_Init(cpy);
    env->ReleaseStringUTFChars(outputFilePath, p);
}

/*
 * Class:     org_jetbrains_java_decompiler_modules_bgen_BGenDriver
 * Method:    bgenFinish
 * Signature: ()V
 */
void JNICALL Java_org_jetbrains_java_decompiler_modules_bgen_BGenDriver_bgenFinish
  (JNIEnv *env, jclass clazz) {
  printf("%s","######## finishing BGEN.\n");
  JGEN_Finish();
  JGEN_File_Finish();
  printf("%s","######## finish all.\n");
}
