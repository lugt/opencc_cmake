//
// Created by xc5 on 29/7/2018.
//

#ifndef OSPREY_JGEN_BASE_DECL_H
#define OSPREY_JGEN_BASE_DECL_H

namespace JGEN {


class JGEN_IR_Decl{
 public:
  /**
   *
   */
  virtual int get_next_decl() = 0;

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
  virtual int getDeclKind()= 0;
  virtual const Json::Value &getRoot() const = 0;
  virtual void setRoot(const Json::Value &root)= 0;
  virtual const Json::Value &getDecl() const = 0;
  virtual void setDecl(const Json::Value &decl)= 0;
  virtual int getSymbol_json_id() const = 0;
  virtual void setSymbol_json_id(int symbol_json_id) = 0;
  virtual int getType_json_id() const = 0;
  virtual void setType_json_id(int type_json_id)= 0;
  virtual int getTag_json() const = 0;
  virtual void setTag_json(int tag_json)= 0;
  virtual int getKind() const = 0;
  virtual void setKind(int kind) = 0;
  virtual const string &getTag_name() const = 0;
  virtual void setTag_name(const string &tag_name) = 0;
  virtual int getChild_count() const = 0;
  virtual void setChild_count(int child_count) = 0;
  virtual JGEN_SymbolTree_Base * get_symbol_tree() = 0;
  virtual JGEN_Typetree_Base * get_type_tree() = 0;

};

}

#endif //OSPREY_JGEN_BASE_DECL_H
