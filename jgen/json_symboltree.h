//
// Created by Jason Lu on 3/8/2018.
//

#ifndef OSPREY_JSON_SYMBOLTREE_H
#define OSPREY_JSON_SYMBOLTREE_H

#include "jgen_include.h"
#include "jgen_base_decl.h"
#include <json/json.h>

namespace JGEN {


class Json_SymbolTree_Simple : public JGEN_SymbolTree_Base {

 public:

  Json::Value *_tree;
  Json::Value *_currentptr;
  int _currentId;

  Json_SymbolTree_Simple() {
    _tree = nullptr;
    _currentId = 0;
    _currentptr = nullptr;
  }

  Json_SymbolTree_Simple(Json::Value &symtree) {
    // Temporarilly set to nullptr, later overridden by init(symtree)
    _tree = nullptr;
    _currentId = 0;
    _currentptr = nullptr;
    init((void *) &symtree);
  }

  void init(void *tree) override;

  // read Kind from Node
  U64U getKind(U32U pos) override;
  // read Name from Node
  std::string getKindName(U32U pos) override;
  // read Kind from Node
  U64U getFlag(U32U pos) override;
  // get DefId form Node
  int getJsonRefId(U32U pos) override;
  // get (Symbol) Name from Node
  std::string getJsonName(U32U pos) override;
  // retrieve the previously bound Idx
  int getIdx(U32U pos) override;
  // bind Idx to the tree node
  void setTypeIdx(U32U pos, int idx) override;
  // bind Idx to the tree node
  //      Json_MemberFields &getMemberFields(int idx) override ;
  int gotoStId(U32U pos) const;

  bool isPublic (U32U jIndex)
  {
    return (getFlag(jIndex) & JGEN_ST_FLAG_MASK_PUBLIC) > 0;
  }
  bool isWeak (U32U jIndex)
  {
    return (getFlag(jIndex) & JGEN_ST_FLAG_MASK_WEAK) > 0;
  }
  bool isConstructor (U32U jIndex) const override;
  string getNameString(U32U jIndex) override;
  void setTypeIdx(U32U jIndex) override;
  JGEN_SymbolTree_Base &getMemberFields(U32U jIndex) override;
  JGEN_SymbolTree_Base *getParent(U32U jIndex) override;
  bool isPureVFunc (U32U jIndex) const override;
  bool isMethodOfClass (U32U jIndex) const override;
  int get_method_base_type (U32U jIndex) const override;
  bool isContextNamespace (U32U jIndex) const override;
  bool isContextRecord (U32U jIndex) const override;
  bool isLangSpecific (U32U jIndex) const override;
  bool isReallyExtern (U32U jIndex) const override;
  bool isNoThrow (U32U jIndex) const override;

};

}


#endif //OSPREY_JSON_SYMBOLTREE_H
