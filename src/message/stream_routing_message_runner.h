//
// Created by genshen on 4/7/18.
//

#ifndef PNOHS_STREAM_ROUTING_MESSAGE_RUNNER_H
#define PNOHS_STREAM_ROUTING_MESSAGE_RUNNER_H


#include <io/io_writer.h>
#include <event/message_runner.h>
#include "../nodes_pool.h"
#include "../context.h"

/**
 * In our implementation,
 * the all callback functions below will runs in a new thread.
 */
class StreamRoutingMessageRunner : public kiwi::MessageRunner {
public:
    StreamRoutingMessageRunner(Context &ctx, NodesPool *pPool);

    bool shouldDetach() const override;

    bool filter(MPI_Status *pStatus) override;

    void onMessage(MPI_Status *pStatus) override;

private:
    Context &ctx;
    NodesPool *pNodesPool;
};


#endif //PNOHS_STREAM_ROUTING_MESSAGE_RUNNER_H
