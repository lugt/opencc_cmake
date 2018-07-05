/**
 * Json AST Reading Base Class Declaration
 * Author: Jason Lu : lu.gt@163.com
 * Version : V0.1 
 * Usage:
 *  1. Instantiate the JGEN::Json_IR class,
 *  2. JsonIR::open (file_name)
 *  3. JsonIR::read ()
 ***/

#ifndef JSON_READER_H_
#define JSON_READER_H_ 

#include <json/json.h>

extern int JSON_READING_STATE;

namespace JGEN{

class Json_IR{
private:
  Json::Reader reader;
  Json::Value root;
  const char * fn;

public:
  int read();
  int read_string(const char *str);
  int open(const char * fn);

};

}


#endif
