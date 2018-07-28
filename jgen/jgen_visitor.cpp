//
// Created by xc5 on 27/7/2018.
//

#include "jgen_visitor.h"

namespace JGEN
{
    int JGEN_Visitor::visit_top_decl (Json_IR_Decl provider)
    {

        if(provider.getDeclKind () == JGEN_DECL_CLASS){
            provider.get_next_decl ();
            JGEN_ST st;
            st.createClass ();
        }

        // Find Child
        if(provider.hasChild () > 0){
            Json_IR_Decl child = provider.getFirstChild ();
            visit_decl(child);
        }
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