/*
 *  
 */

#include <flag_data/flag_data.h>
#include <ros/console.h>

int main (int argc, char **argv)
{
  ros::init (argc, argv, "flag_data");

  /*if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
		     ros::console::notifyLoggerLevelsChanged();
  }
  */
  ros::NodeHandle n;
  flag_data::Flagger flag(n);
  flag.init();
  flag.spin();
  //ros::spin ();
  return 0;
}

namespace flag_data 
{
  Flagger::Flagger (ros::NodeHandle & n):n_ (n)
  {


	//modifications to allow path list from outside the package

	//grab output txt file name
	
	
/*
	if (!n_param.getParam ("output_txt_ticks", outputToFile))	{
      outputToFile = false;
      ROS_INFO ("\tNot outputting pose to file");
	}
	else	{
	    if(outputToFile)	{
			ROS_INFO ("Outputting Pose");
			n_param.param ("pose_output_file", local_path, default_path_output);
			sprintf (pose_output_filename_, "%s", local_path.c_str ());
			ROS_INFO ("pose output Filename: %s", pose_output_filename_);
			output.open(pose_output_filename_);
		}
		else	{
      		ROS_INFO ("\tNot outputting pose to file");
		
		}
	}
*/
    // **** subscribe

	/*
    ROS_INFO ("Subscribing to info topic");
    sub_ = n_.subscribe (cameraInfoTopic_, 1, &Flagger::camInfoCallback, this);
    getCamInfo_ = false;
*/     
 
    // **** advertse 
/*
    arMarkerPub_ = n_.advertise < ar_pose::ARMarkers > ("ar_pose_marker", 0);
    if(publishVisualMarkers_)
    {
      rvizMarkerPub_ = n_.advertise < visualization_msgs::Marker > ("visualization_marker", 0);
    }
	*/
  }

  Flagger::~Flagger (void)
  {
	output.close();
  }
  

  void Flagger::init ()
  {
    ROS_INFO("Flagger::Starting Init");

	//eventually need to WAIT for IMU to spin up
	//maybe even camera to spin up
	output.open("example.txt");
	
  }

  void Flagger::spin()	{
	//
	bool start= true;
	printf("Ready.");
	printf("Press enter on start and stop of each run.\n");
	printf("Type q and hit enter to quit.\n");
	
	int runNum = 0;
	char buffer[50];
	ros::Time tick;

	do	{
		getline(std::cin, input_str);
		if(input_str.size() ==0)	{
				tick = ros::Time::now();
				if(start)	{
					sprintf(buffer,"[%d.%d]Start run #%d.", tick.sec, tick.nsec, runNum);
				}
				else	{
					sprintf(buffer,"[%d.%d]Stop run. #%d.", tick.sec, tick.nsec, runNum);
					runNum++;
				}
				start = !start;
				printf("%s", buffer);
				output << buffer << '\n';
}
		else	{
			if(input_str[0] == 'q')	{
				printf("Quitting.\n");
			}
			else	{
				printf("Ignoring input.\n");
			}
		}
	}
	while(input_str[0] != 'q');	
	printf("Flagger::Finished.");
  }
   
} // end namespace ar_pose
