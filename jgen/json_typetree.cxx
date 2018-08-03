//
// Created by xc5 on 3/8/2018.
//

#include "json_typetree.h"

namespace JGEN{

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
unsigned long long Json_Typetree_Simple::getKind(U32U jIndex) {

};

// read Name from Node
std::string &Json_Typetree_Simple::getKindName(U32U jIndex) {

};

// read Kind from Node
unsigned long long Json_Typetree_Simple::getFlag(U32U jIndex) {

};

// get DefId form Node
int Json_Typetree_Simple::getJsonRefId(U32U jIndex) {

};

// Json_Typetree_Simple::get (Symbol) Name from Node
std::string &Json_Typetree_Simple::getNameString(U32U jIndex) {

};

// retrieve the previously bound Idx
int Json_Typetree_Simple::getIdx(U32U jIndex) {

};

// bind Idx to the tree node
void Json_Typetree_Simple::setTypeIdx(int idx) {

};

}