//
// Created by genshen on 8/2/18.
//

#ifndef PNOHS_MODEL_PARAMS_DEF_H
#define PNOHS_MODEL_PARAMS_DEF_H

#include <string>

typedef int param_tp_integer;
typedef double param_tp_float;
typedef bool param_tp_boolean;

union param_union {
    param_tp_float float_param;
    param_tp_integer integer_param;
    param_tp_boolean boolean_param;
};

// this variable not change when it is assigned, use as model params.
typedef param_union param_const;

// type used for status variable (e.g. the variable of last time step).
typedef param_union var_status_double;

// type used for initial status variable.
typedef param_union init_status_double;

// type used for temporary variable, local variable.
typedef param_union var_local_double;

typedef param_const _type_param;

typedef std::string params_key;


#endif //PNOHS_MODEL_PARAMS_DEF_H
