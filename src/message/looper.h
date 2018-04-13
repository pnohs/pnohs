//
// Created by genshen on 4/6/18.
//

#ifndef PNOHS_LOOP_H
#define PNOHS_LOOP_H


class Looper {
public:
    /**
     * Factory method to create objects
     * @return A Looper instance.
     */
    static Looper *NewMessageLooper();

private:
    Looper() = default;

    /** Method for pthread create, this method runs in a new thread.
     * It runs a loop, listen to new message, and dispatch message to different register.
     * @param args pthread arg.
     * @return pthread return.
     */
    static void *messageLoopNewThread(void *object);
};


#endif //PNOHS_LOOP_H
