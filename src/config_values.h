//
// Created by genshen on 6/30/18.
//

#ifndef PNOHS_CONFIG_VALUES_H
#define PNOHS_CONFIG_VALUES_H


#include "config/config.h"

class ConfigValues {
public:
    // config property here

    /**
     * the total simulation time steps.
     */
    unsigned long simulationTimeSteps = 0;

    /**
     * the path of binary dispatch file.
     * The dispatch file specified how the whole simulation sub-basins(simulation nodes) are dispatched to every processors(MPI rank).
     */
    std::string dispatchFilePath;


    /** pickup strategy in scheduler.
     * This term specified how the scheduler pickup a runnable simulation node in all available simulation nodes
     * to perform simulation.
     */
    std::string pickupStrategy;

    void packConfig(kiwi::Bundle &bundle);

    void unpackConfig(kiwi::Bundle &bundle);

    static const std::string DefaultPickupStrategy;
};


#endif //PNOHS_CONFIG_VALUES_H
