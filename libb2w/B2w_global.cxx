#include "B2w_common.h"

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
BOOL Run_vsaopt = FALSE;

void Cleanup_Files(BOOL a, BOOL dotofile){

}


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

  // TO BE SWITCHABLE?
  Tracing_Enabled = true;
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
