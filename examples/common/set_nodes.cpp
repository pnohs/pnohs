//
// Created by genshen on 2020/7/2.
//

#include <cassert>
#include <mpi.h>
#include <nodes_pool.h>

void setupNodes(NodesPool *p_node_pool, MPI_Comm comm) {
    int rank = 0, size = 0;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    assert(size == 3);

    switch (rank) {
        case 0: // mpi rank 0
        {
            SimulationNode node1(1);
            node1.downstream.putDownMetaStream(StreamMeta{4, 0});
            node1.notifyDataSetChanged();
            p_node_pool->appendNode(node1);

            SimulationNode node2(4);
            node2.upstream.putUpMetaStream(StreamMeta{1, 0});
            node2.downstream.putDownMetaStream(StreamMeta{8, 1});
            node2.notifyDataSetChanged();
            p_node_pool->appendNode(node2);

            SimulationNode node3(7);
            node3.downstream.putDownMetaStream(StreamMeta{10, 0});
            node3.notifyDataSetChanged();
            p_node_pool->appendNode(node3);

            SimulationNode node4(10);
            node4.upstream.putUpMetaStream(StreamMeta{7, 0});
            node4.downstream.putDownMetaStream(StreamMeta{13, 0});
            node4.notifyDataSetChanged();
            p_node_pool->appendNode(node4);

            SimulationNode node5(13);
            node5.upstream.putUpMetaStream(StreamMeta{10, 0});
            node5.upstream.putUpMetaStream(StreamMeta{11, 1});
            node5.downstream.putDownMetaStream(StreamMeta{16, 0});
            node5.notifyDataSetChanged();
            p_node_pool->appendNode(node5);

            SimulationNode node6(16);
            node6.upstream.putUpMetaStream(StreamMeta{13, 0});
            node6.upstream.putUpMetaStream(StreamMeta{14, 1});
            node6.upstream.putUpMetaStream(StreamMeta{12, 2});
            node6.upstream.putUpMetaStream(StreamMeta{15, 2});
            node6.notifyDataSetChanged();
            p_node_pool->appendNode(node6);
        }
            break;
        case 1: // mpi rank 1
        {
            SimulationNode node1(2);
            node1.downstream.putDownMetaStream(StreamMeta{8, 1});
            node1.notifyDataSetChanged();
            p_node_pool->appendNode(node1);

            SimulationNode node2(5);
            node2.downstream.putDownMetaStream(StreamMeta{8, 1});
            node2.notifyDataSetChanged();
            p_node_pool->appendNode(node2);

            SimulationNode node3(8);
            node3.upstream.putUpMetaStream(StreamMeta{4, 0});
            node3.upstream.putUpMetaStream(StreamMeta{2, 1});
            node3.upstream.putUpMetaStream(StreamMeta{5, 1});
            node3.upstream.putUpMetaStream(StreamMeta{3, 3});
            node3.downstream.putDownMetaStream(StreamMeta{12, 2});
            node3.notifyDataSetChanged();
            p_node_pool->appendNode(node3);

            SimulationNode node4(11);
            node4.downstream.putDownMetaStream(StreamMeta{13, 0});
            node4.notifyDataSetChanged();
            p_node_pool->appendNode(node4);

            SimulationNode node5(14);
            node5.downstream.putDownMetaStream(StreamMeta{16, 0});
            node5.notifyDataSetChanged();
            p_node_pool->appendNode(node5);
        }
            break;
        case 2: // mpi rank 2
        {
            SimulationNode node1(3);
            node1.downstream.putDownMetaStream(StreamMeta{8, 1});
            node1.notifyDataSetChanged();
            p_node_pool->appendNode(node1);

            SimulationNode node2(6);
            node2.downstream.putDownMetaStream(StreamMeta{9, 2});
            node2.notifyDataSetChanged();
            p_node_pool->appendNode(node2);

            SimulationNode node3(9);
            node3.upstream.putUpMetaStream(StreamMeta{6, 2});
            node3.downstream.putDownMetaStream(StreamMeta{12, 2});
            node3.notifyDataSetChanged();
            p_node_pool->appendNode(node3);

            SimulationNode node4(12);
            node4.upstream.putUpMetaStream(StreamMeta{8, 1});
            node4.upstream.putUpMetaStream(StreamMeta{9, 2});
            node4.downstream.putDownMetaStream(StreamMeta{16, 0});
            node4.notifyDataSetChanged();
            p_node_pool->appendNode(node4);

            SimulationNode node5(15);
            node5.downstream.putDownMetaStream(StreamMeta{16, 0});
            node5.notifyDataSetChanged();
            p_node_pool->appendNode(node5);
        }
            break;
    }
}
