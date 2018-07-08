#ifndef JGEN_NODE_H
#define JGEN_NODE_H

#include <json/json.h>
#include <string>

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
#include "config.h"
#include "file_util.h" // for Last_Pathname_Component
#include "wgen_misc.h"

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
#ifdef FE_GNU_4_2_0
BOOL enable_cxx_openmp = TRUE;
#endif
gs_t program;
/*       MAX_DEBUG_LEVEL        2  :: Defined in flags.h */
# define DEF_DEBUG_LEVEL        0
INT Debug_Level = DEF_DEBUG_LEVEL;	/* -gn: debug level */

/***
    
   Starting the wgen_decl preset

 ***/

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
#include "defs.h"
#include "errors.h"

#include "glob.h"
#include "wn.h"
#include "wn_util.h"
#include "symtab.h"
#include "const.h"
#include "pu_info.h"
#include "ir_bwrite.h"
#include "ir_reader.h"
#include "erglob.h"  // EC_Unimplemented_Feature
#include "jgen_decl.h"
#include "wgen_misc.h"
#include "wgen_dst.h"
#include "wgen_spin_symbol.h"
#include "wgen_expr.h"
#include "wgen_stmt.h"
#include "wgen_tracing.h"
//#include "tree_cmp.h"
#include "wgen_dst.h" // DST_enter_member_function
#include "dwarf_DST_dump.h"
#include "targ_sim.h" // PUSH_RETURN_ADDRESS_ON_STACK
#include "wgen_omp_directives.h"

#ifdef KEY
#include <ext/hash_map>
#endif

extern BOOL c_omit_external; // for C programs, omit generating functions with
			     // gs_decl_external = TRUE, which is the default

int flag_openmp;
gs_t decl_arguments;

static gs_t WGEN_get_thunk_target (gs_t decl);
static gs_t WGEN_get_final_thunk_target (gs_t decl);
static void WGEN_Handle_Named_Return_Value(gs_t fn);
static WN *WGEN_Start_Function(gs_t fndecl);
static void WGEN_Finish_Function(gs_t fndecl);

// The initializer for the named return value object.  Expand this in place of
// the DECL_INITIAL in the object's VAR_DECL.
// IMPORTANT:  Doesn't work for nested functions.
gs_t named_ret_obj_initializer;

/* ST to represent EXC_PTR_EXPR if C++ exceptions are disabled */
ST * Dummy_Exc_Ptr_Expr = NULL;

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
WN *Current_Entry_WN(void) {
    if (curr_entry_wn.size()==0) {
        return NULL;
    } else {
        return curr_entry_wn.back(); 
    }
}

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

void JGEN_Root::finish(){
  Verify_SYMTAB (GLOBAL_SYMTAB);
  Write_Global_Info (PU_Tree_Root);
  Close_Output_Info ();
  IR_reader_finish ();
  MEM_POOL_Pop (&MEM_src_pool);
};

void JGEN_Root::init(){
  char * buf = new char[2000];
  if(this->output_file.size() < 1900){
    strcpy(buf, this->output_file.c_str());
  }
  Open_Output_Info(buf);
}

void JGEN_Root::init(string & fn){
  this->output_file = fn;
  char * buf = new char[2000];
  if(this->output_file.size() < 1900){
    strcpy(buf, this->output_file.c_str());
  }
  Open_Output_Info ( buf );
};


#endif
