//
// Created by genshen on 8/9/18.
//

#ifndef PNOHS_API_PARAMS_H
#define PNOHS_API_PARAMS_H

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

    const static short PARAMS_LOAD_MODE_RUNOFF = 1 << 0;
    const static short PARAMS_LOAD_MODE_ROUTING = 1 << 1;
    const static short PARAMS_LOAD_MODE_BOTH = (1 << 0) | (1 << 1);
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
     * @param _local_params the local models params for all simulation nodes on this processors,
     *  including routing and runoff parameters.
     * @param length length of array @var params (currently, it is not used).
     */
    void setNodesParams(SContext *s_ctx, _type_param _local_params[], const size_t length);

    /**
     * distribute global parameters (parameters for all nodes in all processors) to each processor.
     * Make sure ths id list @var g_nodes_id_lists is created on root processor before calling this function.
     * For non-root processor, the @param params and @param length can be null.
     *
     * @param params global parameters data.
     * @param length the length of parameters array.
     * @param size the size of parameters for one simulation node.
     *  We assume the parameters size of each simulation node is all the same.
     * @param local_params parameters for local nodes in current processor.
     * @param global_nodes_count nodes counts on each processor.
     * @param root the rank of root processor.
     * @return return true if conversation success, false for otherwise.
     */
    static bool distParams(_type_param params[], const size_t length, const size_t size,
                           _type_param local_params[], const _type_nodes_count global_nodes_count[],
                           const kiwi::RID root);

    /**
     * It is almost the same as above.
     * But, the parameters size of each simulation node can be distinguishing.
     * \param params, length, local_params, global_nodes_count, root the same as above one.
     * \param sizes the global parameters number on each MPI processors.
     * \return return true if conversation success, false for otherwise.
     */
    static bool distParams(_type_param params[], const size_t length, const size_t sizes[],
                           _type_param local_params[], const _type_nodes_count global_nodes_count[],
                           const kiwi::RID root);

    /**
     * this api is used for get total parameters number of simulation nodes on current processor.
     * The parameters includes routing parameters and runoff parameters.
     * \tparam MODE MODE is used to control only count routing parameters or, only runoff parameters,
     *  or both routing parameters and runoff parameters.
     * \return the parameters number of simulation nodes on current processor.
     */
    template<short MODE>
    unsigned int localParamsCount(SContext *s_ctx);

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

private:
    /**
     * implementation of distributing global parameters (parameters for all nodes in all processors) to each processor.
     * @param params global parameters data.
     * @param length the length of parameters array.
     * @param size the size of parameters for one simulation node.
     *   It can be used if the parameters size of each simulation node is all the same.
     * \param sizes the global parameters number on each MPI processors.
     *   It can be used if the parameters size of each simulation node can be distinguishing.
     *   Otherwise, it can be nullptr.
     * @param local_params parameters for local nodes in current processor.
     * @param global_nodes_count nodes counts on each processor.
     * @param root the rank of root processor.
     * @return return true if conversation success, false for otherwise.
     */
    static bool privateDistParams(_type_param params[], const size_t length, const size_t size, const size_t sizes[],
                                  _type_param _local_params[], const _type_nodes_count global_nodes_count[],
                                  const kiwi::RID root);
};

#include "api_params.inl"

#endif //PNOHS_API_PARAMS_H
