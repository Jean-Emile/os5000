#ifndef SR_OS5000_H
#define SR_OS5000_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serial_SR.h"
#include "timing_SR.h"

/******************************
 *
 * #defines
 *
 *****************************/

/* Command Set Summary for the Ocean Server compass. */
#ifndef OS5000_COMMANDS
#define OS5000_COMMANDS
/** @name Command values for the compass. */
//@{
#define OS5000_CMD_ESC             '\x1b'
#define OS5000_CMD_SET_BAUD        'B'
#define OS5000_CMD_SET_RATE        'R'
#define OS5000_CMD_SET_FIELDS      'X'
#define OS5000_CMD_GET_FIRMWARE    'V'
#define OS5000_CMD_SET_ORIENTATION 'E'
#define OS5000_CMD_GET_CONFIG      '&'
#define OS5000_CMD_END             '\r'
//@}
#endif // OS5000_COMMANDS

#ifndef OS5000_DELIM
#define OS5000_DELIM " $CPRT*\n\r"
#endif // OS5000_DELIM

#ifndef OS5000_STRING_SIZE
#define OS5000_STRING_SIZE 128
#endif // OS5000_STRING_SIZE

#ifndef OS5000_SERIAL_DELAY
#define OS5000_SERIAL_DELAY 100000
#endif // OS5000_SERIAL_DELAY

#ifndef OS5000_RESPONSE
#define OS5000_RESPONSE_START  '$'
#define OS5000_RESPONSE_END    '*'
#endif // OS5000_RESPONSE

#ifndef OS5000_ERROR_HEADER
#define OS5000_SUCCESS	        1
#define OS5000_ERROR_HEADER    -1
#define OS5000_ERROR_CHECKSUM  -2
#define OS5000_ERROR_LENGTH    -3
#define OS5000_ERROR_VALID_MSG -4
#endif // OS5000_ERROR_HEADER

/******************************
 *
 * Classes
 *
 *****************************/

class Compass : public Serial
{
public:
    //! Constructor.
    //! \param _portname The name of the port that the compass is connected to.
    //! \param _baud The baud rate that the compass is configured to communicate at.
    //! \param _rate The rate that the compass should be set up to send messages at.
    //! \param _initTime The amount of time to try establishing communications with the compass before timing out.
    Compass(string _portname, int _baud, int _rate, int _initTime);

    //! Destructor.
    ~Compass();

    //! Establish communications with the compass.
    void Setup();

    //! Get orientation data from compass.
    void GetData();

    //! Set the rate at which messages are sent by the compass.
    //! Valid rates are from 0 - 20. Any numbers outside that range will be shifted
    //! into that range.
    void SetRate();

    //! Simulates compass data when no compass is available.
    void SimulateData();

    //! Looks for valid data from the compass for a specified amount of time.
    void Init();

    //! Serial number of the compass.
    int serialNumber;

    //! Pitch angle in units of degrees, range of (-180,180].
    float pitch;

    //! Roll angle in units of degrees, range of (-180,180].
    float roll;

    //! Yaw angle in units of degrees, range of (-180,180].
    float yaw;

    //! Temperature as measured on the compass board in units of Fahrenheit. This is not a precise measurement but does
    //! give a rough indication of the temperature.
    float temperature;

    //! The file descriptor used to communicate with the compass.
    int fd;

    //! The amount of time attempting to set up communications with the compass.
    int initTime;

    //! The rate that the compass should send out data updates.
    int rate;

    //! Pointer to a timer.
    Timing *timer;

private:
    //! Searches a buffer looking for the start and end sequences.
    void FindMsg();

    //! Parses a message for compass data.
    void ParseMsg();

    //! Whether the compass was initialized correctly.
    bool bCompassInitialized;

    //! Whether a complete message was found after reading compass data.
    bool bFoundCompleteMessage;
};

#endif // SR_OS5000_H
