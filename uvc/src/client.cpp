#include "ros/ros.h"
#include "ros/console.h"
#include "uvc/set_lamp.h"

#include <thread>
#include <chrono>

/*
 *  Client node to demonstrate set_lamp service
 *
 *  Establish client node
 *  Generate request to turn lamps off, then on, then off again
 */
int main(int argc, char **argv)
{
    //initialize client
    ros::init(argc, argv, "uvc_client");
    ros::NodeHandle node_handle;
    ros::ServiceClient client = node_handle.serviceClient<uvc::set_lamp>("set_lamp"); //change name to something unique?

    //declare service
    uvc::set_lamp srv;
    
    //generate request to turn lamps off
    srv.request.active = false; //set srv args
    client.call(srv);
    ROS_INFO("OFF"); //print status to console

    //wait 10 seconds
    std::this_thread::sleep_for(std::chrono::seconds(10));

    //now generate request to turn lamps on
    srv.request.active = true; //set srv args
    client.call(srv);
    ROS_INFO("ON"); //print status to console

    //wait 10 seconds
    std::this_thread::sleep_for(std::chrono::seconds(10));

    //turn lamps off again
    srv.request.active = false; //set srv args
    client.call(srv);
    ROS_INFO("OFF"); //print status to console

    return 0;
}
