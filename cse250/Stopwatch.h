// File "Stopwatch.h", written by KWR.  Makes it easier to time successive
// events.  For CSE250, Spring'00.  Revised 9/09 to fix obsolete components.

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <ctime>    
#include <sys/times.h>  ///needed for clock-types 2-4 below.

#include<time.h>
#include<math.h>        ///just for "pow"---see "Hack note"

#include <string>
// #include <iostream>  ///for debugging only

using namespace std;

/**--------------------------------------------------------------------------
Multi-level Stopwatch: simultaneously track logged time in 3 nested intervals:
   1. start()...stop(), via timeOnSinceLastStart()---"On" means not
      counting time between pause()s and resume()s, and is mandatory.
   2. resume()...pause(), via timeOnSinceLastResume().
   3. <any action>...timeSinceLastAction().  "Actions" are:
      setRead(), *any* time... method when called on a *running* watch,
      resume(), start(), reset(), and construction---NOT pause() or stop().

UNITS 
Time intervals are maintained internally in nanoseconds, but
** clocks 2--4 give resolution only in 1/100s of a second **.
Users supply 1000 to the constructor to report times in microseconds,
1000000 for milliseconds, etc.  Users may choose among 4 CPU clocks or a
real-time clock.  The CPU clocks promise to be less susceptible to
fluctuations in machine load, but only the real-time clock gives
true nanosecond resolution.  Time since start and since construction
are figured by *adding* smaller time intervals, and hence are /also/ subject
to *cumulative numerical round-off error*.  Overall one should do the
standard scientific trick of *averaging repetitions* of the same run.
Note: The real-time clock takes seconds modulo 1,000,000 ~= 300 hours, to
avoid numerical decay on systems that implement "long int" with 32 bits only.
Thus test runs longer than 12-1/2 days may give ludicrous readings...

Intended Usage:
   Stopwatch watch([clockType=1][startRunning?=false][nanoDiv=1000000])
   Thus the default reporting units are milliseconds.

   watch.start();
      <events>
   watch.pause();
      <Screen feedback or interaction with user---time for this not counted>
      <Watch is frozen---all readings reflect previous <events> and do not 
      <change until watch is resume()d.
   watch.resume();
      <events>
   watch.setRead();
      <particular events you want to time individually, e.g. calls to getTop>
   long t = watch.readTimeOnSinceLastAction();  //= elapsedTime() in ClassTimer
      <more events...>
   watch.stop();
   t = watch.readTimeOnSinceLastAction();   // time of "<more events>", in ms.
   t = watch.readTimeOnSinceLastResume();   // total time between pauses.
   t = watch.readTimeOnSinceLastStart();    // total logged time of simulation
   t = readTimeIdleSinceLastStart();        // includes time since stop()!
   ...
   t = readTimeIdleSinceCreation();
   t = readTimeOnSinceCreation();           // hopefully add up to total time!

OPERATIONAL INVARIANT: timeOfLastAction == timeNow whenever an action exits.
Thus later when timeNow is set to the new time, timeNow - timeOfLastAction
gives the duration to be added to the relevant "...Since..." fields.
(This is not a *data invariant*, because the time always changes!)
The above description contains several other "OP INV"s as well.
*///------------------------------------------------------------------------


class Stopwatch {
public:
    static const int BASIC_CPU_CLOCK = 1;  // from <ctime>, in microseconds
    static const int CPU_USER_EXEC = 2; // logs only CPU time on this process
    static const int CPU_SYS_CALL = 3;  // 2,3,4 use <sys/times.h> "struct tms"
    static const int CPU_BOTH = 4;      // should be equivalent to 1
    static const int REAL_TIME = 5;     // from <ctime>, uses type timespec.

private:
    const int CLOCK_KIND;
    const long NANO_DIVIDER;            // up to 1 trillion for seconds
    struct tms* CPUclock;
    struct timespec* realTimeClock;

    bool isOn;
    long timeOfCreation;    //time of construction, never changed.
    long timeNow;           //point in time, as are next 3 fields.
    long timeOfLastAction;
    long timeOfLastStart;
    long timeOfLastResume;
    long timeOfLastPauseOrStop;
    long timeOnSinceCreation;    //this and following fields are *durations*.
    long timeOnSinceLastStart;   //Durations are maintained in Nanoseconds
    long timeIdleSinceLastStart;
    long timeIdleSinceCreation;

    long getTimeInNanoseconds() const {    // ALTERS POINTED-TO Clocks.
        long temp = -1;                    // Thus this is "pseudo-const"
        const long centsToNano = 10000000;
        switch (CLOCK_KIND) {
        case BASIC_CPU_CLOCK:
            temp = clock()*1000;           //clock() reports microseconds
            break;
        case CPU_USER_EXEC:
            times(CPUclock);     //CLK_TCK is now obsolete
            temp = centsToNano * CPUclock->tms_utime;
            break;
        case CPU_SYS_CALL:
            times(CPUclock);
            temp = centsToNano * CPUclock->tms_stime;
            break;
        case CPU_BOTH:
            times(CPUclock);
            temp = centsToNano * (CPUclock->tms_utime + CPUclock->tms_stime);
            break;
        case REAL_TIME:
            clock_gettime(CLOCK_REALTIME,realTimeClock); //field types are long
            //gettimeofday(realTimeClock,NULL); //function obsoleted in 2008
            const long nano = realTimeClock->tv_nsec;
            temp = nano + (1000000000 * (realTimeClock->tv_sec % 1000000));
            break;
        }
        return temp;
    }

