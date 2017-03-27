/*
 * SimpleTimer.h
 *
 * SimpleTimer - A timer library for Arduino.
 * Author: mromani@ottotecnica.com
 * Copyright (c) 2010 OTTOTECNICA Italy
 *
 * Modifications by Bill Knight <billk@rosw.com> 18March2017
 *
 * This library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser
 * General Public License along with this library; if not,
 * write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */


#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

typedef void (*timer_callback)(void *);

class SimpleTimer {

public:
    // maximum number of timers
    const static int MAX_TIMERS = 10;

    // setTimer() constants
    const static int RUN_FOREVER = 0;
    const static int RUN_ONCE = 1;

    // constructor
    SimpleTimer();

    // this function must be called inside loop()
    void run();

    // Timer will call function 'f' with parameter 'p' every 'd' milliseconds forever
	// returns the timer number (numTimer) on success or
	// -1 on failure (f == NULL) or no free timers
    int setInterval(unsigned long d, timer_callback f, void* p = NULL);

    // Timer will call function 'f' with parameter 'p' after 'd' milliseconds one time
	// returns the timer number (numTimer) on success or
	// -1 on failure (f == NULL) or no free timers
    int setTimeout(unsigned long d, timer_callback f, void* p = NULL);

    // Timer will call function 'f' with parameter 'p' every 'd' milliseconds 'n' times
	// returns the timer number (numTimer) on success or
	// -1 on failure (f == NULL) or no free timers
    int setTimer(unsigned long d, timer_callback f, unsigned n, void* p = NULL);

    // destroy the specified timer
    void deleteTimer(unsigned numTimer);

    // restart the specified timer
    void restartTimer(unsigned numTimer);

    // returns true if the specified timer is enabled
    boolean isEnabled(unsigned numTimer);

    // enables the specified timer
    void enable(unsigned numTimer);

    // disables the specified timer
    void disable(unsigned numTimer);

    // enables the specified timer if it's currently disabled,
    // and vice-versa
    void toggle(unsigned numTimer);

    // returns the number of used timers
    unsigned getNumTimers();

    // returns the number of available timers
    unsigned getNumAvailableTimers() { return MAX_TIMERS - numTimers; };

private:
    // deferred call constants
    const static int DEFCALL_DONTRUN = 0;       // don't call the callback function
    const static int DEFCALL_RUNONLY = 1;       // call the callback function but don't delete the timer
    const static int DEFCALL_RUNANDDEL = 2;     // call the callback function and delete the timer

    // find the first available slot
    int findFirstFreeSlot();

    // value returned by the millis() function
    // in the previous run() call
    unsigned long prev_millis[MAX_TIMERS];

    // pointers to the callback functions
    timer_callback callbacks[MAX_TIMERS];

	// function parameters
	void *params[MAX_TIMERS];

    // delay values
    unsigned long delays[MAX_TIMERS];

    // number of runs to be executed for each timer
    unsigned maxNumRuns[MAX_TIMERS];

    // number of executed runs for each timer
    unsigned numRuns[MAX_TIMERS];

    // which timers are enabled
    boolean enabled[MAX_TIMERS];

    // deferred function call (sort of) - N.B.: this array is only used in run()
    unsigned toBeCalled[MAX_TIMERS];

    // actual number of timers in use
    unsigned numTimers;
};

#endif
