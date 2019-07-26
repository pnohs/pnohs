//
// Created by genshen on 2018-03-28.
//

#include <iostream>
#include <logs/logs.h>
#include "sys_context.h"

SysContext::SysContext() {
    // todo use pthread_once: https://linux.die.net/man/3/pthread_mutex_init
    // todo destroy
    // initialize pthread mutex and cond
    pthread_mutex_init(&_t_mu, nullptr); // or use static initialize.
    pthread_cond_init(&_t_cond, nullptr);
}

SysContext::~SysContext() { // todo delete context.
}

void SysContext::abort(const std::string &reason, int code) {
    kiwi::logs::e("abort", (reason + "\n").c_str());
    MPI_Abort(MPI_COMM_WORLD, code);
}

void SysContext::onThreadBlock(double delta_blocking_time) {
    blocking_time += delta_blocking_time;
    block_times++;
}
