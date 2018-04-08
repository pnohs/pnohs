//
// Created by genshen on 4/6/18.
//

#include <iostream>
#include <pthread.h>
#include <utils/mpi_utils.h>
#include <event/message_looper.h>
#include "looper.h"
#include "stream_routing_message_runner.h"

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

// those runs in a new thread.
void *Looper::messageLoopNewThread(void *object) {
//    Looper *looperInstance = reinterpret_cast<Looper *>(object);

    kiwi::MessageLooper::registerRunner(new StreamRoutingMessageRunner());
    // a dead loop to listen and dispatch messages.
    // And runners in message loop will be unregistered automatically before loop finished.
    kiwi::MessageLooper::start();
    pthread_exit(nullptr);
}

