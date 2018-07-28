//
// Created by xc5 on 27/7/2018.
//

#include "json_ir_decl.h"
#include "json_reader.h"

namespace JGEN
{
    int JGEN::Json_IR_Decl::init (void *data)
    {
      return 0;
    }
    int JGEN::Json_IR_Decl::get_next_decl ()
    {
      return 0;
    }
    int JGEN::Json_IR_Decl::hasChild ()
    {
      return 1;
    }
    Json_IR_Decl JGEN::Json_IR_Decl::getFirstChild ()
    {
      return nullptr;
    }
    long long JGEN::Json_IR_Decl::getDeclKind ()
    {
      return 0;
    }

}