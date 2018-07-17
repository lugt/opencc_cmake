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
    };

    class Json_Typetree {

    public:

        Json_Typetree(){};

        Json_Typetree(Json::Value & val){
            init(val);
        }

        virtual ~Json_Typetree(){}

        virtual void init(Json::Value &tree) {};

        // Reading another node (next) (traverse)
        // @return whether there is one to be read(1), or none (0)
        virtual int next() {};

        // read Kind from Node
        virtual unsigned long long getKind(){};

        // read Name from Node
        virtual std::string &getKindName(){};

        // read Kind from Node
        virtual unsigned long long getFlag(){};

        // get DefId form Node
        virtual int getJsonRefId(){};

        // get (Symbol) Name from Node
        virtual std::string &getJsonName(){};

        // retrieve the previously bound Idx
        virtual int getIdx(){};

        // bind Idx to the tree node
        virtual void setTypeIdx(int idx){};

        // bind Idx to the tree node
        virtual Json_MemberFields &getMemberFields(int idx){};
    };

    class Json_Typetree_Simple : public Json_Typetree {

    public:

        Json::Value val;
        int flag;
        int statics;


        Json_Typetree_Simple() {}

        Json_Typetree_Simple(Json::Value & val) {
            init(val);
        }

        void init(Json::Value &tree) override ;

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
        Json_MemberFields &getMemberFields(int idx) override ;

    };


}


#endif
