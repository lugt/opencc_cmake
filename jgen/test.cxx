#include "json_reader.h"
#include <string>
#include <iostream>
#include "jgen_node.h"

using namespace std;
using namespace JGEN;

void parse_class_def(Json_IR ir){
  Json::Value defs = ir.get_defs();
}

void parse_one_function(JGEN::Json_IR ir){  
  
}

string infn;
string outfn;

int main(int argc, char ** argv){
  JGEN_Root root;
  if(argc >= 2){
    cout << "---------  File:  ---------"<< endl
	 << argv[1] << endl;
    JGEN::Json_IR ir;
    cout << "-------  Json_IR Opening --------" << endl;
    ir.open(argv[1]);
    cout << "------- Json_IR Reading --------" << endl;
    ir.read();
    cout << "------- Jgen_Root :: Init  ----- " << endl;
    outfn = "out.B";
    root.init(outfn);
    cout << "-------- Root Init finished -------" << endl;
    parse_class_def(ir);
    cout << "-------- def finished --------" << endl;
    root.finish();
    cout << "-------- root finished --------" << endl;
  }else{
    cout << "----------   Usage -------------" << endl;
    cout << " -  jwtest <json_file_path> [...arguments] " << endl;
    cout << "-------- File Not Given --------" << endl;
    return -1;
  }
  return 0;
}
