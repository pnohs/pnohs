//
// Created by genshen on 6/30/18.
//

#include "config_values.h"

const std::string ConfigValues::DefaultPickupStrategy = "ring";

void ConfigValues::packConfig(kiwi::Bundle &bundle) {
    bundle.put(dispatchFilePath);
    bundle.put(simulationTimeSteps);
    bundle.put(pickupStrategy);
}

void ConfigValues::unpackConfig(kiwi::Bundle &bundle) {
    int cursor = 0;
    bundle.get(cursor, dispatchFilePath);
    bundle.get(cursor, simulationTimeSteps);
    bundle.get(cursor, pickupStrategy);
}
