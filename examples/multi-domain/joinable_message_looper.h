//
// Created by genshen on 2020/10/18.
//

#ifndef PNOHS_JOINABLE_MESSAGE_LOOPER_H
#define PNOHS_JOINABLE_MESSAGE_LOOPER_H

#include <pthread.h>
#include <utils/mpi_utils.h>
#include <event/message_looper.h>
#include <logs/logs.h>
#include "message/stream_routing_message_runner.h"
#include "utils/sim_domain.h"

class JoinableMessageLooper {
public:
    /**
     * Factory method to create objects
     * @return A Looper instance.
     */
    static JoinableMessageLooper *NewMessageLooper() {
        auto looperInstance = new JoinableMessageLooper(); // todo delete.
        int ret;

        ret = pthread_create(&(looperInstance->message_thread), nullptr,
                             JoinableMessageLooper::messageLoopNewThread, nullptr);
        if (ret != 0) {
            return nullptr;
        }
        return looperInstance;
    }

    /**
     * wait the new thread to finish using pthread_join.
     * This is called on main thread
     */
    void Wait() {
        int err_join = pthread_join(message_thread, nullptr);
        if (err_join != 0) {
            kiwi::logs::e("lopper", "error join thread.\n");
        }
    }

private:
    pthread_t message_thread;

    JoinableMessageLooper() = default;

    /** Method for pthread create, this method runs in a new thread.
     * It runs a loop, listen to new message, and dispatch message to different register.
     * @param args pthread arg.
     * @return pthread return.
     */
    static void *messageLoopNewThread(void *object) {
        // we only listen messages in simulation communication domain.
        kiwi::MessageLooper::setGlobalMessageDomain(domain::mpi_sim_process.comm);
        // Start a dead loop to listen and dispatch messages.
        // And runners in message loop will be unregistered automatically before loop finished.
        kiwi::MessageLooper::start();

        return nullptr;
    }
};

#endif //PNOHS_JOINABLE_MESSAGE_LOOPER_H
