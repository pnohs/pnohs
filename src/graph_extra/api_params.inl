//
// Created by genshen on 8/9/18.
//

#ifndef PNOHS_ALPHA_API_PARAMS_INC
#define PNOHS_ALPHA_API_PARAMS_INC

#include "api_params.h"

template<short MODE>
unsigned int ApiParams::localParamsCount(SContext *s_ctx) {
    unsigned int counter = 0;
    for (int i = 0; i < graph_meta.local_nodes_count; i++) {
        SimulationNode *node = s_ctx->pNodesPool->findNodeById(graph_meta.local_nodes_id_lists->at(i));
        if (node == nullptr) {
            // set default value when fault error happen.
            kiwi::logs::w("params", "node not fount by id {}", graph_meta.local_nodes_id_lists->at(i));
            continue;
        }
        if (MODE & ApiParams::PARAMS_LOAD_MODE_RUNOFF) {
            counter += node->_p_runoff_model->paramCount();
        }
        if (MODE & ApiParams::PARAMS_LOAD_MODE_ROUTING) {
            counter += node->_p_routing_model->paramCount();
        }
    }
    return counter;
}

#endif //PNOHS_ALPHA_API_PARAMS_INC
