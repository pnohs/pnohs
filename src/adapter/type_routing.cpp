//
// Created by genshen on 4/9/18.
//

#include "type_routing.h"

TypeRouting::TypeRouting(_type_node_id source, _type_node_id des) : source_id(source), destination_id(des) {

}

void TypeRouting::routingSend(const kiwi::RID target_rank, const MPI_Comm comm) {
    size_t send_size_bytes = sizeof(source_id) + sizeof(destination_id)
                             + sizeof(tp_routing_data) * routing_data.size();
    kiwi::Bundle bundle(send_size_bytes);
    bundle.put(source_id);
    bundle.put(destination_id);
    bundle.put(routing_data.size(), routing_data.data());
    MPI_Send(bundle.getPackedData(), send_size_bytes, MPI_BYTE,
             target_rank, TagStreamRoutingMessage, comm);
    bundle.freePackBuffer();
}
