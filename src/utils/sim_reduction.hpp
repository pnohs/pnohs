//
// Created by genshen on 9/11/18.
//

#ifndef PNOHS_SIM_REDUCTION_H
#define PNOHS_SIM_REDUCTION_H

#include <map>
#include <vector>
#include "predefine.h"
#include "../adapter/model_context.h"

/**
 * In this class, it process simulation result like storing simulation data, filter data.
 * @tparam T the simulation result type for one step on one node.
 */
template<class T>
class SimReduction {
public:
    static const unsigned int BUFFER_FLAG_NONE = 0;

    /**
     * We store simulation data in a buffered map-vector @var r.
     * If the buffer comes to full, the function @fn  will be called. todo on buffer full.
     * set @var buffer_size to @var BUFFER_FLAG_NONE to disable buffer (all simulation data will be saved in memory).
     */
    SimReduction(const unsigned long buffer_size);

    /**
     * release memory of @var r.
     */
    ~SimReduction();

    /**
     * this function cal be call when performing simulation.
     * For each node, this function will be called to save to @var r simulation data in each time-step.
     * @note: you can override @fn filter to filter simulation data.
     *
     * @param context model context for current simulation node.
     * @param id the node id.
     * @param time_step current simulation time step.
     */
    void OnOneStep(T &res, const _type_node_id id, const unsigned long time_step);

    /**
     * simulation data filter.
     * This function will be called in @fn OnOneStep.
     * If this function returns false, the simulation data will be skipped,
     * otherwise the data will be stored in @var r.
     * @return false fot skipping processing data, true for processing data.
     */
    virtual bool filter(const _type_node_id id, const unsigned long time_step);

protected:
    /*
     * simulation results.
     * it is a map, the key of this map is the simulation node's id;
     * and its value is a vector, ths vector length equals to simulation time-steps;
     * items in vector represents the flow of river outlet in each time-step.
     */
    std::map<_type_node_id, std::vector<T>> r;

private:
    const unsigned long buffer_size;
};

template<class T>
SimReduction<T>::SimReduction(const unsigned long buffer_size):buffer_size(buffer_size) {}

template<class T>
SimReduction<T>::~SimReduction() {
// todo release memory.
}

template<class T>
void SimReduction<T>::OnOneStep(T &res, const _type_node_id id, const unsigned long time_step) {
    if (!filter(id, time_step)) {
        return;
    }
    if (r.find(id) != r.end()) {
        r[id].push_back(res);
    } else {
        std::vector<T> v;
        v.push_back(res);
        r.insert(std::pair<_type_node_id, std::vector<T>>(id, v));
    }
}

template<class T>
bool SimReduction<T>::filter(const _type_node_id id, const unsigned long time_step) {
    // return false as default value, which means it does not process any simulation data.
    return false;
}

#endif //PNOHS_SIM_REDUCTION_H
