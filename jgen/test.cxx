#include "json_reader.h"
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char ** argv){
  if(argc >= 2){
    std::cout << "--------  Reading  --------- \n  " << argv[1] << endl;
    JGEN::Json_IR ir;
    cout << "--------- IR Opening --------" << endl;
    ir.open(argv[1]);
    cout << "--------- IR Reading --------" << endl;
    ir.read();
    cout << "-----------------------------" << endl;
  }else{
    cout << "----------   Usage -------------" << endl;
    cout << " -  jwtest <json_file_path> [...arguments] " << endl;
    return -1;
  }
  return 0;
}
