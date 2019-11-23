//
// Created by genshen on 4/7/18.
//

#ifndef PNOHS_STREAM_ROUTING_MESSAGE_RUNNER_H
#define PNOHS_STREAM_ROUTING_MESSAGE_RUNNER_H


#include <io/io_writer.h>
#include <event/message_runner.h>
#include "../adapter/type_routing.h"
#include "../sys_context.h"

/**
 * In our implementation,
 * the all callback functions below will runs in a new thread.
 */
class NodesPool;

class StreamRoutingMessageRunner : public kiwi::MessageRunner {
public:
    StreamRoutingMessageRunner(SysContext &ctx, NodesPool *pPool, const unsigned long totalSteps);

    // this function runs in main thread.
    // initialize @var _msg_upper_bound here.
    void onAttach() override;

    bool shouldDetach() const override;

    bool filter(MPI_Status *pStatus) override;

    void onMessage(MPI_Status *pStatus) override;

    void onMessage(MPI_Status *pStatus, MPI_Message *pMessage) override;

    void onDetach() override;

private:
    const unsigned long total_steps; // total simulation step of one node.

    // total messages count need to be received for all nodes,
    // the nodes which is origin of river or is located on this processor are excluded.
    unsigned long _msg_upper_bound;

    // messages count have received.
    unsigned long _msg_accumulator;

    SysContext &ctx;
    NodesPool *pNodesPool;

    /**
     * routing touing data to queue and weak up the main thread
     */
    void queueAppend(TypeRouting &up_routing);
};


#endif //PNOHS_STREAM_ROUTING_MESSAGE_RUNNER_H
