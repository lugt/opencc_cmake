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
    try{
    unsigned int count = root.size() - 1;
    cout << endl << " -----  ROOT level classes count : " << count << endl;
    for (unsigned int i = 0; i < count; ++i)
    {
        string name = root[i]["name"].asString();
        int salary = root[i]["salary"].asInt();
        cout << "name: " << name << " salary: " << salary << endl;
    }
    cout << "last msg: " << root[count].asString() << endl;
    cout << endl << endl;
    }catch(exception e){
      cout << "------ Exception Encountered -------" << endl;
      std::cout << e.what() << endl;
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

  int Json_IR::open(const char * fn){
    if(fn == NULL){
      return -2;
    }
    this->fn = fn;
    std::ifstream ifs;
    ifs.open(fn);
    if(!ifs.is_open()){
      return -1;
    }
    ifs.close();
    return 0;
  }

  Json::Value Json_IR::get_defs(){
    
  }

  Json::Value Json_IR::get_sym_tree(){
    
  }
  
  Json::Value Json_IR::get_type_tree(){
    
  }
  
}
