//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_NODE_H
#define PNOHS_NODE_H

#include <vector>
#include "stream_meta.h"
#include "upstream.h"
#include "downstream.h"
#include "../utils/predefine.h"

/**
 * Node in river-routing relationship graph.
 * Node is a simulation unit (e.g. sub-basin, hydrological response unit(HRU)) in geography.
 * In our graph, node refers to simulation unit, vertex refers to river-routing relationship from upstream to downstream.
 */

class Node {
public:
    const _type_node_id id; // node id.

    /**
     *  upstream of this node.
     */
    Upstream upstream;

    /**
     * downstream of this node (usually,it has only one downstream node).
     */
    Downstream downstream;

    /**
     * construction method for creating a node using given id.
     * @param id node id.
     */
    Node(const _type_node_id id);

    /**
     * use this function to update/refresh node information in this class
     * after some upstream or downstream nodes are added to this node.
     */
    void notifyDataSetChanged();

    /**
     * Check whether this node is the river outlet.
     * @return
     */
    inline bool isRiverOutlet() const {
        return _is_river_outlet;
    }

    /**
     * Check whether this node is the river origin.
     * @return
     */
    inline const bool isRiverOrigin() {
        return _is_river_origin;
    }

private:
    bool _is_river_outlet = true; // default value
    bool _is_river_origin = true;
};

#endif //PNOHS_NODE_H
