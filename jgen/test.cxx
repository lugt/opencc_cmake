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
    cout << "Reading:"
	 << argv[1] << endl;
    JGEN::Json_IR ir;
    cout << endl << "--------- [IR] Opening --------" << endl;
    ir.open(argv[1]);
    cout << endl << "--------- [IR] Reading --------" << endl;
    ir.read();
    cout << endl << "-------- Init JGEN Root  ----- " << endl;
    outfn = "out.B";
    root.init(outfn);
    cout << endl << "-------- Root Init finished -------" << endl;
    parse_class_def(ir);
    cout << endl << "-------- def finished --------" << endl;
    root.finish();
    cout << endl << "-------- root finished --------" << endl;
  }else{
    cout << endl << "----------   Usage -------------" << endl;
    cout << endl << " -  jwtest <json_file_path> [...arguments] " << endl;
    cout << endl << "-------- File Not Given --------" << endl;
    return -1;
  }
  return 0;
}
