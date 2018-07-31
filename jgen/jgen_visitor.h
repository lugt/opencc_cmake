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
      JGEN_IR_Decl * parent_decl;
      JGEN_IR_Decl * now_decl;

     public:

      JGEN_Visitor(){};
      ~JGEN_Visitor(){};

      int visit_top_decl(JGEN_IR_Decl & provider);
      int visit_decl(JGEN_IR_Decl & provider);

      void visit_first_round (JGEN_IR_Decl &provider);
      void visit_second_round (JGEN_IR_Decl &decl);
      void visit_child_round (JGEN_IR_Decl &decl);
    };
}

#endif //OSPREY_JGEN_VISITOR_H
