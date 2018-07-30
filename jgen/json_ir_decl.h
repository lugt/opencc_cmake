#ifndef OSPREY_JGEN_DECL_H
#define OSPREY_JGEN_DECL_H

#include <string>
#include <iostream>
#include "jgen_include.h"
#include "jgen_st.h"
#include "jgen_type.h"
#include <json/json.h>
#include "jgen_base_decl.h"

using std::string;

namespace JGEN{

    /**
       *  Json IR Decl Interface
       * */
    class Json_IR_Decl : public JGEN_IR_Decl{
     private:
       Json::Value root;
       Json::Value decl;
       int symbol_json_id;
       int type_json_id;
       int tag_json;
       int kind;
       string tag_name;
       int child_count;

     public:

      Json_IR_Decl(Json::Value & code_table, Json::Value & root);

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
      Json_IR_Decl * getChildAtPosition (unsigned int pos);


      /***
       *  Get the Kind of the Decl
       *  @return longlong JGEN_DECL_CLASS
       */
      int getDeclKind();
      const Json::Value &getRoot() const;
      void setRoot(const Json::Value &root);
      const Json::Value &getDecl() const;
      void setDecl(const Json::Value &decl);
      int getSymbol_json_id() const;
      void setSymbol_json_id(int symbol_json_id);
      int getType_json_id() const;
      void setType_json_id(int type_json_id);
      int getTag_json() const;
      void setTag_json(int tag_json);
      int getKind() const;
      void setKind(int kind);
      const string &getTag_name() const;
      void setTag_name(const string &tag_name);
      int getChild_count() const;
      void setChild_count(int child_count);
      JGEN_SymbolTree_Base * get_symbol_tree();
      JGEN_Typetree_Base * get_type_tree();

    };
}

#endif