#include "json2whirl.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cmplrs/rcodes.h>
#include "defs.h"
#include "glob.h"
#include "erglob.h"
#include "err_host.tab"
#include "config.h"
#include "file_util.h" // for Last_Pathname_Component
#include "wgen_misc.h"


/***
    JGEN as J2WGEN or Json2Whirl 
 */

using std::string;
using std::cin;
using std::cout;

class JGEN{
private:

  int stage;
  int stage_json;
  int stage_parse;
  int stage_write;
  int last_error;
  
  string _in_filepath;
  string _out_filepath; 

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
  JGEN(string & json_path,
       string & out_path)  :   stage(0), stage_json(0), stage_write(0), stage_parse(0),
			       last_error(0) {
    _in_filepath = json_path;
    _out_filepath = out_path;
  }

  /**
   *  Set Path to JSON File
   */
  void setJsonPath(string & json_path){
    _in_filepath = json_path;
  }

  void setOutPath(string & out_path){
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

  // Proceed to next stage in JGEN
  int proceed(){
    /* 
       Continuously Do Stuff
     */
    int outcome = 0;
    while(stage != JGEN_FATAL_STOPPED && stage != JGEN_SUCCESS){
      if(stage == JGEN_JSON){
	stage_json = jgen_json.proceed();
	parse_stage_outcome(stage_json);
      }else if(stage == JGEN_PARSE){
	stage_json = jgen_parse.proceed();
	parse_stage_outcome(stage_json);
      }else if(stage == JGEN_WRITE){
	stage_write = write.proceed();
	parse_stage_outcome(stage_write);
      }
    }
    
    if(stage == JGEN_FATAL_STOPPED){
      return -1;
    }

    return 0;

  }

  void parse_stage_outcome(int out){
    int remainder = 0;
    if(out <= 10000 || out >= 99999){
      stage = JGEN_FATAL_STOPPED;
      last_error = 
      return ;
    }
    remainder = out % 10000;
    if(out % 10000 == 9999 || out % 10000){
      // FATAL;
      return JGEN_FATAL_STOPPED;
    }
    
  }

  jgen_stage 
  
}

int jgen_process_command(int argc, char ** argv){
  return 0;
}

  
int main(int argc, char **argv){
  jgen_process_command(argc, argv);
  jgen_act_accord();
}
