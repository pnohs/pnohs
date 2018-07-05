//
// Created by genshen on 7/1/18.
//

#ifndef PNOHS_STOPWATCH_H
#define PNOHS_STOPWATCH_H

/**
 * the time line.
 */
#include <list>

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

    // declare overriding.
    std::ostream &operator<<(std::ostream &out, const event &e);

    // all events at each time step are stored here.
    extern std::list<event> time_line; // todo release mem.

    /**
     * this method returns current clock time, which is used as default param for {@function appendToTimeLine}.
     * @return current clock time.
     */
    long defaultWatch();

    /**
     * add an event to time line, which can customize the function of getting current clock time.
     * @param id river sub-basin id.
     * @param step simulation step of current node.
     * @param signal signal type.
     * @param watch the function returns current clock time.
     */
    void appendToTimeLine(long id, long step, int signal, long (*watch)() = defaultWatch);

    void dumpToFile(const std::string &filename);

    void deleteAllEvent();

};


#endif //PNOHS_STOPWATCH_H
