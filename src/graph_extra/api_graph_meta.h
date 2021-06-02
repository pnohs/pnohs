//
// Created by genshen on 9/12/18.
//

#ifndef PNOHS_ALPHA_API_GRAPHMETA_H
#define PNOHS_ALPHA_API_GRAPHMETA_H

#include <functional>

#include "graph/graph.h"
#include "utils/mpi_utils.h"

class ApiGraphMeta;


/**
 * @note In builder, before calling build function, the graph pointer must be set,
 * and @var graph_builder may also be set to initialize the graph.
 */
class GraphMetaBuilder {
public:
    /**
     * set root
     * @param rank id of root.
     * @return
     */
    inline GraphMetaBuilder *setRoot(kiwi::RID root) {
        this->root = root;
        return this;
    }

    /**
     * set root
     * @param rank id of root.
     * @return
     */
    inline GraphMetaBuilder *setDomain(kiwi::mpi_process domain) {
        this->d = domain;
        return this;
    }

    /**
    * set function pointer for initialize graph data.
    * @return
    */
    inline GraphMetaBuilder *setGraphBuilder(std::function<void(Graph *)> graph_builder) {
        this->graph_builder = graph_builder;
        return this;
    }

    /**
     * new an empty graph object and set it to @var graph.
     * @return
     */
    inline GraphMetaBuilder *createGraph() {
        this->graph = new Graph();
        return this;
    }

    /**
     * set existing graph pointer to @var graph.
     * @param graph reference of local sub-graph, it will be assigned to @var graph.
     * @return
     */
    inline GraphMetaBuilder *setGraph(Graph *graph) {
        this->graph = graph;
        return this;
    }

    /**
    * create a new graph meta.
    * It need communication to obtain global graph information.
    *
    * @note the data about ids are not stored in this class,
    * this class just have pointers to the arrays/vectors.
    *
    * The graph must be initialized(have nodes data in graph) before passed to this function.
    * @param sim_process
    * @return object of graph meta.
    */
    ApiGraphMeta build();

    /**
     * destroy the entity(e.g. global nodes ids array, ids count on each processor) created by newInstance.
     * @param meta graph mate.
     */
    static void destroyMetaEntity(ApiGraphMeta meta);

private:
    Graph *graph = nullptr;
    kiwi::RID root; // root processor in communication domain.
    kiwi::mpi_process d; // simulation domain.
    std::function<void(Graph *)> graph_builder; // It shows how to initialize graph object.
};

/**
 * In this class, some meta data about global graph are provided,
 * including global and local nodes count, pointer of nodes id list.
 *
 * @note the global nodes ids are only be stored on this root processor.
 */
class ApiGraphMeta {
public:
    friend ApiGraphMeta GraphMetaBuilder::build();

    static const kiwi::RID RANK_NOT_FOUND = -1;
    /**
     * local graph(sub-graph) for current processor.
     */
    Graph *graph = nullptr;

    /**
     * array of storing the nodes count of all processors in simulation domain.
     */
    _type_nodes_count *g_nodes_counts = nullptr;

    /**
     * the count of all nodes in simulation domain.
     * It is the sum of all elements in array @var g_nodes_counts.
     */
    _type_nodes_count g_total_nodes_count = 0;

    /**
     * local nodes count in current processor
     */
    _type_nodes_count local_nodes_count = 0;

    /**
     * all nodes ids of processors in simulation domain.
     * @note This array is only created in root processor.
     * If you index this array on non-root processor, out-of-boundary error may happen.
     */
    _type_node_id *g_nodes_id_lists = nullptr;

    /**
     * nodes id of local processor.
     */
    std::vector<_type_node_id> *local_nodes_id_lists = nullptr;

    /**
     * This function queries nodes id table, and returns a rank P as result.
     * On rank P, it has a node whose id is @param id.
     * @note this function can only be called on root processor.
     * @param id the node id to be queried.
     * @return a rank id matching the given node id or RANK_NOT_FOUND if the matching rank is not found.
     */
    kiwi::RID locateRank(const _type_node_id id);

private:
    kiwi::mpi_process d; // simulation domain.
};


#endif //PNOHS_ALPHA_API_GRAPHMETA_H
