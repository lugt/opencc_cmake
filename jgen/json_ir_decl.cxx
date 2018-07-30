//
// Created by xc5 on 27/7/2018.
//

#include "json_ir_decl.h"
#include "json_reader.h"
#include "jgen_include.h"
#include "jgen_global.h"

namespace JGEN
{

Json_IR_Decl::Json_IR_Decl (Json::Value &code_table_, Json::Value &root_)
{
  root = root_;
  decl = code_table_;

  child_count = 0;

  tag_json = decl["tag"].asInt ();
  tag_name = decl["tag_name"].asString ();

  switch (tag_json)
    {
  case 3: // CLASSDEF
    kind = JGEN_DECL_CLASS;
      if (!decl["defs"].isNull ())
        {
          child_count = decl["defs"].size ();
        }
      break;
  case 4: // METHODDEF
    kind = JGEN_DECL_METHOD;
      if (!decl["body"].isNull ())
        {
          child_count = 1;
        }
      break;
  case 7:
    kind = JGEN_DECL_BLOCK;
    if (!decl["body"].isNull ())
      {
        child_count = 1;
      }
    break;
  case 20:// EXEC
      kind = JGEN_DECL_STMT;
      break;
  case 37://IDENT
      kind = JGEN_DECL_OPERATOR;
  case 26://APPLY
      kind = JGEN_DECL_OPERATOR;
      break;
  default:kind = JGEN_DECL_UNKNOWN_KIND;
      break;
    }
  if (decl["type"].isInt ())
  {
      type_json_id = decl["type"].asInt ();
  }
  if (decl["sym"].isInt ())
  {
      symbol_json_id = decl["sym"].asInt ();
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
Json_IR_Decl *Json_IR_Decl::getChildAtPosition (unsigned int pos)
{

  if (child_count <= pos)
    {
      logger ("");
      return nullptr;
    }

  if (kind == JGEN_DECL_CLASS)
    {
      if (!decl["defs"].empty())
        {
          return (new Json_IR_Decl (decl["defs"][0], root));
        }
      return 0;
    }
  else if (kind == JGEN_DECL_METHOD)
    {
      if (!decl["body"].isNull ())
        {
          return (new Json_IR_Decl (decl["body"], root));
        }
      return 0;
    }
  else if (kind == JGEN_DECL_BLOCK)
    {
      if (!decl["stats"].isNull ())
        {
          return (new Json_IR_Decl (decl["stats"], root));
        }
      return 0;
    }

  return nullptr;
}
int JGEN::Json_IR_Decl::getDeclKind ()
{
  return kind;
}
const Json::Value &Json_IR_Decl::getRoot() const {
  return root;
}
void Json_IR_Decl::setRoot(const Json::Value &root) {
  Json_IR_Decl::root = root;
}
const Json::Value &Json_IR_Decl::getDecl() const {
  return decl;
}
void Json_IR_Decl::setDecl(const Json::Value &decl) {
  Json_IR_Decl::decl = decl;
}
int Json_IR_Decl::getSymbol_json_id() const {
  return symbol_json_id;
}
void Json_IR_Decl::setSymbol_json_id(int symbol_json_id) {
  Json_IR_Decl::symbol_json_id = symbol_json_id;
}
int Json_IR_Decl::getType_json_id() const {
  return type_json_id;
}
void Json_IR_Decl::setType_json_id(int type_json_id) {
  Json_IR_Decl::type_json_id = type_json_id;
}
int Json_IR_Decl::getTag_json() const {
  return tag_json;
}
void Json_IR_Decl::setTag_json(int tag_json) {
  Json_IR_Decl::tag_json = tag_json;
}
int Json_IR_Decl::getKind() const {
  return kind;
}
void Json_IR_Decl::setKind(int kind) {
  Json_IR_Decl::kind = kind;
}
const string &Json_IR_Decl::getTag_name() const {
  return tag_name;
}
void Json_IR_Decl::setTag_name(const string &tag_name) {
  Json_IR_Decl::tag_name = tag_name;
}
int Json_IR_Decl::getChild_count() const {
  return child_count;
}
void Json_IR_Decl::setChild_count(int child_count) {
  Json_IR_Decl::child_count = child_count;
}

JGEN_SymbolTree_Base *Json_IR_Decl::get_symbol_tree() {
  JGEN_SymbolTree_Base * sym = new JGEN_SymbolTree_Base();
  sym->init();
  return nullptr;
}
JGEN_Typetree_Base *Json_IR_Decl::get_type_tree() {
  return nullptr;
}

}