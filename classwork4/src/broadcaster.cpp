#include <ros/ros.h>
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "classwork4/service.h"
#include <tf/transform_broadcaster.h>

using namespace std;

int main(int argc, char** argv) {

    ros::init(argc, argv, "broadcaster");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<classwork4::service>("service");

    classwork4::service srv;
    srv.request.frame_a.data = "base_link";   
	srv.request.frame_b.data = "link7";   
    tf::TransformBroadcaster br;
    tf::Transform transform;          

    ros::Rate rate(10);
    while (ros::ok()) {
 
        cout << srv.response.pose << endl;
        
        tf::Quaternion quaternion(srv.response.pose.orientation.x, srv.response.pose.orientation.y, srv.response.pose.orientation.z, srv.response.pose.orientation.w);
        transform.setOrigin(tf::Vector3(srv.response.pose.position.x, srv.response.pose.position.y, srv.response.pose.position.z));
        transform.setRotation(quaternion);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "camera_link"));
        rate.sleep();
    }
    return 0;
}
