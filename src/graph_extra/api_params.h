//
// Created by genshen on 8/9/18.
//

#ifndef PNOHS_ALPHA_API_PARAMS_H
#define PNOHS_ALPHA_API_PARAMS_H

#include "graph/graph.h"
#include "utils/predefine.h"
#include "ds/model_params_def.h"
#include "scheduler/s_context.h"
#include "api_graph_meta.h"

/**
 * api for performing parameter calibration.
 */
class ApiParams {
    friend class Params;

public:
    /**
     * Initialize api environment,
     * including creating and filling  @var g_nodes_counts array and @var g_nodes_id_list array.
     *
     * @param root root rank in simulation domain (usually rank 0).
     */
    ApiParams(SContext *s_ctx, kiwi::RID root);

    /**
     * destroy all kinds of array here.
     */
    ~ApiParams();

    /**
     * set parameters on the whole basin in domain::mpi_sim_process using given params specified by \param params
     * @param s_ctx scheduler context.
     * @param params the global models params that may generated by parameter calibration algorithm.
     * @param length length of array @var params.
     * @param size parameters count for one simulation node.
     */
    void setNodesParams(SContext *s_ctx, _type_param params[], const size_t length, const size_t size);

    /**
     * distribute global parameters (parameters for all nodes in all processors) to each processor.
     * Make sure ths id list @var g_nodes_id_lists is created on root processor before calling this function.
     * For non-root processor, the @param params and @param length can be null.
     *
     * @param params global parameters data.
     * @param length the length of parameters array.
     * @param size the size of parameters for one node.
     * @param local_params parameters for local nodes in current processor.
     * @param global_nodes_count nodes counts on each processor.
     * @param root the rank of root processor.
     * @return return true if conversation success, false for otherwise.
     */
    static bool distParams(_type_param params[], const size_t length, const size_t size,
                           _type_param local_params[], _type_nodes_count global_nodes_count[], const kiwi::RID root);

    /**
     * It returns id of next simulation node.
     * This function must be called by all processor in simulation domain.
     * @deprecated
     * @return id of next simulation node
     */
    _type_node_id nextSimNodeId();

    /**
     * calculate displacement.
     * @note make sure the array @var g_nodes_counts is created before calling this function.
     */
//    void calcDisp();
private:

    ApiGraphMeta graph_meta;
    /**
     * rank of root processor.
     */
    const kiwi::RID root;

};


#endif //PNOHS_ALPHA_API_PARAMS_H
