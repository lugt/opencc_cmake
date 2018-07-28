//
// Created by xc5 on 27/7/2018.
//

#include "jgen_type.h"
#include <string>
using std::string;

namespace JGEN
{
    std::string  JGEN_TY::type_str;
    long long  JGEN_TY::kind;
    long long  JGEN_TY::flag;
    TY_IDX  JGEN_TY::idx;
    TYPE_ID  JGEN_TY::mtype;
    INT64  JGEN_TY::tsize;
    BOOL  JGEN_TY::variable_size;
    std::string  JGEN_TY::kname;
    JGEN_TY *JGEN_TY::return_val;
    vector<JGEN_TY>  JGEN_TY::args;

    void
    JGEN_TY::init (std::string &name_, long long kind_, long long flag_, INT64 tsize_, BOOL isLengthVariable_, string kname_, JGEN_TY *retval)
    {
        type_str = name_;
        kind = kind_;
        flag = flag_;
        tsize = tsize_;
        variable_size = isLengthVariable_;
        kname = kname_;
        return_val = retval;
    }


}