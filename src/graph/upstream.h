//
// Created by genshen on 2018-03-26.
//

#ifndef PNOHS_UPSTREAM_H
#define PNOHS_UPSTREAM_H


#include <vector>
#include <list>
#include "stream_meta.h"
#include "upstream_node.h"
#include "../routing/type_routing.h"

class Upstream {
public:

    // node id of upstream nodes. Null or empty indicates that there is no upstream node.
    std::vector<UpstreamNode> nodes; // nodes meta information // todo make private.

    // count of upstream nodes of this node.
    inline const unsigned long count() {
        return nodes.size(); // todo
    }

    // whether the upstream nodes of this node is ready to start a new time-step simulation.
    // That is the task queues of each upstream nodes are all not empty.
    bool isReady();

    /**
     * checkout whether there is a upstream node whose id is the given id,
     * returns pointer of UpstreamNode if found.
     * @param id node id
     * @return if true, return pointer of this UpstreamNode, otherwise return null.
     */
    UpstreamNode *findUpstreamNodeById(_type_node_id id);

    /**
     * add a upstream node to vector @var nodes and create a queue for this node
     * It is used when doing stream parsing.
     */
    void putUpMetaStream(const StreamMeta &meta);

    /**
     * Add a upstream-routing result to task queue.
     * In stream routing process, a node receives routing result from its upstream node
     * (mpi communication if its upstream is not on the same processor, or just memory copy if its upstream is on the same processor),
     * then this node will append the result to task queue of
     * the corresponding upstream node (in {@var std::vector<UpstreamNode>  nodes}) of this node.
     * @param upstream_node_id the node id of upstream node.
     * @param data the routing result data to be added to task queue.
     */
    void appendUpstreamRouting(_type_node_id upstream_node_id, TypeRouting &data);

    /**
     * Dequeue an routing results of task queue from each upstream nodes.
     * Each upstream node would contribute one routing results.
     * And all routing results all belongs to the same time step.
     *
     * If one task queue of upstream nodes is empty,
     * a new and empty TypeRouting will be added to the returned list.
     *
     * @return list od dequeued routing results.
     */
    std::list<TypeRouting> deQueue(); // todo std:: array or list? // todo function name.
};

#endif //PNOHS_UPSTREAM_H
