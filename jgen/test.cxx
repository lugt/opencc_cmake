#include "json_reader.h"
#include <string>
#include <iostream>
#include "jgen_node.h"
#include "jgen_global.h"

using std::string;
using namespace JGEN;

void parse_class_def(Json_IR ir){
  // Predef

  // Type

  // Defs . Member Fields
  Json::Value defs = ir.get_defs();
}

void parse_one_function(JGEN::Json_IR ir){  
  
}

std::string infn;
std::string outfn;

using std::cout;
using std::endl;

int main(int argc, char ** argv){
  JGEN_Root root;
  outfn = "out.B";
  if(argc >= 2){
    cout << "---------  File:  ---------"<< endl
	 << argv[1] << endl;
    JGEN::Json_IR ir;
    cout << endl << "---------       [IR] Opening       --------" << endl;
    ir.open(argv[1]);
    cout << endl << "---------       [IR] Reading       --------" << endl;
    ir.read();
    cout << endl << "-------- [Gen:Root] Init root  -------------" << endl;
    root.init(outfn);
    cout << endl << "-------- [Gen:Root] init finished ----------" << endl;
    cout << endl << "-------- [Test] parse_class_def ------------" << endl;
    parse_class_def(ir);
    cout << endl << "-------- [Test] parse_class_def finished ---" << endl;
    root.finish();
    cout << endl << "-------- [Gen:root] finished --------" << endl;
    cout << endl << "-------- [Jwtest] all procedure finished  --------" << endl;
  }else{
    cout << "----------   Usage -------------" << endl;
    cout << " -  jwtest <json_file_path> [...arguments] " << endl;
    cout << "-------- File Not Given --------" << endl;
    return -1;
  }
  return 0;
}
