//
// Created by xc5 on 15/7/2018.
//

#include "jgen_include.h"
#include "jgen_global.h"

#ifndef TARG_MIPS
BOOL TARGET_64BIT = TRUE;
#else
BOOL TARGET_64BIT = FALSE;  // 11953: On MIPS, n32 is default abi
#endif

int Debug_Level = 1;
int trace_verbose = FALSE;
// an_error_severity error_threshold = es_warning;

/* Static data:	command	line information: */
        INT32 Argc;		/* Copy of argc */
 char **Argv;		/* Copy of argv */
 INT32 Source_Arg = 0;	/* Number of current source arg */
 char Dash [] = "-";

/* Internal flags: */
 BOOL Echo_Flag =	FALSE;	/* Echo command	lines */
 BOOL Delete_IR_File = FALSE;	/* Delete SGIR file when done */

// KEY
bool Did_Not_Terminate_Region = FALSE;


 gs_t *deferred_function_stack;
 INT32 deferred_function_i;
 INT32 deferred_function_max;
 BOOL flag_keep_inline_functions = FALSE;
 UINT32 WGEN_PU_count = 0;
 BOOL finish_alias = FALSE;

// keep pu and pu_info
extern PU_Info *PU_Tree_Root;
 PU_Info *PU_Info_Table     [258] = {0};


 ST      *Return_Address_ST [258] = {0};
 BOOL map_mempool_initialized = FALSE;
 MEM_POOL Map_Mem_Pool;


// to manage the current function
 gs_t curr_namespace_decl = NULL;

 int __ctors = 0;
 int __dtors = 0;

 gs_t *func_decl_stack = NULL;
 INT func_decl_stack_size = 0;
 INT func_decl_stack_top = -1;


int  WGEN_Keep_Zero_Length_Structs = TRUE;
PU_Info *PU_Tree_Root = NULL;
int Reg_Parm_Count = 0;
BOOL SSE_Reg_Parm = FALSE;


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
BOOL JGEN_expanding_function_definition = FALSE;

// The following taken from gnu/flags.h
enum debug_info_level
{
    DINFO_LEVEL_NONE,     /* Write no debugging info.  */
    DINFO_LEVEL_TERSE,    /* Write minimal info to support tracebacks only.  */
    DINFO_LEVEL_NORMAL,   /* Write info for all declarations (and line table). */
    DINFO_LEVEL_VERBOSE   /* Write normal info plus #define/#undef info.  */
};

#include "err_host.tab"

void get_err_tables(){
 Set_Error_Tables ( Phases, host_errlist );
}


void Cleanup_Files(BOOL a, BOOL dotofile){

}


static std::vector<WN*> curr_entry_wn;
static void Push_Current_Entry_WN(WN *wn) { curr_entry_wn.push_back(wn); }
static void Pop_Current_Entry_WN() { curr_entry_wn.pop_back(); }