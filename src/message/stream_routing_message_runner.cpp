//
// Created by genshen on 4/7/18.
//

#include "stream_routing_message_runner.h"

bool StreamRoutingMessageRunner::shouldDetach() const {
    return MessageRunner::shouldDetach();  // todo
}

bool StreamRoutingMessageRunner::filter(MPI_Status *pStatus) {
    return false; // todo
}

void StreamRoutingMessageRunner::onMessage(MPI_Status *pStatus) {
    // todo
// if type = task{
//    pthread_mutex_lock(&_t_mu);
//    //    addToQueue()  // write queue.
//    if (_t_waiting) {
//        //weak up, pthread_cond_signal() will have no effect if there are no threads currently blocked on cond.
//        pthread_cond_signal(&_t_cond);
//    }
//    pthread_mutex_unlock(&_t_mu);
// }
}
