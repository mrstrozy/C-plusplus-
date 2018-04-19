/** File "CPUTimer.h", by KWR for CSE250, Fall 2009.
    Wraps a class around basic timing functions, clarifying which times
    are clock-reads and which are *durations*, i.e. differences between reads.
    Assumes 64-bit longs (or higher), may break on old Windows setups
 */

#ifndef CPU_TIMER_H_
#define CPU_TIMER_H_

#include <vector>
#include <string>
#include <time.h>  
using std::string;


class CPUTimer {
    clockid_t clockID;
    double nanoDivider;
    struct timespec* const timestamp;     //standard calls require a pointer
    struct timespec prevStamp;            //INV: == *timestamp upon update
    struct timespec newInterval;          //time *difference* not stamp
    struct timespec intervalSinceReset;

    void updateDurations() {
        clock_gettime(clockID, timestamp);//deliberately first line of code
        const long nanoDiff = timestamp->tv_nsec - prevStamp.tv_nsec;
        const time_t secondsDiff = timestamp->tv_sec - prevStamp.tv_sec;
        prevStamp = *timestamp;           //restore INV as soon as possible
        if (nanoDiff < 0) {  //nano-reader wrapped around signed long boundary
            newInterval.tv_nsec = 1000000000 + nanoDiff;
            newInterval.tv_sec = secondsDiff - 1;
        } else {
            newInterval.tv_nsec = nanoDiff;
            newInterval.tv_sec = secondsDiff;
        }
        intervalSinceReset.tv_nsec += newInterval.tv_nsec;
        intervalSinceReset.tv_sec += newInterval.tv_sec;
        // FYI:
        // The "Stopwatch" class maintained a timestamp of last reset
        // because these repeated adds can increase roundoff errors,
        // but with nanosecond precision now those matter much less.
    }

    long newIntervalInNanoseconds() const {
        return newInterval.tv_nsec + 1000000000*newInterval.tv_sec;
    }

    long sinceResetInNanoseconds() const {
        return intervalSinceReset.tv_nsec 
           + 1000000000*intervalSinceReset.tv_sec;
    }

  public:
    enum Units { SECONDS, MILLISECONDS, MICROSECONDS, NANOSECONDS };
    /** Default units are microseconds
     */
    CPUTimer()
      : clockID(CLOCK_PROCESS_CPUTIME_ID)
      , nanoDivider(1000.0)
      , timestamp(new timespec())
      , prevStamp(timespec())    //overwritten
      , newInterval(timespec())  //meaningful
      , intervalSinceReset(timespec())    //meaningful
    {
        clock_gettime(clockID, timestamp);
        prevStamp = *timestamp;     //so INV holds
    }

    CPUTimer(clockid_t clockID, Units units)
      : clockID(clockID)
      , nanoDivider(units == SECONDS ? 1000000000.0
                        : (units == MILLISECONDS ? 1000000.0
                            : (units == NANOSECONDS ? 1.0 : 1000.0) ) ) 
      , timestamp(new timespec())
      , prevStamp(timespec())    //overwritten
      , newInterval(timespec())  //meaningful
      , intervalSinceReset(timespec())    //meaningful
    {
        clock_gettime(clockID, timestamp);
        prevStamp = *timestamp;     //so INV holds
    }

    ~CPUTimer() { delete(timestamp); }
    
    /** Copy constructor clones the old reading, rather than create
        an independent timer with a new reading.  We need this code only
        so that the new timestamp pointer does not point at the old fields!
     */
    CPUTimer(const CPUTimer& rhs) 
       : clockID(rhs.clockID)
       , nanoDivider(rhs.nanoDivider)
       , timestamp(new timespec(*rhs.timestamp))  //calls trivial timspec c-ctor
       , prevStamp(rhs.prevStamp)
       , newInterval(rhs.newInterval) 
       , intervalSinceReset(rhs.intervalSinceReset)
    { }  //we do not do a new reading.

    /** Again, and graphically illustrating text's notes in Cha. 3,
        the only reason we can't allow the trivial operator= is that
        "timespec" must be a pointer---and we need its fresh fields.
     */
    CPUTimer& operator=(const CPUTimer& rhs) {
        clockID = rhs.clockID;
        nanoDivider = rhs.nanoDivider;
        //timestamp = new timespec(*rhs.timestamp);   //fresh copy
        timestamp->tv_nsec = rhs.timestamp->tv_nsec;
        timestamp->tv_sec = rhs.timestamp->tv_sec;
        prevStamp = rhs.prevStamp;
        newInterval = rhs.newInterval;
        intervalSinceReset = rhs.intervalSinceReset;
    }

    void reset() {
        newInterval = intervalSinceReset = timespec();
        clock_gettime(clockID, timestamp);
        prevStamp = *timestamp;
    }
        
    double elapsedTime() {  //NOT CONST! Returns time since last call or reset
        updateDurations();
        return newIntervalInNanoseconds() / nanoDivider;
    }

    double timeSinceReset() {
        updateDurations();
        return sinceResetInNanoseconds() / nanoDivider;
    }

    string getUnits() const {
        if (nanoDivider > 999999999.9) {
            return "seconds";
        } else if (nanoDivider > 999999.9) {
            return "milliseconds";
        } else if (nanoDivider > 999.9) {
            return "microseconds";
        } else {
            return "nanoseconds!";
        }
    }

      
};


#endif

