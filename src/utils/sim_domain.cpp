//
// Created by genshen on 8/2/18.
//

#include "sim_domain.h"

kiwi::mpi_process domain::mpi_sim_process;

void domain::setCommDomain(MPI_Comm comm) {
    mpi_sim_process.comm = comm;
    MPI_Comm_rank(comm, &mpi_sim_process.own_rank);
    MPI_Comm_size(comm, &mpi_sim_process.all_ranks);
}
