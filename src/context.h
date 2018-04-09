//
// Created by genshen on 3/28/18.
//

#ifndef PNOHS_CONTROLLER_H
#define PNOHS_CONTROLLER_H

#include "simulation_node.h"
#include "config_toml.h"
#include "nodes_pool.h"

class Context {
public:

    Context(ConfigToml *pConfig);

    ~ Context();

    /**
     *  abort all processors with exit code specified by {@var code}
     * @param reason the error message wil print.
     * @param code exit code
     */
    void abort(const std::string &reason, int code);

    // pthread variable
    int _t_waiting = 0;
    pthread_mutex_t _t_mu;
    pthread_cond_t _t_cond;

private:
    const ConfigToml *pConfig;

};

#endif //PNOHS_CONTROLLER_H
