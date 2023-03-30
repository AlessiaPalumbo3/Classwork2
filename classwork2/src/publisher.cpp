
#include "ros/ros.h" 
#include "classwork2/message.h"  
#include <cmath>

int main(int argc, char **argv) {

	ros::init(argc, argv, "sinu_publisher");
	ros::NodeHandle nh;
	ros::Publisher topic_pub = nh.advertise<classwork2::message>("/sinusoid", 1);


	//Rate object: 10 Hz of rate
	ros::Rate rate(10); 

	classwork2::message msg; 

    float amp = 13.0;
    float freq = 0.5;
    float t = 0.0;
    float T = 1.0/freq;

    msg.amplitude = amp;
        
    while ( ros::ok() ) {

        msg.value = amp * ( sin( 2*M_PI*t / T ));
		msg.period = 2*M_PI/T;
        t += 1.0/10.0;		
		topic_pub.publish(msg);
		ROS_INFO("Done");
		
		//Rate to maintain the 10 Hz
		rate.sleep();
	}
	
	return 0;
}


