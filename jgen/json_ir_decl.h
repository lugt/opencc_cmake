#ifndef OSPREY_JGEN_DECL_H
#define OSPREY_JGEN_DECL_H

#include <string>
#include <iostream>
#include "jgen_include.h"

namespace JGEN{
    /**
       *  Json IR Decl Interface
       * */
    class Json_IR_Decl{
     public:
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
      Json_IR_Decl getFirstChild();


      /***
       *  Get the Kind of the Decl
       *  @return longlong JGEN_DECL_CLASS
       */
      long long getDeclKind();
    };
}

#endif