///
// Created by genshen on 4/9/18.
//

#include <utils/mpi_utils.h>
#include <logs/logs.h>
#include "scheduler.h"
#include "strategy_container.h"
#include "../utils/stopwatch.h"

Scheduler::Scheduler(SysContext &ctx, SContext &scheduleContext) :
        ctx(ctx), schCtx(scheduleContext) {
}

Scheduler::~Scheduler() {}

bool Scheduler::setPickupStrategy(const std::string &key) {
    StrategyAdapter *pAdapter = StrategyContainer::findStrategyByKey(key);
    if (pAdapter == nullptr) {
        return false; // todo handel error
    } else {
        pickup = pAdapter;
        pickup->onStrategySelected(); // initialize this pickup strategy.
        return true;
    }
}

bool Scheduler::select() {
    if (schCtx.pNodesPool->allCompleted()) { // all simulation nodes have finished their simulation.
        // dump time line if time line is enabled.
        char buffer[50] = {'\0'};
        sprintf(buffer, "debug_timeline_%d.dump", kiwi::mpiUtils::ownRank);
        stopwatch::dumpToFile(std::string(buffer));
        return false;
    }

    // select one node can be simulated.
    SimulationNode *pickedNode = nullptr;
    while (true) {
        pthread_mutex_lock(&(ctx._t_mu)); // lock
        pickedNode = pickup->pickRunnable(); // read queue
        if (pickedNode == nullptr) {
            stopwatch::appendToTimeLineNow(stopwatch::STOP_ID_NONE, stopwatch::STOP_STEP_NONE,
                                           stopwatch::EventSignals::EVENT_SIGNAL_WAITING);
            ctx._t_waiting++;
            pthread_cond_wait(&(ctx._t_cond), &(ctx._t_mu));
            ctx._t_waiting--;
            pthread_mutex_unlock(&(ctx._t_mu)); // lock
            stopwatch::appendToTimeLineNow(stopwatch::STOP_ID_NONE, stopwatch::STOP_STEP_NONE,
                                           stopwatch::EventSignals::EVENT_SIGNAL_RESUME);
            continue;
        } else {
            schCtx.curNode = pickedNode;
            // got/picked up a runnable node, log this moment.
            stopwatch::appendToTimeLineNow(schCtx.curNode->id, schCtx.curNode->_time_steps,
                                           stopwatch::EventSignals::EVENT_SIGNAL_PICKED);
            // Dequeue upstreams // write queue
            // the task queue must have data (because pickRunnable returns non-null pointer).
            // and the other thread only add data to task queue (don't remove data).
            if (!pickedNode->isRiverOrigin()) {
                std::list<TypeRouting> routingData = schCtx.curNode->upstream.deQueue();
            }

            pthread_mutex_unlock(&(ctx._t_mu)); // lock
            return true;
        }
    }
}

void Scheduler::postStep() {
    schCtx.curNode->_time_steps++;
    schCtx.pNodesPool->updateStatusAllCompleted(schCtx._total_steps); // update

    stopwatch::appendToTimeLineNow(schCtx.curNode->id, schCtx.curNode->_time_steps,
                                   stopwatch::EventSignals::EVENT_SIGNAL_FINISH); // finish one step, log this time.
//    kiwi::logs::i("schedule", "\tnode_id: {0}\t steps:{1}/{2}\tcom-status:{3}\tnodes_couts:{4}\n",
//                  schCtx.curNode->id,
//                  schCtx.curNode->_time_steps,
//                  schCtx._total_steps,
//                  schCtx.pNodesPool->allCompleted(), 0);
//                  schCtx.pNodesPool->simulationNodes->size());
}
