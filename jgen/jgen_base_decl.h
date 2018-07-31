//
// Created by xc5 on 29/7/2018.
//

#ifndef OSPREY_JGEN_BASE_DECL_H
#define OSPREY_JGEN_BASE_DECL_H

#include <string>
#include <vector>

using std::string;

namespace JGEN {


class JGEN_Typetree_Base {

 public:

  // goto some type with an typetree internal Id
  virtual int gotoId(unsigned int type_id){};

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

};



class JGEN_SymbolTree_Base {

 public:

  virtual void init(void * tree) {};

  // Reading another node (next) (traverse)
  // @return whether there is one to be read(1), or none (0)
  virtual int next() {};

  // read Kind from Node
  virtual U64U getKind(){};

  // read Name from Node
  virtual std::string getKindName(){};

  // read Kind from Node
  virtual unsigned long long getFlag(){};

  // get DefId form Node
  virtual int getJsonRefId(){};

  // get (Symbol) Name from Node
  virtual std::string getJsonName(){};

  // retrieve the previously bound Idx
  virtual int getIdx(){};

  // bind Idx to the tree node
  virtual void setTypeIdx(int idx){};

  // bind Idx to the tree node
  virtual JGEN_SymbolTree_Base & getMemberFields(int idx){};

  virtual JGEN_SymbolTree_Base * getParent(){};

  virtual int gotoStId(unsigned int ir_sym_id){};
};


class JGEN_IR_Decl{
 public:

  /**
   *   check if have child (childnum)
   *   @return remainning child nums;
   */
  virtual int hasChild() = 0;

  /**
   *  Returns a child
   */
  virtual JGEN_IR_Decl * getChildAtPosition (unsigned int pos) = 0;


  /***
   *  Get the Kind of the Decl
   *  @return longlong JGEN_DECL_CLASS
   */
  virtual int getKind() const = 0;
  virtual int getChild_count() const = 0;

  virtual JGEN_SymbolTree_Base * get_symbol_tree() = 0;
  virtual JGEN_Typetree_Base * get_type_tree() = 0;

  virtual int getSymbolId() = 0;
  virtual int getTypeId() = 0;

};

}

#endif //OSPREY_JGEN_BASE_DECL_H
