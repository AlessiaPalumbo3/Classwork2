#include <ros/ros.h>
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "classwork4/service.h"
#include <tf/transform_listener.h>

using namespace std;

bool service_cb(classwork4::service::Request &req, classwork4::service::Response &res) {
    bool success = true;

    tf::TransformListener listener;
    tf::StampedTransform stamped_transform;

    cout<<req.frame_a.data<<endl<<req.frame_b.data<<endl;

    try {
        listener.waitForTransform(req.frame_a.data, req.frame_b.data, ros::Time(0), ros::Duration(3.0));
        listener.lookupTransform(req.frame_a.data, req.frame_b.data, ros::Time(0), stamped_transform);

        success = true;    

        res.pose.position.x = stamped_transform.getOrigin().x();
        res.pose.position.y = stamped_transform.getOrigin().y();
        res.pose.position.z = stamped_transform.getOrigin().z();

        res.pose.orientation.x = stamped_transform.getRotation().x();
        res.pose.orientation.y = stamped_transform.getRotation().y();
        res.pose.orientation.z = stamped_transform.getRotation().z();
        res.pose.orientation.w = stamped_transform.getRotation().w();

        } 
        catch (tf::TransformException exception) {
        ROS_ERROR("%s", exception.what());
        success = false;
    }

    return success;
}


int main(int argc, char** argv){
    
    ros::init(argc, argv, "listener");
    ros::NodeHandle node;
    ros::ServiceServer service = node.advertiseService("service", service_cb);
    ros::spin();

    return 0;
}
