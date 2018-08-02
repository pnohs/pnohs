//
// Created by genshen on 4/6/18.
//

#include <pthread.h>
#include <utils/mpi_utils.h>
#include <event/message_looper.h>
#include "looper.h"
#include "stream_routing_message_runner.h"
#include "../utils/sim_domain.h"

Looper *Looper::NewMessageLooper() {
    auto looperInstance = new Looper(); // todo delete.
    pthread_t message_thread;
    int ret;

    ret = pthread_create(&message_thread, nullptr, Looper::messageLoopNewThread, nullptr);
    if (ret != 0) {
        return nullptr;
    }
    return looperInstance;
}

// those codes run in a new thread.
void *Looper::messageLoopNewThread(void *object) {
//    Looper *looperInstance = reinterpret_cast<Looper *>(object);

    // we only listen messages in simulation communication domain.
    kiwi::MessageLooper::setGlobalMessageDomain(domain::mpi_sim_process.comm);
    // Start a dead loop to listen and dispatch messages.
    // And runners in message loop will be unregistered automatically before loop finished.
    kiwi::MessageLooper::start();
    pthread_exit(nullptr);
}
