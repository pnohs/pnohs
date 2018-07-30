//
// Created by genshen on 7/5/18.
//

#include <gtest/gtest.h>
#include <scheduler/s_context.h>
#include <scheduler/longest_pickup.h>

struct PickupTestUpMate {
    _type_node_id id;
    kiwi::RID rank;
    unsigned int queue_size;
};

typedef std::vector<PickupTestUpMate> ups;
struct PickupTestNode {
    _type_node_id id;
    ups _ups;  // multiple upstream.
};

void generateTestNodes(SContext *context, std::vector<PickupTestNode> &nodes) {
    // set nodes and its upstream graph.
    for (PickupTestNode &node: nodes) {
        SimulationNode snode;
        snode.id = node.id;
        for (PickupTestUpMate up: node._ups) {
            snode.upstream.putUpMetaStream(StreamMeta{up.id, up.rank}); // StreamMeta{upstream_id, upstream_rank}
        }
        snode.downstream.putDownMetaStream(StreamMeta{node.id + 1, 2}); // add downstream node (not important).
        snode.notifyDataSetChanged();
        context->pNodesPool->appendNode(snode);
    }
    // setup upstreams task queue.
    TypeRouting r;
    for (PickupTestNode &node: nodes) {
        SimulationNode *snode = context->pNodesPool->findNodeById(node.id);
        for (PickupTestUpMate up: node._ups) {
            for (int i = 0; i < up.queue_size; i++) {
                // add routing to this upstream for queue_size times.
                snode->upstream.appendUpstreamRouting(up.id, r);
            }
        }
    }
}

TEST(longest_pickup_strategy_test, scheduler_pickup_test) {
    std::vector<PickupTestNode> test_nodes = {
            PickupTestNode{id:1, _ups:ups{
                    PickupTestUpMate{id:10, rank:2, queue_size:5},
                    PickupTestUpMate{id:11, rank:2, queue_size:0},
            }},
            PickupTestNode{id:2, _ups:ups{
                    PickupTestUpMate{id:20, rank:2, queue_size:3},
                    PickupTestUpMate{id:21, rank:2, queue_size:4},
            }},
            PickupTestNode{id:3, _ups:ups{
                    PickupTestUpMate{id:30, rank:2, queue_size:5},
                    PickupTestUpMate{id:31, rank:2, queue_size:2},
            }},
            PickupTestNode{id:4, _ups:ups{
                    PickupTestUpMate{id:40, rank:2, queue_size:8},
                    PickupTestUpMate{id:41, rank:2, queue_size:0},
            }},
    };

    SContext *ctx = new SContext(6); //param: total steps
    generateTestNodes(ctx, test_nodes);

    // run test
    auto *pickup = new LongestPickup(*ctx);
    pickup->onStrategySelected();

    SimulationNode *picked = pickup->pickRunnable();
    EXPECT_NE(picked == nullptr, true);
    EXPECT_EQ(picked->id, (_type_node_id) 3);

    delete pickup;
    delete ctx;
}
