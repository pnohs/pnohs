//
// Created by genshen on 8/24/18.
//

#include <random>
#include <gtest/gtest.h>
#include <scheduler/ring_pickup.h>
#include <utils/sim_domain.h>

#include <logs/logs.h>
#include <graph_extra/api_params.h>
#include "../test_config.h"


TEST(api_params_test_dist_params, api_params_test) {
    domain::mpi_sim_process = kiwi::mpiUtils::global_process;
    // in this test, rank i has i+1 nodes.
    const auto total_nodes = domain::mpi_sim_process.all_ranks * (domain::mpi_sim_process.all_ranks + 1) / 2;
    const _type_params_count PARAMS_SIZE = 2;
    const _type_params_count PARAMS_LEN = PARAMS_SIZE * total_nodes;
    const kiwi::RID root = MASTER_PROCESSOR;

    _type_param *global_params = nullptr;

    // create nodes count data.
    _type_nodes_count *nodes_count = new _type_nodes_count[domain::mpi_sim_process.all_ranks];
    for (kiwi::RID r = 0; r < domain::mpi_sim_process.all_ranks; r++) {
        nodes_count[r] = r + 1; // rank r has i+1 nodes.
    }
    // create global parameters(in fact, only root processor is ok).
    global_params = new _type_param[total_nodes * PARAMS_SIZE];
    unsigned long p_i = 0;
    for (kiwi::RID r = 0; r < domain::mpi_sim_process.all_ranks; r++) { // for all ranks.
        for (int i = 0; i < nodes_count[r]; i++) { // for all nodes on one processor.
            for (int j = 0; j < PARAMS_SIZE; j++) { // for all parameter in one node.
                p_i++;
                global_params[p_i].float_param = p_i;
            }
        }
    }


    // create local parameters array.
    _type_param *local_params = new _type_param[PARAMS_SIZE * (domain::mpi_sim_process.own_rank + 1)];
    // run distribution
    ApiParams::distParams(global_params, PARAMS_LEN, PARAMS_SIZE,
                          local_params, nodes_count, root);

    // DO result test.
    unsigned long local_index = 0;
    // data before current processor.
    p_i = PARAMS_SIZE * (domain::mpi_sim_process.own_rank *
                         (domain::mpi_sim_process.own_rank + 1) / 2);
    for (int i = 0; i < nodes_count[domain::mpi_sim_process.own_rank]; i++) { // for all nodes on my processor.
        for (int j = 0; j < PARAMS_SIZE; j++) { // for all parameter in one node.
            EXPECT_DOUBLE_EQ(global_params[p_i++].float_param, local_params[local_index++].float_param);
        }
    }
    delete[]nodes_count;
    delete[]global_params;
    delete[]local_params;
}