
#include "ros/ros.h"
#include <cmath>
#include "classwork2/message.h"
#include "std_msgs/Float32.h"
#include  "boost/thread.hpp"

using namespace std;

class LP_FILTER {
	public:
		LP_FILTER();
		void topic_show( classwork2::message::ConstPtr data);
		void lowpassfilter();

	private:
		float filtered_value;
		float sinus;
		float cutoff_freq;
		float sampling_freq;
		ros::NodeHandle N;
		ros::Subscriber topic_sub;
		ros::Publisher topic_pub;
		ros::Rate rate;
};


LP_FILTER::LP_FILTER(): rate(10) {

	filtered_value = 0;
	sinus = 0;
	cutoff_freq = 0.2;
	sampling_freq = 0.1;
	topic_sub = N.subscribe("/sinusoid", 1, &LP_FILTER::topic_show, this);
	topic_pub = N.advertise<std_msgs::Float32>("/filtered_sinu", 1);
	boost::thread(&LP_FILTER::lowpassfilter, this);
}


void LP_FILTER::topic_show( classwork2::message::ConstPtr data) {

	ROS_INFO("Listener: amplitude : %f, period: %f, value: %f", data->amplitude, data->period, data->value);
	sinus = data->value;
}

void LP_FILTER::lowpassfilter() {
	std_msgs::Float32 low_pass_filter;
	while (true) {
		float tau = 1.0/(2.0*M_PI*cutoff_freq);
		float alfa = tau/(tau+1.0/(2.0*M_PI*sampling_freq));
		filtered_value = alfa*sinus+ (1-alfa)*filtered_value;
		ROS_INFO("Filtered value: %f", filtered_value);
		low_pass_filter.data = filtered_value;
		topic_pub.publish(low_pass_filter);
		rate.sleep();
	}
	
}

int main( int argc, char** argv ) {

	ros::init(argc, argv, "ros_subscriber");
	LP_FILTER rs;
	ros::spin(); 

	return 0;
}
