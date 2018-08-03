//
// Created by xc5 on 27/7/2018.
//

#include "jgen_type.h"
#include <string>
#include <map>
using std::string;

namespace JGEN
{


    TY_IDX JGEN_TY::getExistTypeIdx(U32U jTypeIndex) {
        if(generatedType.find(jTypeIndex) != generatedType.end()){
            return *(generatedType.find(jTypeIndex));
        }
        return 0;
    }

}