//
// Created by genshen on 8/2/18.
//

#ifndef PNOHS_MODEL_PARAMS_DEF_H
#define PNOHS_MODEL_PARAMS_DEF_H

#include <string>

// type used for status variable (e.g. the variable of last time step).
typedef double var_status_double;

// type used for initial status variable.
typedef double init_status_double;

// type used for temporary variable, local variable.
typedef double var_local_double;

// this variable not change when it is assigned, use as model params.
typedef double param_const;

typedef std::string params_key;


#endif //PNOHS_MODEL_PARAMS_DEF_H
