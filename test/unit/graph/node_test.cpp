//
// Created by genshen on 4/4/18.
//

#include <gtest/gtest.h>
#include "graph/node.h"

TEST(node_upstream_add_test, grapg_node_test) {
    Node node = Node();
    EXPECT_EQ(node.isRiverOrigin(), true);
    EXPECT_EQ(node.isRiverOutlet(), true);

    StreamMeta meta = StreamMeta();
    meta.id = 1;
    node.upstream.putUpMetaStream(meta);  // add upstream node.
    EXPECT_EQ(node.isRiverOrigin(), true);
    EXPECT_EQ(node.isRiverOutlet(), true);

    node.notifyDataSetChanged();
    EXPECT_EQ(node.isRiverOrigin(), false);
    EXPECT_EQ(node.isRiverOutlet(), true);

    meta.id = 2;
    node.downstream.putDownMetaStream(meta); // add downstream node.
    EXPECT_EQ(node.isRiverOrigin(), false);
    EXPECT_EQ(node.isRiverOutlet(), true);
    EXPECT_EQ(node.upstream.nodes[0].id, (_type_node_id) 1); // not change upstream node id
    EXPECT_EQ(node.downstream.nodes[0].id, (_type_node_id) 2);

    node.notifyDataSetChanged();
    EXPECT_EQ(node.isRiverOrigin(), false);
    EXPECT_EQ(node.isRiverOutlet(), false);
}

TEST(node_find_upstream_by_id_test, grapg_node_test) {
    Node node = Node();

    node.upstream.putUpMetaStream(StreamMeta(100, 0));  // add upstream nodes.
    node.upstream.putUpMetaStream(StreamMeta(101, 1));
    node.upstream.putUpMetaStream(StreamMeta(102, 2));
    node.downstream.putDownMetaStream(StreamMeta(1000, 3)); // add downstream node.
    node.notifyDataSetChanged();

    EXPECT_EQ(node.upstream.findUpstreamNodeById(102)->location, (kiwi::RID) 2);
    EXPECT_EQ(node.upstream.findUpstreamNodeById(102)->id, (_type_node_id) 102);
    EXPECT_EQ(node.upstream.findUpstreamNodeById(99), nullptr);
}

// test appendUpstreamRouting and isReady and minQueSize.
TEST(node_task_queue_ready_test, grapg_node_test) {
    Node node = Node();
    node.id = 1000;

    node.upstream.putUpMetaStream(StreamMeta(100, 0));  // add upstream nodes.
    node.upstream.putUpMetaStream(StreamMeta(101, 1));
    node.upstream.putUpMetaStream(StreamMeta(102, 2));
    node.downstream.putDownMetaStream(StreamMeta(1000, 3)); // add downstream node.
    node.notifyDataSetChanged();

    EXPECT_EQ(node.upstream.isReady(), false);

    TypeRouting r0(100, 1000);
    EXPECT_EQ(node.upstream.appendUpstreamRouting(100, r0), true);
    EXPECT_EQ(node.upstream.isReady(), false);

    TypeRouting r1(101, 1000);
    EXPECT_EQ(node.upstream.appendUpstreamRouting(101, r1), true);
    EXPECT_EQ(node.upstream.isReady(), false);

    TypeRouting r2(102, 1000);
    EXPECT_EQ(node.upstream.appendUpstreamRouting(102, r2), true);
    EXPECT_EQ(node.upstream.isReady(), true);

    TypeRouting r3(103, 1000);
    EXPECT_EQ(node.upstream.appendUpstreamRouting(103, r3), false); // append failed

    EXPECT_EQ(node.upstream.minQueSize(), (unsigned long) 1);

    // de queue test.
    node.upstream.deQueue();
    EXPECT_EQ(node.upstream.isReady(), false);

    EXPECT_EQ(node.upstream.minQueSize(), (unsigned long) 0); //  size of all queue will be zero.
}