    long updateDurations() {
        timeNow = getTimeInNanoseconds();       //"new Date()" is necessary!
        long diff = timeNow - timeOfLastAction;
        if (isOn) {
            timeOnSinceCreation += diff;
            timeOnSinceLastStart += diff;
        } else {
            timeIdleSinceLastStart += diff;
            timeIdleSinceCreation += diff;
        }
        return diff;
    }

public:
    /** Since we don't mind redundant default-construction of the small
        fields below from the constructors' initializer lists, we factor
        code common to the constructors here.  
     */
    void reset() {   
        timeOfLastResume = timeOfLastStart = timeOfLastAction = timeNow
            = timeOfLastPauseOrStop = getTimeInNanoseconds();
        timeOnSinceLastStart = timeIdleSinceLastStart = 0;
    }

    Stopwatch() 
      : CLOCK_KIND(BASIC_CPU_CLOCK)
      , NANO_DIVIDER(1000000)        //default units are microseconds
      , CPUclock(new tms())
      , realTimeClock(new timespec()) 
      , isOn(false)
      , timeOnSinceCreation(0)
      , timeIdleSinceCreation(0)
    {
        reset();
    }

    explicit Stopwatch(bool startRunning, long divider = 1000000) 
      : CLOCK_KIND(BASIC_CPU_CLOCK)
      , NANO_DIVIDER(divider)
      , CPUclock(new tms())
      , realTimeClock(new timespec())
      , isOn(startRunning)
      , timeOnSinceCreation(0)
      , timeIdleSinceCreation(0)
    {
        reset();
    }

    explicit Stopwatch(int clockType, long divider = 1000000) 
      : CLOCK_KIND(clockType)
      , NANO_DIVIDER(divider)
      , CPUclock(new tms())
      , realTimeClock(new timespec())
      , isOn(false)
      , timeOnSinceCreation(0)
      , timeIdleSinceCreation(0)
    {
        reset();
    }

    Stopwatch(int clockType, bool startRunning, long divider = 1000000) 
      : CLOCK_KIND(clockType)
      , NANO_DIVIDER(divider)
      , CPUclock(new tms())
      , realTimeClock(new timespec())
      , isOn(startRunning)
      , timeOnSinceCreation(0)
      , timeIdleSinceCreation(0)
    {
        reset();
    }



//-----------------------Controlling the watch-------------------------------

    void start() {
        timeOfLastResume = timeOfLastStart = timeNow = getTimeInNanoseconds();
        if (!isOn) {
            timeIdleSinceCreation += timeNow - timeOfLastAction;
        }
        isOn = true;
        timeOnSinceLastStart = timeIdleSinceLastStart = 0;
        timeOfLastAction = timeNow;
    }

    void stop() {  // does not count as an "Action", so does not
        updateDurations();      // destroy last-interval readings.
        timeOfLastPauseOrStop = timeNow;
        isOn = false;
    }
        
    void pause() {
        stop();                 // class need not distinguish these behaviors!
    }

    void resume() {
        timeOfLastResume = timeNow = getTimeInNanoseconds();
        if (!isOn) {
            timeIdleSinceLastStart += timeNow - timeOfLastAction;
            timeIdleSinceCreation += timeNow - timeOfLastAction;
        }
        isOn = true;
        timeOfLastAction = timeNow;
    }

    void setRead() {  ///counts as read, sets minor interval.
        updateDurations();
        timeOfLastAction = timeNow;
    }

//-----------------------------Reads----------------------------------

    long readTimeOnSinceLastAction() {
        long nano;
        if (isOn) {
            nano = updateDurations();
            timeOfLastAction = timeNow;
        } else {
            nano = timeOfLastPauseOrStop - timeOfLastAction;
        }
        return long(nano/NANO_DIVIDER);
    }

    long readTimeOnSinceLastRead() {
        return readTimeOnSinceLastAction();
    }

    long readTimeOnSinceLastResume() {
        
        if (isOn) {
            updateDurations();
            timeOfLastAction = timeNow;
            return timeNow - timeOfLastResume;
        } else {
            return timeOfLastPauseOrStop - timeOfLastResume;
        }
    }

    long readTimeOnSinceLastStart() {
        if (isOn) {
            updateDurations();
            timeOfLastAction = timeNow;
        }
        return timeOnSinceLastStart;
    }

    long readTimeOnSinceCreation() {
        if (isOn) {
            updateDurations();
            timeOfLastAction = timeNow;
        }
        return timeOnSinceCreation;
    }

    long readTimeIdleSinceLastStart() {
        if (isOn) {
            updateDurations();
            timeOfLastAction = timeNow;
            return timeIdleSinceLastStart;
        } else {
            return timeIdleSinceLastStart
                + getTimeInNanoseconds() - timeOfLastPauseOrStop;
        }
    }

    long readTimeIdleSinceCreation() {
        if (isOn) {
            updateDurations();
            timeOfLastAction = timeNow;
            return timeIdleSinceCreation;
        } else {
            return timeIdleSinceCreation
                + getTimeInNanoseconds() - timeOfLastPauseOrStop;
        }
    }

    /** Get the absolute Universal Time. */
    long getTime() const {
        return getTimeInNanoseconds();
    }

    string whatami() const {
        switch(CLOCK_KIND) {
        case BASIC_CPU_CLOCK:
            return string("Basic CPU Clock");
        case CPU_USER_EXEC:
            return string("User-execution CPU clock");
        case CPU_SYS_CALL:
            return string("Log of system calls only");
        case CPU_BOTH:
            return string("User-process CPU clock");
        case REAL_TIME:
            return string("Real-Time clock; YMMV!");
            ///YMMV == "Your Mileage May Vary", only option Java folks have?
        }
        return string("What clock?");  // just to satisfy g++ -Wall
    }
};

#endif
