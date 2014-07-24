/*
*/

#ifndef FLAG_DATA_H
#define FLAG_DATA_H 

#include <fstream>	//for writing to output file
#include <string.h>
#include <stdarg.h>

#include <ros/ros.h>
#include <ros/package.h>
#include <ros/console.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_broadcaster.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>
#include <visualization_msgs/Marker.h>
#include <resource_retriever/retriever.h>

#include <boost/filesystem.hpp>


#include <sensor_msgs/Image.h>


const std::string cameraImageTopic_ = "/camera/image_raw";
const std::string cameraInfoTopic_  = "/camera/camera_info";

const double AR_TO_ROS = 0.001;

namespace flag_data 
{
  class Flagger
  {
  public:
    Flagger (ros::NodeHandle & n);
    ~Flagger (void);
    void init();
	void spin();

  private:

	//writing to file the output
	std::ofstream output;
	std::string input_str;

	
    char tick_output_filename_[80];

    ros::NodeHandle n_;
//    ros::Subscriber imu;


  };                            // end class Flagger 
}                               //end namespace flag_data 

#endif
