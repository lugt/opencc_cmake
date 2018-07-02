/**


   Version
   V0.0.0.1

   Author:
   Jason Lu @ 2018 Jul. 1 @ lu.gt@163.com

   Description:
   Using as a main entry for json2whirl
   
   Usage:
   1. Create an instance of JGEN class, JGEN(infile,outfile)
   2. JGEN.startProcess();
   3. It's done!

   Changelog:
   V0.0.0.1 Added basic structures.

*/

#include "json2whirl.h"
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

#include <iostream>
#include <string>

/***
    JGEN as J2WGEN or Json2Whirl 
 */

namespace JGEN{

class JGEN{
private:

  int stage;
  int stage_json;
  int stage_parse;
  int stage_write;
  int last_error;
  
  std::string _in_filepath;
  std::string _out_filepath; 

public:
  /**
   *  Empty Initializer
   */
  JGEN() : stage(0), stage_json(0),
	   stage_write(0), stage_parse(0), last_error(0) {
    _in_filepath = "";
    _out_filepath = "";
  }

  /**
   *  Default   
   *  @param json_path Path to JSON Input File
   *  @param out_path Path to Output Whirl (.B) file
   */
  JGEN(std::string & json_path,
       std::string & out_path)  :   stage(0), stage_json(0), stage_write(0), stage_parse(0),
			       last_error(0) {
    _in_filepath = json_path;
    _out_filepath = out_path;
  }

  /**
   *  Set Path to JSON File
   */
  void setJsonPath(std::string & json_path){
    _in_filepath = json_path;
  }

  void setOutPath(std::string & out_path){
    _out_filepath = out_path;
  }

  int startProcess(){
    stage = JGEN_STARTING;
    if(_in_filepath == ""){
      return JGEN_ERR_NO_INPUT_FILEPATH;
    }
    if(_out_filepath == ""){
      return JGEN_ERR_NO_OUTPUT_FILEPATH;
    }
    return proceed();
  }

private:
  // Proceed to next stage in JGEN
  int proceed(){
    /* 
       Continuously Do Stuff
     */
    int outcome = 0;
    while(stage != JGEN_FATAL_STOPPED && stage != JGEN_SUCCESS){
      if(stage <= JGEN_JSON){
	//void * jsonobj = json2mid.read(_in_filepath);
	stage = JGEN_PARSE;
      }else if(stage <= JGEN_PARSE){
	//void * parse_out = parse.parse(jsonobj);
	stage = JGEN_WRITE;
      }else if(stage <= JGEN_WRITE){
	stage = JGEN_SUCCESS;
      }
    }
    
    if(stage == JGEN_FATAL_STOPPED){
      return -1;
    }

    // Success !
    return 0;

  }

  void parse_stage_outcome(int out){
    int remainder = 0;
    if(out <= 10000 || out >= 99999){
      stage = JGEN_FATAL_STOPPED;
      last_error = out;
      return ;
    }
    remainder = out % 10000;
    if(remainder == 9999){
      // FATAL;
      stage = JGEN_FATAL_STOPPED;
    }else if(remainder == 8000){
      stage = JGEN_SUCCESS;
    }
  }
};

void output_help(){
  std::cout << "-------------------------------------------"<< std::endl;
  std::cout << "       Jgen : Json to Whirl Generator      \n"<<
              " Further description please go to wiki/docs  " << std::endl;
  std::cout << " -  https://github.com/lugt/opencc_cmake   -" << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << "Usage : jgen <INPUT_JSON_FILE> <OUTPUT_B_FILE>" << std::endl;
  std::cout << "Usage : jgen <INPUT_JSON_FILE> <OUTPUT_B_FILE> [... PARAMS]" << std::endl;
  std::cout << "Usage : jgen --help " << std::endl;      
}
  
JGEN * g;

int jgen_process_command(int argc, char ** argv){
  if(argc < 2) {
    output_help();
    return -1;
  }

  std::string fni = argv[1], fno = "";
  if(fni == "-h" || fni == "--help" || fni == "h" || fni == "help" || fni == "-v" || fni == "--version" || fni == "--v" || fni == "--h" || fni == "-version" || fni[0] == '-'){
    output_help();
    return -2;
  }
  std::cout << "Reading from " << argv[1] ;
  if(argc >= 3) {
    fno = argv[2];
  }else{
    fno = fni + ".B";
  }
  std::cout << ", and output as " << fno << std::endl;
  g = new JGEN(fni, fno);
  return 0;
}

void jgen_act_accord(){
  if(g == NULL){
    throw new std::exception();
  }
  g->startProcess();
}


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


}

int main(int argc, char **argv){
  if(JGEN::jgen_process_command(argc, argv) < 0){
    return -10;
  }
  JGEN::jgen_act_accord();
}
