/***
 * Json AST Reading Base Class Declaration
 * Author: Jason Lu : lu.gt@163.com
 * Version : V0.1 
 * Usage:
 *  1. Instantiate the JGEN::Json_IR class,
 *  2. JsonIR::open (file_name)
 *  3. JsonIR::read ()
 ***/
#include "json_reader.h"
#include "jgen_global.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <algorithm>
#include <string>


int JSON_READING_STATE = 0;

namespace JGEN {

    using namespace std;

    static const char *json_data = "data";

    int Json_IR::read() {
        std::ifstream ifs;
        ifs.open(fn);
        if (!ifs.is_open()) {
            return -1;
        }

        if (!reader.parse(ifs, root, false)) {
            cerr << " JGEN::json_parse on file failed \n";
            return -2;
        }


        // root
        // 1. Get All Data Stored In
        try {
            Json::Value::Members roots = root.getMemberNames();
            if (roots.empty()) {
                // Error
                cerr << "-- [FATAL ERROR] [Json_Reader] No Class Object Found in json" << endl;
                return -3;
            } else {
                cout << "-- [INFO] [Json_Reader] selecting to read the class : (" << roots[0] << ")" << endl;
            }

            // only get the first;
            string corename = roots[0];
            if (root[corename].isNull()) {
                cerr << "-- [Json_Reader] Class Object is Null " << endl;
                return -4;
            }

            root = root[corename]; //TODO:
            if (root["code_table"].isNull()) {
                cerr << "-- [Json_Reader] Cannot find defs in the class object" << endl;
                return -5;
            }

            if (root["symbol_table"].isNull()) {
                cerr << "-- [Json_Reader]  Cannot find symbol_table in the class object" << endl;
                return -6;
            }

            if (root["type_table"].isNull()) {
                cerr << "-- [Json_Reader]  Cannot find type_table in the class object" << endl;
                return -7;
            }
            return 0;
        } catch (std::exception & e) {
            cerr << "-- [Json_Reader] Exception" << endl;
            cerr << e.what();
            return -5;
        }
    }

    int Json_IR::read_string(const char *str) {
        if (json_data == nullptr) {
            return -2;
        }
        if (!reader.parse(json_data, json_data + strlen(json_data), root)) {
            cerr << "-- [Json_Reader] json parse failed\n";
            return -1;
        }
        return 0;
    }

    int Json_IR::open(const char *string1) {
        if (string1 == nullptr) {
            return -2;
        }
        fn = string1;
        std::ifstream ifs;
        ifs.open(fn);
        if (!ifs.is_open()) {
            return -1;
        }
        ifs.close();
        return 0;
    }

    Json::Value Json_IR::get_defs() {
        Json::Value val = root["code_table"]["defs"];
        return val;
    }

    Json::Value Json_IR::get_sym_tree() {
        return root["symbol_table"];
    }

    Json::Value Json_IR::get_type_tree() {
        return root["type_table"];
    }

    JGEN_IR_Decl * Json_IR::get_top_decl ()
    {
        return new Json_IR_Decl (root["code_table"], root);
    }

    bool Json_IR::isNull() {
      return root.isNull();
    }

    void Json_Typetree_Simple::init(Json::Value &tree) {
        // Take whatever needed form tree
        // Mark the length, and current cursot to zero.
        _tree = &tree;
    };

    // Reading another node (next) (traverse)
    // @return whether there is one to be read(1), or none (0)
    int Json_Typetree_Simple::next() {
        // Move cursor
    };

    // read Kind from Node
    unsigned long long Json_Typetree_Simple::getKind() {

    };

    // read Name from Node
    std::string &Json_Typetree_Simple::getKindName() {

    };

    // read Kind from Node
    unsigned long long Json_Typetree_Simple::getFlag() {

    };

    // get DefId form Node
    int Json_Typetree_Simple::getJsonRefId() {

    };

    // Json_Typetree_Simple::get (Symbol) Name from Node
    std::string &Json_Typetree_Simple::getJsonName() {

    };

    // retrieve the previously bound Idx
    int Json_Typetree_Simple::getIdx() {

    };

    // bind Idx to the tree node
    void Json_Typetree_Simple::setTypeIdx(int idx) {

    };

    void Json_SymbolTree_Simple::init(void *tree) {
      int i;
      this->_tree = (Json::Value *) tree;
      // length
      count = this->_tree->size();
      for (i = 0; i < count; i++) {
        Json::Value *decl = (new Json::Value(Json::nullValue));
        Json::Value val = (*_tree)[i];
        decl->copy(val);
        internalIdValMap.insert(std::make_pair(100 + i, decl));
      }
    }

    int Json_SymbolTree_Simple::next() {
      if(currentId > 0){
        return gotoStId(static_cast<unsigned int>(currentId + 1));
      }
      return -6;
    }

    U64U json_kind_list[] = {1, 2, 16, 4};
    U64U internal_kind_list[] = {JGEN_ST_PACKAGE, JGEN_ST_CLASS, JGEN_ST_METHOD, JGEN_ST_VAR};

    unsigned long long Json_SymbolTree_Simple::getKind() {
      U64U jsonkind = 0;
      if(current != nullptr){
        jsonkind = (*current)["kind"].asUInt64();
      }else if(_tree != nullptr){
        jsonkind = (*_tree)["kind"].asUInt64();
      }

      if(jsonkind == 0)  return 0;

      // Low efficiency method? map better?
      {
        for(int i = 0; i < sizeof(json_kind_list) ; i++){
          if(json_kind_list[i] == jsonkind)
          return internal_kind_list[i];
        }
      }
      return jsonkind;
    }

    std::string Json_SymbolTree_Simple::getKindName() {
      if(current != nullptr){
        return (*current)["kindname"].asString();
      }else if(_tree != nullptr){
        return (*_tree)["kindname"].asString();
      }
      return *(new string("[JSON_Symbol_TREE]"));
    }

    unsigned long long Json_SymbolTree_Simple::getFlag() {
      if(current != nullptr){
        return (*current)["flag"].asUInt64();
      }else if(_tree != nullptr){
        return (*_tree)["flag"].asUInt64();
      }
      return 0;
    }

    int Json_SymbolTree_Simple::getJsonRefId() {
      return currentId;
    }

    std::string Json_SymbolTree_Simple::getJsonName() {
        if(current != nullptr){
          return (*current)["name"].asString();
        }else if(_tree != nullptr){
          return (*_tree)["name"].asString();
        }
        return *(new string("[JSON_Symbol_TREE]"));
    }

    int Json_SymbolTree_Simple::getIdx() {
        return JGEN_SymbolTree_Base::getIdx();
    }

    void Json_SymbolTree_Simple::setTypeIdx(int idx) {
        JGEN_SymbolTree_Base::setTypeIdx(idx);
    }

    int Json_SymbolTree_Simple::gotoStId(unsigned int ir_sym_id) {
        // indexed doing
        if(count > 0){
            if(this->internalIdValMap.find((int) ir_sym_id) != this->internalIdValMap.end()) {
                Json::Value * ptr = new Json::Value(* (this->internalIdValMap.at((int) ir_sym_id)));
                current = ptr;
                return 0;
            }
            logger("-- JSON_ERROR : [Json_SymbolTree_Simple][gotoStId] cannot find such symId in map.");
            return -2;
        }
        logger("-- JSON_ERROR : [Json_SymbolTree_Simple][gotoStId] count <= 0 ");
        return -1;
    }
}
