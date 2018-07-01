//
// Created by genshen on 6/30/18.
//

#include "config_values.h"

const std::string ConfigValues::DefaultPickupStrategy = "ring";

void ConfigValues::packConfig(kiwi::Bundle &bundle) {
    bundle.put(MPI_COMM_WORLD, dispatchFilePath);
    bundle.put(MPI_COMM_WORLD, simulationTimeSteps);
    bundle.put(MPI_COMM_WORLD, pickupStrategy);
}

void ConfigValues::unpackConfig(kiwi::Bundle &bundle) {
    int cursor = 0;
    bundle.get(MPI_COMM_WORLD, cursor, dispatchFilePath);
    bundle.get(MPI_COMM_WORLD, cursor, simulationTimeSteps);
    bundle.get(MPI_COMM_WORLD, cursor, pickupStrategy);
}
