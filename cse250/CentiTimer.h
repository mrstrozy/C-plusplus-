/** File "CentiTimer.h", by KWR for CSE250, Fall 2009.  Still "mutable"?!?
    Wraps a class around basic timing functions, clarifying which times
    are clock-reads and which are *durations*, i.e. differences between reads.

    Gives only 1/100 sec. resolution :-(, despite the old value
    CLK_TCK = 100 being replaced by CLOCKS_PER_SEC = 1000000.

 */
#ifndef CENTI_TIMER_H_
#define CENTI_TIMER_H_

//#include <sys/time.h>  
#include<vector>
#include<string>
#include<time.h>
using std::string;

/** CLASS INV: prevstamp == timestamp always, except during the first 2 lines
    of updateDurations() and reset().  Note clock_t is the type of both
    "absolute" time (a clock reading) and "duration".
 */

class CentiTimer {
    //clockid_t clockID;
    double divider;
    clock_t timestamp;            //mirrors TIME0 in time.h
    clock_t prevstamp;            //mirrors TIME1 in time.h
    clock_t newInterval;          //time *difference* not stamp
    clock_t intervalSinceReset;

    void updateDurations() {
        timestamp = clock();      //deliberately first line of code
        newInterval = timestamp - prevstamp;
        prevstamp = timestamp;
        intervalSinceReset += newInterval;
        
        
/*
        //const double secondsDiff = microDiff / double(CLOCKS_PER_SEC);
        if (nanoDiff < 0) {  //nano-reader wrapped around signed long boundary
            newInterval.tv_nsec = 1000000000 + nanoDiff;
            newInterval.tv_sec = secondsDiff - 1;
        } else {
            newInterval.tv_nsec = nanoDiff;
            newInterval.tv_sec = secondsDiff;
        }
        intervalSinceReset.tv_nsec += newInterval.tv_nsec;
        intervalSinceReset.tv_sec += newInterval.tv_sec;
*/
        // FYI:
        // The "Stopwatch" class maintained a timestamp of last reset
        // because these repeated adds can increase roundoff errors,
        // but with nanosecond precision now those matter much less.
    }

  public:
    enum Units { SECONDS, MILLISECONDS, MICROSECONDS, NANOSECONDS };
    /** Default units are milliseconds
     */
    CentiTimer()
      : divider(CLOCKS_PER_SEC/1000.0)
      , timestamp(0)
      , prevstamp(0)    //overwritten
      , newInterval(0)  //meaningful
      , intervalSinceReset(0)    //meaningful
    {
        reset();
    }

    CentiTimer(Units units)
      : divider(units == SECONDS ? CLOCKS_PER_SEC
                    : (units == MILLISECONDS ? CLOCKS_PER_SEC/1000.0
                        : (units == MICROSECONDS ? CLOCKS_PER_SEC/1000000.0
                                                 : 1.0) ) ) 
      , timestamp(0)
      , prevstamp(0)    //overwritten
      , newInterval(0)  //meaningful
      , intervalSinceReset(0)    //meaningful
    {
        reset();
    }

    void reset() {
        newInterval = intervalSinceReset = 0;
        timestamp = clock();
        prevstamp = timestamp;
    }
        
    double elapsedTime() {  //NOT CONST! Returns time since last call or reset
        updateDurations();
        return newInterval / divider;
    }

    double timeSinceReset() {
        updateDurations();
        return intervalSinceReset / divider;
    }

    string getUnits() const {
        if (divider > 999999.9) {
            return "seconds";
        } else if (divider > 999.9) {
            return "milliseconds";
        } else if (divider > 0.9) {
            return "microseconds";
        } else {
            return "nanoseconds??";
        }
    }

      
};


#endif

