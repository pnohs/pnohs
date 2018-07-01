//
// Created by genshen on 7/1/18.
//

#ifndef PNOHS_STOPWATCH_H
#define PNOHS_STOPWATCH_H

/**
 * the time line.
 */
#include <list>
#include <string>
#include <ctime>
#include <fstream>
#include "../building_config.h"

namespace stopwatch {
    const int STOP_ID_NONE = -1;
    const int STOP_STEP_NONE = -1;
    // event types.
    enum EventSignals {
        EVENT_SIGNAL_WAITING,
        EVENT_SIGNAL_RESUME,
        EVENT_SIGNAL_PICKED,
        EVENT_SIGNAL_FINISH,
    };


    class event {
    public:
        long clock_t; // the processor time consumed by the program.
        long id; // node id of river sub-basin (set to -1 to ignore it).
        long step; // simulation step of this node (set to -1 to ignore it).
        int signal; // the tag for identifying different types of stops.
        friend std::ostream &operator<<(std::ostream &out, const event &e);
    };

    std::ostream &operator<<(std::ostream &out, const stopwatch::event &e) {
        out << e.clock_t << " " << e.id << " " << e.step << " " << e.signal << std::endl;
        return out;
    }

    std::list<event> time_line; // todo release mem.

    /**
     * add an event to time line.
     * @param id river sub-basin id.
     * @param signal signal type.
     */
    inline void appendToTimeLineNow(long id, long step, int signal) {
#ifdef BUILDING_DEBUG_MODE
        time_line.push_back(event{clock(), id, step, signal});
#endif
    }

    inline void dumpToFile(const std::string &filename) {
#ifdef BUILDING_DEBUG_MODE
        std::ofstream ofs(filename);
        if (!ofs.good()) {
            return;
        }

        // write data.
        for (event &e : time_line) {
            ofs << e;
        }
        ofs.flush();
        ofs.close();
#endif
    }

    inline void deleteAllEvent() {
#ifdef BUILDING_DEBUG_MODE
        time_line.clear();
#endif
    }

};


#endif //PNOHS_STOPWATCH_H
