//
// Created by genshen on 4/7/18.
//

#include "stream_routing_message_runner.h"

// initial context for thread here.
StreamRoutingMessageRunner::StreamRoutingMessageRunner(Context &ctx, NodesPool *pPool) : ctx(ctx), pNodesPool(pPool) {}

bool StreamRoutingMessageRunner::shouldDetach() const {
    return !(pNodesPool->potentiallyCompleted());
}

bool StreamRoutingMessageRunner::filter(MPI_Status *pStatus) {
    return pStatus->MPI_TAG == TagStreamRoutingMessage; // only receive stream routing message.
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
    // wake up the blocked main thread if necessary.

}
