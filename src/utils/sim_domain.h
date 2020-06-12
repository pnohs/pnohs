//
// Created by genshen on 8/2/18.
//

#ifndef PNOHS_SIM_DOMAIN_H
#define PNOHS_SIM_DOMAIN_H

#include <utils/mpi_utils.h>

struct domain {
    /**
     * mpi_sim_process is the simulation domain used in simulation.
     * the processes in this domain (mpi communicator) would compute several nodes together.
     */
    static kiwi::mpi_process mpi_sim_process;

    /**
     * set mpi_sim_process by mpi communicator.
     * @param comm the mpi communicator for simulation.
     */
    void setCommDomain(MPI_Comm comm);
};

#endif //PNOHS_SIM_DOMAIN_H
