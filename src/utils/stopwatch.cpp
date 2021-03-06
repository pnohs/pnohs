//
// Created by genshen on 7/3/18.
//

#include <string>
#include <ctime>
#include <fstream>

#include "stopwatch.h"
#include "../building_config.h"

#ifdef PNOHS_MPI_ENABLED

#include <mpi.h>

#endif

std::list<stopwatch::event> stopwatch::time_line;
bool stopwatch::enabled=false;

void stopwatch::setStopWatchEnabled(bool enabled) {
    stopwatch::enabled = enabled;
}

long stopwatch::defaultWatch() {
#ifdef PNOHS_MPI_ENABLED
    return static_cast<long>(1000 * MPI_Wtime());
#else
    return clock();
#endif
}

void stopwatch::appendToTimeLine(long id, long step, int signal, long (*watch)()) {
    // if time line (stopwatch) is disabled, function appendToTimeLine will do nothing.
    if (!stopwatch::enabled) {
        return;
    }
    time_line.push_back(event{watch(), id, step, signal});
//    std::cout << event{watch(), id, step, signal};
}

void stopwatch::dumpToFile(const std::string &filename) {
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
}

void stopwatch::deleteAllEvent() {
    time_line.clear();
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
