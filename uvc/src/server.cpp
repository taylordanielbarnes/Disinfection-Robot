#include "ros/ros.h"
#include "ros/console.h"
#include "uvc/set_lamp.h"

#include <wiringPi.h>

/*
 *  send data to GPIO to control lamps
 *
 *  Service type: set_lamp.srv
 *  Request: bool active
 *  Response: bool status
 *
 *  if request is true, turn on lamps
 *  if request is false, turn off lamps
 */
bool SetLamp(uvc::set_lamp::Request &req, uvc::set_lamp::Response &res)
{
    if (req.active) {
        //print status to console
        ROS_INFO("ON");

        //turn lamps on via GPIO
        digitalWrite(8, 1);

        //return status
        res.status = true;
    }
    else {
        //print status to console
        ROS_INFO("OFF");

        //turn lamps off via GPIO
        digitalWrite(8, 0);

        //return status
        res.status = false;
    }

    return true;
}



/*
 *  Establish Server
 */
int main(int argc, char **argv)
{
    wiringPiSetup();			// Setup the library
    
    pinMode(8, OUTPUT);		// Configure GPIO8 as an output

    //server initialization
    ros::init(argc, argv, "uvc_server");
    ros::NodeHandle node_handle;
    ros::ServiceServer service = node_handle.advertiseService("set_lamp", SetLamp); //change name to something unique?

    //loop
    while (ros::ok()) {
        ros::spin();
    }

    return 0;
}
