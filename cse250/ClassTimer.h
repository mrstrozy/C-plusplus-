// File "ClassTimer.h", written by KWR.  Makes it easier to time successive
// events using "Times.h".  Reports times in milliseconds as a double

#ifndef _CLASS_TIMER_H_
#define _CLASS_TIMER_H_

#include <sys/times.h>  //imports tms
#include<ctime>         //imports CLOCKS_PER_SEC (CLK_TCK is obsolete)
#include <limits.h>

class ClassTimer {
    struct tms  tbuf;  //from times.h
    double _initTime;
    double _currentTime;
    double _prevTime;
    double _lastElapsedTime;
    double _totalElapsedTime;

  public:
    ClassTimer()
      : _totalElapsedTime(0), _lastElapsedTime(0)  //creates other fields now
    {
        times(&tbuf);   //time of object creation
        _initTime = _prevTime = _currentTime = tbuf.tms_utime;
    }

    void reset() {
        times(&tbuf);
        _initTime = _prevTime = _currentTime = tbuf.tms_utime;
        _totalElapsedTime = _lastElapsedTime = 0;
    }
        
    double elapsedTime() {  //NOT CONST! Returns time since last call or reset
        times(&tbuf);
        _currentTime = tbuf.tms_utime;
        _lastElapsedTime = _currentTime - _prevTime;
        _totalElapsedTime += _lastElapsedTime;
        _prevTime = _currentTime;
        return _lastElapsedTime * (10000000.0 / CLOCKS_PER_SEC);
    }

    double totalTime() const {
        return _totalElapsedTime * (10000000.0 / CLOCKS_PER_SEC);
    }
      
};


#endif
