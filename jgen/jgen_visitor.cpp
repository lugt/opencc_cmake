//
// Created by xc5 on 27/7/2018.
//

#include <sstream>
#include "jgen_visitor.h"
#include "json_ir_decl.h"
#include "jgen_global.h"
#include "json_reader.h"
using std::stringstream;

namespace JGEN
{
    int JGEN_Visitor::visit_top_decl (JGEN_IR_Decl & provider)
    {
        // STAGE-PARSING1
        visit_first_round(provider);
        visit_second_round(provider);
        visit_child_round(provider);
        return 0;
    }
    int JGEN_Visitor::visit_decl (JGEN_IR_Decl provider)
    {
        // If it's a class,
        visit_first_round(provider);
        visit_second_round(provider);
        visit_child_round(provider);
        return 0;
    }


    void JGEN_Visitor::visit_first_round (JGEN_IR_Decl &provider)
    {
        JGEN_SymbolTree_Base * symtree = nullptr;
        JGEN_Typetree_Base * typetree = nullptr;
        switch(provider.getDeclKind ()){
            case JGEN_DECL_CLASS:
              logger("-- [Json_Visitor]:: ***  visiting a class  defition.  ***");
              symtree = provider.get_symbol_tree();
              typetree = provider.get_type_tree();
              JGEN_ST::getST(symtree, provider.getSymbol_json_id());
              // Preserve symbol_json_id <--> ST_IDX
              break;
            case JGEN_DECL_METHOD:
              logger("-- [Json_Visitor]:: ***  visiting a method defition.  ***");
              symtree = provider.get_symbol_tree();
              typetree = provider.get_type_tree();
              JGEN_ST::getST(symtree, provider.getSymbol_json_id());
              break;
            case JGEN_DECL_VAR:
              logger("-- [Json_Visitor]:: ***  visiting a var    defition.  ***");
              break;
            default:
              // UNKNOWN
              logger("-- [Jgen_Visitor]:: *** visiting unknown (kind) of provider decl. ***");
              logger("-- [Jgen_Visitor]:: *** kind : " + int2str(provider.getDeclKind()) + " ***");
            return ;
        }
    }

    void JGEN_Visitor::visit_second_round (JGEN_IR_Decl &provider)
    {
      if(provider.getDeclKind () == JGEN_DECL_CLASS){

      }
    }
    void JGEN_Visitor::visit_child_round (JGEN_IR_Decl & provider)
    {
        unsigned int position = 0;
        for(position = 0; position < provider.hasChild () && position <= INT_MAX ; position++)
        {
            JGEN_IR_Decl * decl = provider.getChildAtPosition (position);
            if (decl != nullptr){
                visit_decl (*decl);
            }
        }
    }
}