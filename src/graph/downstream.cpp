//
// Created by genshen on 2018-03-26.
//

#include "downstream.h"

void Downstream::putDownMetaStream(const StreamMeta &meta) {
    DownstreamNode downstream = DownstreamNode();
    downstream.id = meta.id;
    downstream.location = meta.location;
    nodes.push_back(downstream);
}
