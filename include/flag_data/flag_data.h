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
#include <signal.h>	//custom action on sigint.. need to make sure certain things are done before exiting

#include <sensor_msgs/Image.h>



const std::string cameraImageTopic_ = "/camera/image_raw";
const std::string cameraInfoTopic_  = "/camera/camera_info";

const int BUFFER_SIZE = 100;

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

	
    char tick_output_filename_[BUFFER_SIZE];

    ros::NodeHandle n_;
//    ros::Subscriber imu;


  };                            // end class Flagger 
}                               //end namespace flag_data 

#endif
