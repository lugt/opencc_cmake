#include "json_reader.h"
#include <string>
#include <iostream>
#include "jgen_node.h"

using namespace std;
using namespace JGEN;

void parse_class_def(Json_IR ir){
  // Predef

  // Type

  // Defs . Member Fields
  Json::Value defs = ir.get_defs();
}

void parse_one_function(JGEN::Json_IR ir){  
  
}

string infn;
string outfn;

int main(int argc, char ** argv){
  JGEN_Root root;
  outfn = "out.B";
  if(argc >= 2){
    cout << "---------  File:  ---------"<< endl
	 << argv[1] << endl;
    JGEN::Json_IR ir;
    cout << endl << "--------- [IR] Opening --------" << endl;
    ir.open(argv[1]);
    cout << endl << "--------- [IR] Reading --------" << endl;
    ir.read();
    cout << endl << "-------- Init JGEN Root  ----- " << endl;
    outfn = "out.B";
    cout << "------- Jgen_Root :: Init  ----- " << endl;
    root.init(outfn);
    cout << endl << "-------- Root Init finished -------" << endl;
    cout << "-------- parse_class_def -------" << endl;
    parse_class_def(ir);
    cout << endl << "-------- def finished --------" << endl;
    root.finish();
    cout << endl << "-------- root finished --------" << endl;
  }else{
    cout << "----------   Usage -------------" << endl;
    cout << " -  jwtest <json_file_path> [...arguments] " << endl;
    cout << "-------- File Not Given --------" << endl;
    return -1;
  }
  return 0;
}
