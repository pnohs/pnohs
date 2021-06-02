//
// Created by genshen on 8/9/18.
//

#include <logs/logs.h>

#include "utils/sim_domain.h"
#include "simulation_node.h"
#include "api_params.h"

ApiParams::ApiParams(SContext *s_ctx, kiwi::RID root) : root(root) {
    GraphMetaBuilder builder;
    graph_meta = (&builder)
            ->createGraph()
            ->setDomain(domain::mpi_sim_process)
            ->setRoot(root)
            ->setGraphBuilder([s_ctx](Graph *graph) {
                s_ctx->pNodesPool->toPureGraph(graph);
            })  // initialize local graph(sub-graph)
            ->build();
}

ApiParams::~ApiParams() {
    GraphMetaBuilder::destroyMetaEntity(graph_meta); // graph in meta will also be deleted here.
}

void ApiParams::setNodesParams(SContext *s_ctx, _type_param params[], const size_t length, const size_t size) {
    _type_param *_local_params = new _type_param[size * graph_meta.local_nodes_count]; // fixme
    // runoff parameters vector and routing parameter vector points to array _local_params.
    std::vector<_type_param *> runoff_params(graph_meta.local_nodes_count);
    std::vector<_type_param *> routing_params(graph_meta.local_nodes_count);

    if (!distParams(params, length, size, _local_params, graph_meta.g_nodes_counts, root)) {
        kiwi::logs::e("params", "error parameters size.\n");
        delete[]_local_params;
        return;
    }

    // set parameters vector.
    for (int i = 0; i < graph_meta.local_nodes_count; i++) {
        SimulationNode *node = s_ctx->pNodesPool->findNodeById(graph_meta.local_nodes_id_lists->at(i));
        if (node == nullptr) {
            // set default value when fault error happen.
            kiwi::logs::w("params", "node not fount by id {}", graph_meta.local_nodes_id_lists->at(i));
            runoff_params[i] = _local_params;
            routing_params[i] = _local_params;
            continue;
        }
        runoff_params[i] = _local_params + i * size;
        routing_params[i] = _local_params + node->_p_runoff_model->paramCount();
    }

    s_ctx->pNodesPool->setNodesParams(*(graph_meta.local_nodes_id_lists), runoff_params,
                                      routing_params); // todo data copy
    delete[]_local_params;
}

bool ApiParams::distParams(_type_param params[], const size_t length, const size_t size,
                           _type_param _local_params[], _type_nodes_count global_nodes_count[],
                           const kiwi::RID root) {
    _type_nodes_count total_nodes_count = 0, local_nodes_count = 0;
    // compute all nodes counts and local nodes counts.
    for (int i = 0; i < domain::mpi_sim_process.all_ranks; i++) {
        total_nodes_count += global_nodes_count[i];
        if (i == domain::mpi_sim_process.own_rank) {
            local_nodes_count = global_nodes_count[i];
        }
    }

    // set send counts and displacements.
    int *send_counts = nullptr, *displs = nullptr; // todo data reuse.
    if (domain::mpi_sim_process.own_rank == root) {
        // for root processor, the length of array params must be total nodes count * params size.
//        if (length != size * total_nodes_count) {
//            return false; // todo abort it.
//        }
        send_counts = new int[domain::mpi_sim_process.all_ranks];
        displs = new int[domain::mpi_sim_process.all_ranks];
        int offset = 0;
        for (int i = 0; i < domain::mpi_sim_process.all_ranks; i++) {
            send_counts[i] = static_cast<int>(size * global_nodes_count[i]);
            displs[i] = offset;
            offset += send_counts[i];
        }
    }

    // get local params, save it in @var _local_param.
    // On non-root processors, only the arguments recvbuf, recvcount, recvtype, root, and comm are significant.
    MPI_Scatterv(params, send_counts, displs, _type_param_mpi,
                 _local_params, static_cast<int>(size * local_nodes_count), _type_param_mpi,
                 root, domain::mpi_sim_process.comm);
    delete[]send_counts;
    delete[]displs;
    return true;
}

_type_node_id ApiParams::nextSimNodeId() {
    return 0; // todo
}
