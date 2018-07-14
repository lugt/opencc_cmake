#ifndef JGEN_NODE_H
#define JGEN_NODE_H

#include <json/json.h>
#include <string>
#include <fstream>

//******************************************************
// the driver for pathgcc front end
//  -- transform spin to whirl through libspin
//******************************************************
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cmplrs/rcodes.h>
#include "gspin-wgen-interface.h" 
#include "defs.h"
#include "glob.h"
#include "erglob.h"
#include "err_host.tab"
#include "errors.h"
#include "symtab.h"
#include "const.h"
#include "pu_info.h"
#include "config.h"
#include "file_util.h" // for Last_Pathname_Component
#include "wgen_misc.h"
#include "wn.h"
#include "wn_util.h"
#include "wn_simp.h"
#include "ir_reader.h"
#include "ir_bwrite.h"
//#include "wgen_decl.h"
#include "jgen_decl.h"
#include "wgen_expr.h"
#include "wgen_dst.h"
#include "wgen_misc.h"
#include "wgen_stmt.h"
#include "c_int_model.h"
#include "wgen_spin_symbol.h"
#include "wgen_tracing.h"
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
#include "wgen_decl.h"
#include "wgen_expr.h"
#include "wgen_dst.h"
#include "wgen_misc.h"
#include "wgen_stmt.h"
#include "c_int_model.h"



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

#ifndef TARG_MIPS
BOOL TARGET_64BIT = TRUE;
#else
BOOL TARGET_64BIT = FALSE;  // 11953: On MIPS, n32 is default abi
#endif

BOOL wgen_invoke_inliner = FALSE;
int lineno = 0;
char *Spin_File_Name = NULL;
FILE *Spin_File = NULL;
BOOL flag_no_common = FALSE;
int pstatic_as_global = 0;
int emit_exceptions = -1;
BOOL opt_regions = 0;
BOOL lang_cplus = FALSE;
BOOL c_omit_external = TRUE;
BOOL keep_inline_functions=FALSE;
BOOL gen_pic_code = FALSE;
BOOL tls_stress_test = FALSE;
extern void Process_TLS_Stress_Model(const char *p);
BOOL enable_cxx_openmp = TRUE;
gs_t program;
# define DEF_DEBUG_LEVEL        2
INT Debug_Level = DEF_DEBUG_LEVEL;	/* -gn: debug level */

/***
    
   Starting the wgen_decl variable(wgen_misc.h)

 ***/

int  WGEN_Keep_Zero_Length_Structs = TRUE;
PU_Info *PU_Tree_Root = NULL;
int Reg_Parm_Count = 0;
BOOL SSE_Reg_Parm = FALSE;


extern void Initialize_IRB (void);	/* In lieu of irbutil.h */

#ifdef FE_GNU_4_2_0
extern void WGEN_Omp_Init (void);
#endif

static void WGEN_Stmt_Stack_Init (void);
static void WGEN_Stmt_Stack_Free (void);
#ifdef KEY
static void WGEN_Guard_Var_Init();
// When region optimization is enabled using -foptimize-regions, we try not
// to close a region as soon as a call stmt finishes. We try to keep it open
// and include as many calls as possible.
// If we got an opportunity but did not close a region in WGEN_Stmt_Append,
// we set the following flag.
bool Did_Not_Terminate_Region = FALSE;

extern int pstatic_as_global;
#endif

// The following taken from gnu/flags.h
enum debug_info_level
{
  DINFO_LEVEL_NONE,     /* Write no debugging info.  */
  DINFO_LEVEL_TERSE,    /* Write minimal info to support tracebacks only.  */
  DINFO_LEVEL_NORMAL,   /* Write info for all declarations (and line table). */
  DINFO_LEVEL_VERBOSE   /* Write normal info plus #define/#undef info.  */
};

/* Specify how much debugging info to generate.  */
enum debug_info_level debug_info_level;
// End gnu/flags.h data decl

BOOL gv_cond_expr = FALSE;


/* ====================================================================
 *
 * Local data.
 *
 * ====================================================================
 */

# define MAX_MSG_LEVEL 2
# define DEF_MSG_LEVEL 2

#ifdef MONGOOSE_CIF
mUINT32 Cif_Level = 0;       	/* CIF level */
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

int trace_verbose = FALSE;
// an_error_severity error_threshold = es_warning;

/* Static data:	command	line information: */
static INT32 Argc;		/* Copy of argc */
static char **Argv;		/* Copy of argv */
static INT32 Source_Arg = 0;	/* Number of current source arg */
static char Dash [] = "-";

/* Internal flags: */
static BOOL Echo_Flag =	FALSE;	/* Echo command	lines */
static BOOL Delete_IR_File = FALSE;	/* Delete SGIR file when done */


// *****  Misc End


void Cleanup_Files(BOOL a, BOOL dotofile){

}



// *****  Misc Extra Start

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

static void
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

  Delete_IR_File = FALSE;
  
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

#ifdef KEY
#include <ext/hash_map>
#endif

extern BOOL c_omit_external; // for C programs, omit generating functions with
			     // gs_decl_external = TRUE, which is the default

//int flag_openmp;
//gs_t decl_arguments;

static gs_t WGEN_get_thunk_target (gs_t decl);
static gs_t WGEN_get_final_thunk_target (gs_t decl);
static void WGEN_Handle_Named_Return_Value(gs_t fn);
static WN *WGEN_Start_Function(gs_t fndecl);
static void WGEN_Finish_Function(gs_t fndecl);

