//
// Created by xc5 on 3/8/2018.
//

#include "json_symboltree.h"
#include "jgen_global.h"

namespace JGEN{

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

int Json_SymbolTree_Simple::getIdx(U32U index) {
  return 0;
}

void Json_SymbolTree_Simple::setTypeIdx(U32U jIndex, int idx) {
  // to Cache
}

int Json_SymbolTree_Simple::gotoStId(U32U ir_sym_id) const{
  // indexed doing
  if(this->internalIdValMap.find((int) ir_sym_id) != this->internalIdValMap.end()) {
    Json::Value * ptr = new Json::Value(* (this->internalIdValMap.at((int) ir_sym_id)));
    current = ptr;
    return 0;
  }
  logger("-- JSON_ERROR : [Json_SymbolTree_Simple][gotoStId] cannot find such symId in map.");
  return -2;
}

string Json_SymbolTree_Simple::getNameString(U32U jIndex) {
  return std::string();
}
void Json_SymbolTree_Simple::setTypeIdx(U32U jIndex) {

}
JGEN_SymbolTree_Base &Json_SymbolTree_Simple::getMemberFields(U32U jIndex) {
  return <#initializer#>;
}
JGEN_SymbolTree_Base *Json_SymbolTree_Simple::getParent(U32U jIndex) {
  return nullptr;
}
U64U Json_SymbolTree_Simple::getKind(U32U pos) {
  return 0;
}
std::string Json_SymbolTree_Simple::getKindName(U32U pos) {
  gotoStId(pos);
  if(current != nullptr){
    return (*current)["kindname"].asString();
  }else if(_tree != nullptr){
    return (*_tree)["kindname"].asString();
  }
  return *(new string("[JSON_Symbol_TREE]"));
}
U64U Json_SymbolTree_Simple::getFlag(U32U pos) {
  gotoStId(pos);
  return 0;
}
int Json_SymbolTree_Simple::getJsonRefId(U32U pos) {
  gotoStId(pos);
  return 0;
}
std::string Json_SymbolTree_Simple::getJsonName(U32U pos) {
  gotoStId(pos);
  return std::string();
}
int Json_SymbolTree_Simple::getIdx(U32U pos) {
  gotoStId(pos);
  return 0;
}
void Json_SymbolTree_Simple::setTypeIdx(U32U pos, int idx) const {
  gotoStId(pos);
}
bool Json_SymbolTree_Simple::isConstructor(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}
bool Json_SymbolTree_Simple::isPureVFunc(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}
bool Json_SymbolTree_Simple::isMethodOfClass(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}
int Json_SymbolTree_Simple::get_method_base_type(U32U jIndex) const {
  gotoStId(jIndex);
  return 0;
}
bool Json_SymbolTree_Simple::isContextNamespace(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}
bool Json_SymbolTree_Simple::isContextRecord(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}
bool Json_SymbolTree_Simple::isLangSpecific(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}
bool Json_SymbolTree_Simple::isReallyExtern(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}
bool Json_SymbolTree_Simple::isNoThrow(U32U jIndex) const {
  gotoStId(jIndex);
  return false;
}

}