#include "json_reader.h"
#include <string>
#include <iostream>
#include "jgen_node.h"
using namespace std;
using namespace JGEN;

void parse_class_def(Json_IR ir){
  Json::Value defs = ir["defs"];
}

void parse_one_function(Json_IR ir){  
  
}



int main(int argc, char ** argv){
  JGEN_Root root;
  if(argc >= 2){
    cout << "---------  Reading  ---------"<< endl
	 << argv[1] << endl;
    JGEN::Json_IR ir;
    cout << "--------- IR Opening --------" << endl;
    ir.open(argv[1]);
    cout << "--------- IR Reading --------" << endl;
    ir.read();
    root.init("out.B");
    parse_class_info(ir.getClass());
    parse_def_info(ir);
    cout << "-----------------------------" << endl;
  }else{
    cout << "----------   Usage -------------" << endl;
    cout << " -  jwtest <json_file_path> [...arguments] " << endl;
    cout << "-------- File Not Given --------" << endl;
    return -1;
  }
  return 0;
}
