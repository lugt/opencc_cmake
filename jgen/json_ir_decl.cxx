//
// Created by xc5 on 27/7/2018.
//

#include "json_ir_decl.h"
#include "json_reader.h"

namespace JGEN
{

    Json_IR_Decl::Json_IR_Decl (Json::Value & code_table_, Json::Value & root_)
    {
      root = root_;
      decl = code_table_;

      child_count = 0;

      tag_json = decl["tag"].asInt();
      tag_name = decl["tag_name"].asString ();

      switch (tag_json){
        case 3: // CLASSDEF
          kind = JGEN_DECL_CLASS;
          if(!decl["defs"].isNull ())
          {
              child_count = decl["defs"].size ();
          }
          break;
        case 4: // CLASSDEF
          kind = JGEN_DECL_METHOD;
          break;
        default:
          kind = JGEN_DECL_UNKNOWN_KIND;
          break;
      }
      if(decl["type"].isInt ())
      {
          type_json_id = decl["type"].asInt ();
      }
      if(decl["sym"].isInt ())  {
          symbol_json_id = decl["sym"].asInt();
      }
    }

    int JGEN::Json_IR_Decl::get_next_decl ()
    {
      return 0;
    }
    int JGEN::Json_IR_Decl::hasChild ()
    {
      return child_count;
    }
    Json_IR_Decl * Json_IR_Decl::getFirstChild ()
    {
      if(kind == JGEN_DECL_CLASS){
          if(decl["defs"].size () > 0){
              return (new Json_IR_Decl(decl["defs"][0], root));
          }
      }
      return nullptr;
    }
    int JGEN::Json_IR_Decl::getDeclKind ()
    {
      return kind;
    }

}