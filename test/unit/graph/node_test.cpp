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
