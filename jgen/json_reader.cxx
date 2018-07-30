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

    Json_IR_Decl * Json_IR::get_top_decl ()
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
        JGEN_SymbolTree_Base::init(tree);
    }
    int Json_SymbolTree_Simple::next() {
        return JGEN_SymbolTree_Base::next();
    }
    unsigned long long Json_SymbolTree_Simple::getKind() {
        return JGEN_SymbolTree_Base::getKind();
    }
    std::string &Json_SymbolTree_Simple::getKindName() {
        return JGEN_SymbolTree_Base::getKindName();
    }
    unsigned long long Json_SymbolTree_Simple::getFlag() {
        return JGEN_SymbolTree_Base::getFlag();
    }
    int Json_SymbolTree_Simple::getJsonRefId() {
        return JGEN_SymbolTree_Base::getJsonRefId();
    }
    std::string &Json_SymbolTree_Simple::getJsonName() {
        return JGEN_SymbolTree_Base::getJsonName();
    }
    int Json_SymbolTree_Simple::getIdx() {
        return JGEN_SymbolTree_Base::getIdx();
    }
    void Json_SymbolTree_Simple::setTypeIdx(int idx) {
        JGEN_SymbolTree_Base::setTypeIdx(idx);
    }
    int Json_SymbolTree_Simple::gotoStId(unsigned int ir_sym_id) {
        // Goto Id, slowest doing
        if(_tree->size() > 0){
            // Goto IR_SYM_ID
        }
        return JGEN_SymbolTree_Base::gotoStId(ir_sym_id);
    }
}
