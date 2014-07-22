/*
 *  Multi Marker Pose Estimation using ARToolkit
 *  Copyright (C) 2013, I Heart Engineering
 *  Copyright (C) 2010, CCNY Robotics Lab
 *  William Morris <bill@iheartengineering.com>
 *  Ivan Dryanovski <ivan.dryanovski@gmail.com>
 *  Gautier Dumonteil <gautier.dumonteil@gmail.com>
 *  http://www.iheartengineering.com
 *  http://robotics.ccny.cuny.edu
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

    ros::NodeHandle n_;
//    ros::Subscriber imu;


  };                            // end class Flagger 
}                               //end namespace flag_data 

#endif
