//
// Created by genshen on 3/28/18.
//

#ifndef PNOHS_SYS_CONTEXT_H
#define PNOHS_SYS_CONTEXT_H

#include <pthread.h>
#include <string>
#include <utils/mpi_utils.h>

/**
 * system relative context here, such as mutex, program lifetime.
 */
class SysContext {
public:

    SysContext(/*ConfigToml *pConfig*/);

    ~ SysContext();

    /**
     *  abort all processors with exit code specified by {@var code}
     * @param reason the error message wil print.
     * @param code exit code
     */
    void abort(const std::string &reason, int code);

    inline double getBlockingTime() {
        return blocking_time;
    }

    inline unsigned long getBlockTimes() {
        return block_times;
    }

    /**
     * call this function to accumulate blocking time and blocking count.
     * @param delta_blocking_time the blocking time in one thread blocking.
     */
    void onThreadBlock(double delta_blocking_time);

    // pthread variable
    int _t_waiting = 0; // todo add comments here.
    pthread_mutex_t _t_mu;
    pthread_cond_t _t_cond;
//    kiwi::mpi_process mpi_sim_process; // todo move here

private:
    /**
     * the cumulative time of blocking pthread waiting for available simulation nodes.
     */
    double blocking_time = 0.0;

    /**
     * the count of blocking pthread waiting for available simulation nodes.
     * It will plus 1 if selecting simulation node goes to blocked.
     */
    unsigned long block_times = 0;

};

#endif //PNOHS_SYS_CONTEXT_H
