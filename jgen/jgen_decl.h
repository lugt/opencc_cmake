#ifndef OSPREY_JGEN_DECL_H
#define OSPREY_JGEN_DECL_H

#include <string>
#include <iostream>
#include "jgen_include.h"

namespace JGEN{
  class Json_IR_Decl{
   public:

    Json_IR_Decl(){}
    ~Json_IR_Decl(){}

    void init(void * val){};

    long long getFlag(){
      return 0;
    };
  };
}

#endif