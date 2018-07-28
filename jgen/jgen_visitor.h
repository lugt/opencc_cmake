//
// Created by xc5 on 27/7/2018.
//

#ifndef OSPREY_JGEN_VISITOR_H
#define OSPREY_JGEN_VISITOR_H

#include "json_ir_decl.h"
#include "jgen_include.h"
#include "jgen_st.h"

namespace JGEN{
    class JGEN_Visitor {
     private:
      Json_IR_Decl * parent_decl;
      Json_IR_Decl * now_decl;

     public:

      JGEN_Visitor(){};
      ~JGEN_Visitor(){};

      int visit_top_decl(Json_IR_Decl provider);

      int visit_decl(Json_IR_Decl provider);

      JGEN_ST * visit_class(Json_IR_Decl & provider);

    };
}

#endif //OSPREY_JGEN_VISITOR_H
