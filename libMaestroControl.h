#ifndef MAESTROLIBRARY_LIBMAESTROCONTROL_H
#define MAESTROLIBRARY_LIBMAESTROCONTROL_H
#include <unistd.h>
#include <string>
/**
 * @class MaestroControl
 * @author MatchaOnMuffins
 * @date 06/22/2022
 * @brief Class to control the Maestro Servo Controller
 * @details This class is used to control the Maestro Servo Controller.
 * <p>
 *        It can be used to set and get the position of the servo.
**/
class MaestroControl {
private:
    int fd;
    const char *device;

    /**
* @brief Reconnects if connection is lost
*
* Should only be used internally by the MaestroControl class itself.
*/
    void reconnect();

public:

    /**
    * @brief Constructor for MaestroControl
    * @param dev device name (e.g. /dev/ttyACM0)
    */

    explicit MaestroControl(const char *dev);


    /**
 * @brief Returns the name of the serial port.
 * @return Serial port name (e.g. /dev/ttyACM0)
 */
    std::string getSerialPort();

    /**
* @brief Sets position of servo to given value
* @param channel channel number
* @param target servo position (4000-8000)
* @return -1 if an error occurred, 0 if successful
*/
    int setPosition(unsigned char channel, unsigned short target);

    /**
 * @brief Gets position of connected servo on channel given
 *
 * Will only return a number from 4000-8000 or -1 if an error occurred.
 * @param channel channel number
 * @return position of servo, or -1 if error
 */
    int getPosition(unsigned char channel);

    /**
 * @brief Destructor
 *
 * Disconnects from serial port
 */
    ~MaestroControl();
};

#endif //MAESTROLIBRARY_LIBMAESTROCONTROL_H
