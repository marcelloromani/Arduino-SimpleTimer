# SimpleTimer

This is (yet another) simple library to launch timed actions.

It's based on millis(), thus it has 1 ms resolution.

It uses polling, so no guarantee can be made about the exact time when a callback is fired. For example, if you setup the library so that it calls a function every 2ms, but this function requires 5ms to complete, then you'll have an invocation every 5ms.

For applications where non-strict timing is enough, not using interrupts avoids potential problems with global variables shared between the interrupt service routine and the main program, and doesn't consume a hardware timer. 

There's also a fork of SimpleTimer which also supports std::function or lambda-expressions known from C++11. See: https://github.com/schinken/SimpleTimer

# Library page on Arduino.cc

http://playground.arduino.cc/Code/SimpleTimer
