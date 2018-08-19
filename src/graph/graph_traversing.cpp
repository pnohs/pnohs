//
// Created by genshen on 8/16/18.
//

#include "graph_traversing.h"


Traversing::Traversing(Graph &sub_graph) : sub_graph(sub_graph) {

}

void Traversing::resetTraversing() {
    traversing.clear();
}
