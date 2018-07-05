//
// Created by genshen on 7/3/18.
//

#include <string>
#include <ctime>
#include <fstream>

#include "stopwatch.h"
#include "../building_config.h"

#ifdef MPI_ENABLED

#include <mpi.h>

#endif

std::list<stopwatch::event> stopwatch::time_line;

long stopwatch::defaultWatch() {
#ifdef MPI_ENABLED
    return static_cast<long>(1000 * MPI_Wtime());
#else
    return clock();
#endif
}

void stopwatch::appendToTimeLine(long id, long step, int signal, long (*watch)()) {
#ifdef BUILDING_DEBUG_MODE
    time_line.push_back(event{watch(), id, step, signal});
#endif
}

void stopwatch::dumpToFile(const std::string &filename) {
#ifdef BUILDING_DEBUG_MODE
    std::ofstream ofs(filename);
    if (!ofs.good()) {
        return;
    }

    ofs << "# signal describe, W: waiting, R: resume, P: picked, F: finished" << std::endl;
    ofs << "time\tid\tstep\tsignal" << std::endl;
    // write data.
    for (event &e : time_line) {
        ofs << e;
    }
    ofs.flush();
    ofs.close();
#endif
}

void stopwatch::deleteAllEvent() {
#ifdef BUILDING_DEBUG_MODE
    time_line.clear();
#endif
}

std::ostream &stopwatch::operator<<(std::ostream &out, const stopwatch::event &e) {
    out << e.clock_t << " " << e.id << " " << e.step << " ";
    switch (e.signal) {
        case stopwatch::EVENT_SIGNAL_WAITING:
            out << 'W';
            break;
        case stopwatch::EVENT_SIGNAL_RESUME:
            out << 'R';
            break;
        case stopwatch::EVENT_SIGNAL_PICKED:
            out << 'P';
            break;
        case stopwatch::EVENT_SIGNAL_FINISH:
            out << 'F';
            break;

    }
    out << std::endl;
    return out;
}
