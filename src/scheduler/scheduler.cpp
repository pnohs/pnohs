///
// Created by genshen on 4/9/18.
//

#include <utils/mpi_utils.h>
#include <logs/logs.h>
#include "scheduler.h"
#include "strategy_container.h"
#include "../utils/stopwatch.h"
#include "../utils/sim_domain.h"

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
        // dump time line if time line (stopwatch) is enabled.
        if (stopwatch::enabled) {
            char buffer[50] = {'\0'};
            sprintf(buffer, "debug_timeline_%d.dump", domain::mpi_sim_process.own_rank);
            stopwatch::dumpToFile(std::string(buffer));
        }
        stopwatch::deleteAllEvent(); // release event memory.
        return false;
    }

    // select one node can be simulated.
    SimulationNode *pickedNode = nullptr;
    while (true) {
        pthread_mutex_lock(&(ctx._t_mu)); // lock
        pickedNode = pickup->pickRunnable(); // read queue
        if (pickedNode == nullptr) {
            const double t1 = MPI_Wtime();
            // if time line (stopwatch) is disabled, function appendToTimeLine will do nothing.
            stopwatch::appendToTimeLine(stopwatch::STOP_ID_NONE, stopwatch::STOP_STEP_NONE,
                                        stopwatch::EventSignals::EVENT_SIGNAL_WAITING);
            ctx._t_waiting++;
            pthread_cond_wait(&(ctx._t_cond), &(ctx._t_mu));
            ctx._t_waiting--;
            pthread_mutex_unlock(&(ctx._t_mu)); // lock
            stopwatch::appendToTimeLine(stopwatch::STOP_ID_NONE, stopwatch::STOP_STEP_NONE,
                                        stopwatch::EventSignals::EVENT_SIGNAL_RESUME);
            const double t2 = MPI_Wtime();
            ctx.onThreadBlock(t2 - t1); // set blocking time.
            continue;
        } else {
            schCtx.curNode = pickedNode;
            // got/picked up a runnable node, log this moment.
            stopwatch::appendToTimeLine(schCtx.curNode->id, schCtx.curNode->_time_step,
                                        stopwatch::EventSignals::EVENT_SIGNAL_PICKED);
            pthread_mutex_unlock(&(ctx._t_mu)); // lock
            return true;
        }
    }
}

void Scheduler::postStep() {
    schCtx.pNodesPool->updateStatusAllCompleted(schCtx._total_steps); // update

    stopwatch::appendToTimeLine(schCtx.curNode->id, schCtx.curNode->_time_step,
                                stopwatch::EventSignals::EVENT_SIGNAL_FINISH); // finish one step, log this time.
//    kiwi::logs::i("schedule", "\tnode_id: {0}\t steps:{1}/{2}\tcom-status:{3}\tnodes_couts:{4}\n",
//                  schCtx.curNode->id,
//                  schCtx.curNode->_time_step,
//                  schCtx._total_steps,
//                  schCtx.pNodesPool->allCompleted(), 0);
//                  schCtx.pNodesPool->simulationNodes->size());
}
