//
// Created by genshen on 4/9/18.
//

#ifndef PNOHS_TYPE_ROUTING_H
#define PNOHS_TYPE_ROUTING_H

#include <vector>
#include <utils/bundle.h>
#include <utils/data_def.h>
#include "../utils/predefine.h"

/**
 * basic data type for river/stream routing communication among processors.
 */
struct TypeRouting {
    // todo: use vector pointer to reduce data copy
    typedef std::vector<double> tp_routing_data;

    /**
     * Considering deliver routing results to its downstream node, denoted as D,
     * the source_id is the id of the upstream node of D.
     */
    _type_node_id source_id;

    /**
     * destination_id is the id of downstream node D.
     */
    _type_node_id destination_id;

    /**
     * stream routing data.
     */
    tp_routing_data routing_data;

    TypeRouting() = default;

    TypeRouting(_type_node_id source, _type_node_id des);

    /**
     * send routing data to target MPI rank
     * \param target_rank the target MPI rank to receive the message
     * \param comm the communication domain
     */
    void routingSend(const kiwi::RID target_rank, const MPI_Comm comm);

    /**
     * receive routing data from MPI message using MPI_Recv or MPI_Mrecv
     */
    template<bool USE_MPI_MRECV>
    void routingRecv(MPI_Status *p_status, MPI_Message *p_message, MPI_Comm comm);
};

template<bool USE_MPI_MRECV>
void TypeRouting::routingRecv(MPI_Status *p_status, MPI_Message *p_message, MPI_Comm comm) {
    int num_recv = 0;
    MPI_Get_count(p_status, MPI_BYTE, &num_recv);
    kiwi::Bundle bundle(num_recv);

    if (USE_MPI_MRECV) {
        MPI_Mrecv(bundle.getPackedData(), num_recv, MPI_BYTE, p_message, p_status);
    } else {
        MPI_Recv(bundle.getPackedData(), num_recv, MPI_BYTE, p_status->MPI_SOURCE,
                 TagStreamRoutingMessage, comm, MPI_STATUS_IGNORE); // todo use type: TypeRouting
    }

    int cursor = 0;
    size_t size_routing_data = (num_recv - sizeof(source_id) - sizeof(destination_id)) / sizeof(tp_routing_data);
    bundle.get(cursor, source_id);
    bundle.get(cursor, destination_id);
    routing_data.resize(size_routing_data);
    bundle.get(cursor, *routing_data.data());
    bundle.freePackBuffer();
}


#endif //PNOHS_TYPE_ROUTING_H
