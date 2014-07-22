
#include "timing_SR.h"

/*------------------------------------------------------------------------------
 * Timing()
 * Constructor.
 *----------------------------------------------------------------------------*/

Timing::Timing(float _period)
{
    period = _period;
    Setup();
} // end Timing()


/*------------------------------------------------------------------------------
 * ~Timing()
 * Destructor.
 *----------------------------------------------------------------------------*/

Timing::~Timing()
{
} // end ~Timing()


/*------------------------------------------------------------------------------
 * void Setup()
 * Sets up a timer.
 *----------------------------------------------------------------------------*/

void Timing::Setup()
{
    // Set timer to the current system time.
    Set();

    // Initialize variables.
    expired = false;
} // end Setup()


/*------------------------------------------------------------------------------
 * float CheckExpired()
 * Check if a period (in seconds) has elapsed for a timer.
 *----------------------------------------------------------------------------*/

bool Timing::CheckExpired()
{
    // Declare variables.
    struct timeval t = {0, 0};
    int t1 = 0;
    int t2 = 0;

    // Get the current system time.
    gettimeofday(&t, NULL);

    // Convert times to microseconds.
    t1 = (s * 1000000) + us;
    t2 = (t.tv_sec * 1000000) + t.tv_usec;

    // Check to see if period has elapsed.
    if (t2 - t1 > (period * 1000000))
    {
        expired = true;
    }
    else
    {
        expired = false;
    }

    return expired;
} // end CheckExpired()


/*------------------------------------------------------------------------------
 * int Set()
 * Sets a timer to the current system time.
 *----------------------------------------------------------------------------*/

void Timing::Set()
{
    // Declare variables.
    struct timeval t = {0, 0};

    // Get the current system time.
    gettimeofday(&t, NULL);

    // Set timer to the current system time.
    s  = t.tv_sec;
    us = t.tv_usec;
} // end Set()


/*------------------------------------------------------------------------------
 * int GetDt()
 * Get the time elapsed for a given timer. Return the elapsed time in another
 * TIMING element.
 *----------------------------------------------------------------------------*/

int Timing::GetDt()
{
    // Declare variables.
    struct timeval t = {0, 0};
    int elapsedSec = 0;
    int elapsedUsec = 0;

    // Get the current system time.
    gettimeofday(&t, NULL);

    // Check to see which fraction of a second is larger.
    if (t.tv_usec > us)
    {
        elapsedSec = s - t.tv_sec;
        elapsedUsec = 1000000 + us - t.tv_usec;
        // This should never happen. If it does then there is a problem with the system time.
        if (elapsedSec < 0)
            return TIMING_ERROR;
    }
    else
    {
        elapsedSec = s - t.tv_sec;
        elapsedUsec = us - t.tv_usec;
    }

    return elapsedSec * 1000000 + elapsedUsec;
} // end GetDt()


/*------------------------------------------------------------------------------
 * float GetDtS()
 * Get the time elapsed for a given timer in seconds.
 *----------------------------------------------------------------------------*/

float Timing::GetDtS()
{
    // Declare variables.
    struct timeval t = {0, 0};
    int t1 = 0;
    int t2 = 0;

    // Get the current system time.
    gettimeofday(&t, NULL);

    // Convert times to microseconds.
    t1 = s * 1000000 + us;
    t2 = t.tv_sec * 1000000 + t.tv_usec;

    // Return time in seconds.
    return (float)(t2 - t1) / 1000000.;
} // end GetDtS()
