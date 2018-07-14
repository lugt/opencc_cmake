/***
 * Json AST Reading Base Class Declaration
 * Author: Jason Lu : lu.gt@163.com
 * Version : V0.1 
 * Usage:
 *  1. Instantiate the JGEN::Json_IR class,
 *  2. JsonIR::open (file_name)
 *  3. JsonIR::read ()
 ***/
#include "json_reader.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <algorithm>
#include <string>

int JSON_READING_STATE = 0;

namespace JGEN{

  using namespace std;
  
  static const char * json_data = "data";
  
  int Json_IR::read() {    
    std::ifstream ifs;
    ifs.open(fn);
    if(!ifs.is_open()){
      return -1;
    }
    
    if (!reader.parse(ifs, root, false))
    {
        cerr << " JGEN::json_parse on file failed \n";
        return -2;
    }


    // root
    // 1. Get All Data Stored In 
    try {
        Json::Value::Members roots = root.getMemberNames();
        if (roots.size() <= 0) {
            // Error
            cerr << " No Class Object Found in json" << endl;
            return -3;
        }else{
            cout << " selecting to read the class of " << roots[0] << endl;
        }

        // only get the first;
        string corename = roots[0];
        if (root[corename].isNull()) {
            cerr << " Class Object is Null " << endl;
            return -4;
        }

        root = root[corename];
        if (root["defs"].isNull()){
            cerr << " Cannot find defs in the class object" << endl;
            return -5;
        }

        if(root["symbol_table"].isNull()){
            cerr << " Cannot find symbol_table in the class object" << endl;
            return -6;
        }

        if(root["type_table"].isNull()) {
            cerr << " Cannot find type_table in the class object" << endl;
            return -7;
        }
    }catch(std::exception e){
        cerr << "Exception" << endl;
        cerr << e.what();
    }
  }

  int Json_IR::read_string(const char * str){
    if(json_data == NULL){
      return -2;
    }
    if (!reader.parse(json_data, json_data + sizeof(json_data), root))
    {
	cerr << "json parse failed\n";        
	return -1;
    }
  }

  int Json_IR::open(const char * string1){
    if(string1 == NULL){
      return -2;
    }
    fn = string1;
    std::ifstream ifs;
    ifs.open(fn);
    if(!ifs.is_open()){
      return -1;
    }
    ifs.close();
    return 0;
  }

  Json::Value Json_IR::get_defs(){
    Json::Value val = root["defs"];
    return val;
  }

  Json::Value Json_IR::get_sym_tree(){
      return root["symbol_table"];
  }
  
  Json::Value Json_IR::get_type_tree(){
    return root["type_table"];
  }
  
}
