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
template<typename T>
class SimReduction {
public:
    static const unsigned int BUFFER_FLAG_NONE = 0;
    typedef std::map<_type_node_id, std::vector<T>> simred;
    typedef typename simred::iterator simred_iter;

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
     * @param res the simulation data for simulation node specified by node id @param id.
     * @param id the node id.
     * @param time_step current simulation time step.
     */
    void OnOneStep(const _type_node_id id, const unsigned long time_step, T &res);

    /**
     * this method convert simulation results to 2-d array(in fact, it is 1-d due to the consequent memory) specified by @param flows.
     * it contains {nodes count}s rows, in each row, it contains {time_steps}s col,
     * representing {time_steps}s flow data in each time step on this simulation node.
     * @param result_2d the 1-d array to store the flat 2d array.
     * @param len the length of 1d array
     * @param steps the total simulation steps.
     * @return return true if convert success, return false for otherwise.
     */
    bool flat(T *result_2d, const unsigned long len, const unsigned long steps);

    /**
     * This method set the array @var result_vec for usage.
     * It copy memory of the vector form map @param r whose key is @param id to array @param result_vec.
     * If the key-value is not found in map @param r, 
     * this function will be returned leaving array @param result_vec untouched.
     * @param result_vec receive array to save result data form map-vector.
     * @param len the length of array @param result_vec
     * @return true for set array @param result_vec successfully, false for otherwise.
     */
    bool flatNode(T *result_vec, const _type_node_id id, const unsigned long len);

protected:
    /*
     * simulation results.
     * it is a map, the key of this map is the simulation node's id;
     * and its value is a vector, ths vector length equals to simulation time-steps;
     * items in vector represents the flow of river outlet in each time-step.
     */
    simred r;

    /**
     * simulation data filter.
     * This function will be called in @fn OnOneStep.
     * If this function returns false, the simulation data will be skipped,
     * otherwise the data will be stored in @var r.
     * @return false fot skipping processing data, true for processing data.
     */
    virtual bool filter(const _type_node_id id, const unsigned long time_step);

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
void SimReduction<T>::OnOneStep(const _type_node_id id, const unsigned long time_step, T &res) {
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

template<class T>
bool SimReduction<T>::flat(T *result_2d, const unsigned long len, const unsigned long steps) {
    // test length of map/vector data.
    simred_iter iter_len_test;
    int len_real = 0;
    for (iter_len_test = r.begin(); iter_len_test != r.end(); iter_len_test++) {
        len_real += iter_len_test->second.size();
    }
    if (len_real != len || len_real != r.size() * steps) {
        return false;
    }

    // allocate memory for 2d indexing.
    unsigned long x = r.size();
    unsigned long y = steps;
    T **flows2d = new T *[x];
    *flows2d = result_2d;
    for (int i = 0; i < x; i++) {
        flows2d[i] = result_2d + i * y;
    }
    // copy values
    int i = 0;
    simred_iter iter;
    for (iter = r.begin(); iter != r.end(); iter++) {
        int j = 0;
        for (T _flow :iter->second) {
            flows2d[i][j] = _flow;
            j++;
        }
        i++;
    }
    delete[]flows2d;
    return true;
}

template<typename T>
bool SimReduction<T>::flatNode(T *result_vec, const _type_node_id id, const unsigned long len) {
    std::vector<T> &temp = r[id];
    if (temp.size() != len) {
        return false;
    }
    std::copy(temp.begin(), temp.begin() + len, result_vec);
    return true;
}

#endif //PNOHS_SIM_REDUCTION_H
