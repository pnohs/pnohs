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

/**
 * different types of parameters
 */
enum param_type {
    integer_tp, // type of integer (int) parameter
    float_tp, // type of double precision float (float) parameter
    boolean_tp, // type of boolean (bool) parameter
};

// the metadata of model parameter
struct param_meta {
    const param_type type; // type of parameter
    const params_key key; // name or key of parameter
    const param_const max; // maximum value of this parameter
    const param_const min; // minimal value of this parameter
};

#endif //PNOHS_MODEL_PARAMS_DEF_H
