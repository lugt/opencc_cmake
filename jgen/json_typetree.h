//
// Created by xc5 on 3/8/2018.
//

#ifndef OSPREY_JSON_TYPETREE_H
#define OSPREY_JSON_TYPETREE_H

#include <json/json.h>
#include "jgen_base_decl.h"
#include "jgen_include.h"

namespace JGEN{

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

};

}

#endif //OSPREY_JSON_TYPETREE_H
