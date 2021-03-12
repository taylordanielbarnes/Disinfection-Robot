#include "ros/ros.h"
#include "ros/console.h"
#include "uvc/set_lamp.h"

#include <thread>
#include <chrono>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "uvc_client");
   
    ros::NodeHandle node_handle;

    ros::ServiceClient client = node_handle.serviceClient<uvc::set_lamp>("set_lamp");

    uvc::set_lamp srv;

    srv.request.active = false;

    client.call(srv);

    ROS_INFO("OFF");

    std::this_thread::sleep_for(std::chrono::seconds(10));

    srv.request.active = true;
    
    client.call(srv);
    
    ROS_INFO("ON");

    std::this_thread::sleep_for(std::chrono::seconds(10));

    srv.request.active = false;

    client.call(srv);

    ROS_INFO("OFF");

    return 0;
}
