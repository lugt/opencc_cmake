
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

extern BOOL B2W_expanding_function_definition;


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

/***

    Wgen_Decl Prefix ended.

**/

extern char *ABI_Name;

// *****  Misc Extra End
extern BOOL c_omit_external; // for C programs, omit generating functions with
// gs_decl_external = TRUE, which is the default


extern PU_Info *PU_Tree_Root;
#define Tracing() Tracing_Enabled
extern void PPrepare_Source ( char * Src_File_Name );