// The initializer for the named return value object.  Expand this in place of
// the DECL_INITIAL in the object's VAR_DECL.
// IMPORTANT:  Doesn't work for nested functions.
//gs_t named_ret_obj_initializer;

/* ST to represent EXC_PTR_EXPR if C++ exceptions are disabled */
//ST * Dummy_Exc_Ptr_Expr = NULL;

static gs_t *deferred_function_stack;
static INT32 deferred_function_i;
static INT32 deferred_function_max;
static BOOL flag_keep_inline_functions = FALSE;
static UINT32 WGEN_PU_count = 0;
static BOOL finish_alias = FALSE;

// keep pu and pu_info
extern PU_Info *PU_Tree_Root;
static PU_Info *PU_Info_Table     [258] = {0};


static ST      *Return_Address_ST [258] = {0};
static BOOL map_mempool_initialized = FALSE;
static MEM_POOL Map_Mem_Pool;


// to manage the current function
static gs_t curr_namespace_decl = NULL;

static int __ctors = 0;
static int __dtors = 0;

static gs_t *func_decl_stack = NULL;
static INT func_decl_stack_size = 0;
static INT func_decl_stack_top = -1;

//to manage the entry_wn, current function's entry_wn always on top
static std::vector<WN*> curr_entry_wn;
static void Push_Current_Entry_WN(WN *wn) { curr_entry_wn.push_back(wn); }
static void Pop_Current_Entry_WN() { curr_entry_wn.pop_back(); }

/* WN *Current_Entry_WN(void) {
    if (curr_entry_wn.size()==0) {
        return NULL;
    } else {
        return curr_entry_wn.back(); 
    }
}*/

/***
    
    Wgen_Decl Prefix ended.

**/


/***
    WGEN_decl Ended
 ***/

using namespace std;

class JGEN_NODE{
 public:
  WN * whirl;
  string name;
  JGEN_NODE * root;
  JGEN_NODE(){
    whirl = NULL;
    root = NULL;
    name = "empty_node";
  }

  void set_line_info_and_file(int line, string & fn){
    return;
  }
};

class JGEN_Variable : public JGEN_NODE{
 public:
  JGEN_Variable(){};
};

class JGEN_Root : public JGEN_NODE{
public:
  JGEN_Root(){
    output_file = "default.B";
  }
  
  JGEN_Root(string & out){
    output_file = out;
  };
  
  string output_file;
  void init();
  void init(string & fn);
  void finish();

};

class JGEN_Function : public JGEN_NODE{
 private:
  JGEN_NODE parent;
 public:
  JGEN_Function(JGEN_Root parent){
    root = &parent;

    if (!map_mempool_initialized) {
      MEM_POOL_Initialize(&Map_Mem_Pool, "Map_Mem_Pool" , FALSE);
      map_mempool_initialized = TRUE;
    } else {
      MEM_POOL_Pop(&Map_Mem_Pool);
    }

    /* create the map table for the next PU */
    (void)WN_MAP_TAB_Create(&Map_Mem_Pool);
    New_Scope (CURRENT_SYMTAB + 1, Malloc_Mem_Pool, TRUE);
    //jgen_set_line_and_file (lineno, fn);    
  }
};



extern char *ABI_Name;

void
JGEN_Init (char *fn)
{
  // Initialize_Java_Int_Model();
  Initialize_C_Int_Model();
  MEM_Initialize(); /// init memory
  Handle_Signals(); //// handle signals
  /* Perform preliminary command line processing: */
  Set_Error_Line ( ERROR_LINE_UNKNOWN );
  Set_Error_Phase ( "Front End Driver" ); //end driver
  Preconfigure (); /// what to configure

  if (TARGET_64BIT)
    ABI_Name = "n64"; // TARGET_64BIT should be defined somewhere
  else ABI_Name = "n32";

  if (lang_cplus)
    pstatic_as_global = TRUE;
  else
    pstatic_as_global = FALSE;

  Init_Controls_Tbl();
  Argc = 1;
  char * str = "jwtest";
  char ** argv = new char*[2];
  argv[0] = str;
  Argv = argv;
  Configure ();
  IR_reader_init();

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
  PPrepare_Source(fn);
  MEM_POOL_Push (&MEM_src_pool);

  Restore_Cmd_Line_Ctrls();

  /* open output file */
  Open_Output_Info ( Irb_File_Name );
  DST_Init(NULL,0);
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
  Get_Error_Count ( error_count, warning_count);
  *need_inliner = wgen_invoke_inliner;
}


void JGEN_Entry(string fn){

  char * buf = new char[2000];
  if(fn.size() < 1900){
    strcpy(buf, fn.c_str());
  }

  //assert buf not empty;
  INT error_count, sorry_count;
  BOOL need_inliner;
  struct stat sbuf;
  int st;	
  Disable_Simplification_For_FE = TRUE;
  Set_Error_Tables ( Phases, host_errlist );
  //  Process_Cc1_Command_Line(gs_cc1_command_line_args(program));
  JGEN_Init(buf);
  JGEN_File_Init(buf);
}





void JGEN_Root::finish(){
  JGEN_File_Finish();
};

void JGEN_Root::init(){
  JGEN_Entry(this->output_file);
}

void JGEN_Root::init(string & fn){
  this->output_file = fn;
  JGEN_Entry(this->output_file);
};


#endif
