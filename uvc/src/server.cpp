#include "ros/ros.h"
#include "ros/console.h"
#include "uvc/set_lamp.h"

#include <wiringPi.h>

bool SetLamp(uvc::set_lamp::Request &req, uvc::set_lamp::Response &res)
{
    if (req.active) {
        ROS_INFO("ON");

        digitalWrite(8, 1);

        res.status = true;
    }
    else {
        ROS_INFO("OFF");

        digitalWrite(8, 0);

        res.status = false;
    }

    return true;
}

int main(int argc, char **argv)
{
    wiringPiSetup();			// Setup the library
    
    pinMode(8, OUTPUT);		// Configure GPIO0 as an output

    ros::init(argc, argv, "uvc_server");

    ros::NodeHandle node_handle;

    ros::ServiceServer service = node_handle.advertiseService("set_lamp", SetLamp);

    while (ros::ok()) {
        ros::spin();
    }

    return 0;
}
