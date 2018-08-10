#ifndef OSPREY_BGEN_INIT_H
#define OSPREY_BGEN_INIT_H

//******************************************************
// the driver for pathgcc front end
//  -- transform spin to whirl through libspin
//******************************************************
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
#include "wgen_omp_directives.h"

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
#include "gspin-wgen-interface.h"
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
extern INT Debug_Level ;	/* -gn: debug level */

/***

   Starting the wgen_decl variable(wgen_misc.h)

 ***/

extern void Initialize_IRB (void);	/* In lieu of irbutil.h */
extern void WGEN_Omp_Init (void);
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


//
// Created by xc5 on 10/8/2018.
//

void
JGEN_Init (char * fn)
{
  //Initialize_Java_Int_Model();
  Initialize_C_Int_Model ();
  MEM_Initialize (); /// init memory
  Handle_Signals (); //// handle signals
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
  Configure ();
  IR_reader_init ();

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

  // Defered
  //  Init_Deferred_Function_Stack();
  //Init_Deferred_Decl_Init_Stack();
  Div_Split_Allowed = FALSE;
  Recip_Allowed = FALSE;

} /* JGEN_Init */

void
JGEN_File_Init (char *fn)
{
  /* Process each source file: */
  PPrepare_Source (fn);
  MEM_POOL_Push (&MEM_src_pool);

  Restore_Cmd_Line_Ctrls ();

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
  *need_inliner = JGEN::Config::need_inliner;
}


#endif