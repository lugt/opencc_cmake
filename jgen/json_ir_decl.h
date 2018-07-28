#ifndef OSPREY_JGEN_DECL_H
#define OSPREY_JGEN_DECL_H

#include <string>
#include <iostream>
#include "jgen_include.h"
#include <json/json.h>

using std::string;

namespace JGEN{
    /**
       *  Json IR Decl Interface
       * */
    class Json_IR_Decl{
     private:
       Json::Value root;
       Json::Value decl;
       int symbol_json_id;
       int type_json_id;
       int tag_json;
       int kind;
       string tag_name;
       int child_count;

     public:

      Json_IR_Decl(Json::Value & code_table, Json::Value & root);

      /**
       * Initilize the Provider with Json::Value
       * @param data
       * @return -1,-2,-3 = fail, 0 = ok
       */
      int init(void * data);

      /**
       *
       */
      int get_next_decl();

      /**
       *   check if have child (childnum)
       *   @return remainning child nums;
       */
      int hasChild();

      /**
       *  Returns a child
       */
      Json_IR_Decl * getFirstChild();


      /***
       *  Get the Kind of the Decl
       *  @return longlong JGEN_DECL_CLASS
       */
      int getDeclKind();


    };
}

#endif