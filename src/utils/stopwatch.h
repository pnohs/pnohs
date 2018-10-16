//
// Created by genshen on 7/1/18.
//

#ifndef PNOHS_STOPWATCH_H
#define PNOHS_STOPWATCH_H

/**
 * the time line.
 */
#include <list>
#include <fstream>

/**
 * stopwatch is used to record the events and event time
 * while carrying on simulation node selection.
 */
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
    extern std::list<event> time_line;

    /**
     * If @var enabled is true, then the events will be saved to @var time_line.
     * when function @fn appendToTimeLine is called.
     * otherwise, the event will be ignored (events will not be record).
     */
    extern bool enabled;

    /**
     * set @var enabled.
     * @param enabled
     */
    void setStopWatchEnabled(bool enabled);

    /**
     * this method returns current clock time, which is used as default param for {@function appendToTimeLine}.
     * @return current clock time.
     */
    long defaultWatch();

    /**
     * Add an event to @var time line if stopwatch option @var enabled is enabled.
     * You can customize the function of getting current clock time.
     * @param id river sub-basin id.
     * @param step simulation step of current node.
     * @param signal signal type.
     * @param watch the function returns current clock time.
     */
    void appendToTimeLine(long id, long step, int signal, long (*watch)() = defaultWatch);

    /**
     * dump all event data to filesystem.
     * @param filename filename of dump file.
     */
    void dumpToFile(const std::string &filename);

    /**
     * clean all event data saved in list @var time_line.
     */
    void deleteAllEvent();

};


#endif //PNOHS_STOPWATCH_H
