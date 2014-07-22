#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#ifndef SR_TIMING_H
#define SR_TIMING_H

/******************************
 *
 * #defines
 *
 *****************************/

#ifndef TIMING_RETURN_VALS
#define TIMING_SUCCESS			1
#define TIMING_ERROR			0
#endif /* RETURN_VALS */


/******************************
 *
 * Classes
 *
 *****************************/

class Timing 
{
public:
    //! Constructor.
    //! \param setup_baud The baud rate that the serial port should be opened at.
    //! \param setup_portname The name of the serial port.
    Timing(float _period);

    //! Destructor.
    ~Timing();

    //! Initializes a timer.
    void Setup();

    //! Checks to see if time has elapsed.
    //! \return true if period has passed, else false.
    bool CheckExpired();
    
    //! Sets a timer to the current system time.
    void Set();
    
    //! Computes elapsed time for a given timer.
    //! \return The elapsed time in microseconds.
    int GetDt();
    
    //! Get the time elapsed for a given timer in seconds.
    //! \return The time elapsed in seconds as a float.
    float GetDtS();
    
    //! Time in microseconds.
    int us;
   
    //! Time in seconds.
    int s;

    //! Period before timer expires, in seconds.
    float period;

    //! Whether timer has expired or not.
    bool expired;
};

#endif /* SR_TIMING_H */
