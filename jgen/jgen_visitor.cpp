//
// Created by xc5 on 27/7/2018.
//

#include "jgen_visitor.h"

namespace JGEN
{
    int JGEN_Visitor::visit_top_decl (Json_IR_Decl provider)
    {
        // Find Child
        return 0;
    }
    int JGEN_Visitor::visit_decl (Json_IR_Decl provider)
    {
        // If it's a class,
        return 0;
    }

    JGEN_ST * JGEN_Visitor::visit_class (Json_IR_Decl &provider)
    {
        JGEN_ST st;
        return &st;
    }
}