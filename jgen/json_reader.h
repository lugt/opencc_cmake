/**
 * Json AST Reading Base Class Declaration
 * Author: Jason Lu : lu.gt@163.com
 * Version : V0.1 
 * Usage:
 *  1. Instantiate the JGEN::Json_IR class,
 *  2. JsonIR::open (file_name)
 *  3. JsonIR::read ()
 ***/

#ifndef JSON_READER_H_
#define JSON_READER_H_

#include <json/json.h>
#include <map>
#include "json_ir_decl.h"
#include "jgen_type.h"
#include "jgen_st.h"
#include "jgen_base_decl.h"

extern int JSON_READING_STATE;

namespace JGEN {


    class Json_MemberFields {
        void init(Json::Value &val);

        int next();

        std::string getName();

        int getIdx();

        unsigned long long getKind();

        unsigned long long getFlag();
    };

    class Json_Global_ST {
        void init(Json::Value &val);

        int next();

        std::string getName();

        int getIdx();

        unsigned long long getKind();

        unsigned long long getFlag();
    };

    class Json_Method_Stmt_Tree {
        void init(Json::Value &val);
    };

    class Json_Global_Method {
        void init(Json::Value &val);

        int next();

        std::string getName();

        int getIdx();

        unsigned long long getKind();

        unsigned long long getFlag();

        Json_Method_Stmt_Tree getStmt();
    };



    class Json_IR {
    private:
        Json::Reader reader;
        Json::Value root;
        const char *fn;

    public:

        Json_IR(){};

        int read();

        int read_string(const char *str);

        int open(const char *fn);

        Json::Value get_defs();

        Json::Value get_type_tree();

        Json::Value get_sym_tree();

        JGEN_IR_Decl * get_top_decl ();

      bool isNull();
    };

    class Json_Typetree_Simple : public JGEN_Typetree_Base {

    public:

        Json::Value * _tree;
        int flag;
        int statics;
        int count;

        Json_Typetree_Simple() {
            flag = 0;
            _tree = nullptr;
            statics = 0;
            count = 0;
        }

        Json_Typetree_Simple(Json::Value & val) {
            flag = 0;
            _tree = nullptr;
            statics = 0;
            count = 0;
            init(val);
        }

        void init(Json::Value &tree);

// Reading another node (next) (traverse)
// @return whether there is one to be read(1), or none (0)
        int next() override;

// read Kind from Node
        unsigned long long getKind() override;

// read Name from Node
        std::string &getKindName() override;

// read Kind from Node
        unsigned long long getFlag() override;

// get DefId form Node
        int getJsonRefId() override ;

// get (Symbol) Name from Node
        std::string &getJsonName() override;

// retrieve the previously bound Idx
        int getIdx() override;

// bind Idx to the tree node
        void setTypeIdx(int idx) override ;

// bind Idx to the tree node
//      Json_MemberFields &getMemberFields(int idx) override ;

    };

    class Json_SymbolTree_Simple : public JGEN_SymbolTree_Base {

     public:

      Json::Value * _tree;
      int flag;
      int statics;
      int count;
      std::map<int, Json::Value *> internalIdValMap;
      Json::Value * current;

      Json_SymbolTree_Simple() {
          flag = 0;
          _tree = nullptr;
          statics = 0;
          count = 0;
          _tree = nullptr;
      }

      Json_SymbolTree_Simple(Json::Value & symtree) {
          flag = 0;
          _tree = nullptr;
          statics = 0;
          count = 0;
          init((void *) & symtree);
      }

      void init(void * tree) override ;

    // Reading another node (next) (traverse)
    // @return whether there is one to be read(1), or none (0)
      int next() override;

    // read Kind from Node
      unsigned long long getKind() override;

    // read Name from Node
      std::string &getKindName() override;

    // read Kind from Node
      unsigned long long getFlag() override;

    // get DefId form Node
      int getJsonRefId() override ;

    // get (Symbol) Name from Node
      std::string &getJsonName() override;

    // retrieve the previously bound Idx
      int getIdx() override;

    // bind Idx to the tree node
      void setTypeIdx(int idx) override ;

    // bind Idx to the tree node
    //      Json_MemberFields &getMemberFields(int idx) override ;
      int gotoStId(unsigned int ir_sym_id) override;
    };


}


#endif
