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
	
    ros::NodeHandle n_param ("~");
	
	std::string default_path_output = "tick_output.txt";
	std::string local_path;
	

	n_param.param ("tick_output_file", local_path, default_path_output);
	sprintf (tick_output_filename_, "%s", local_path.c_str ());
	ROS_INFO ("run tick output filename: %s", tick_output_filename_);


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
	//THIS IS BAD. THIS DOESN"T ACTUALLY EXECUTE D:
	//nevermind. it does.. just that the ros_info doesn't display because by the time 
	//this happens, we already call ros::shutdown()
	printf("Wrote to file : %s", tick_output_filename_);
	ROS_INFO ("HI IM CLOSING NOW !!!!!!", tick_output_filename_);
  }
  

  void Flagger::init ()
  {
    ROS_INFO("Flagger::Starting Init");

	//eventually need to WAIT for IMU to spin up
	//maybe even camera to spin up
	if ( !boost::filesystem::exists( tick_output_filename_ ) )	{
		boost::filesystem::path p(tick_output_filename_);
		boost::filesystem::path dir = p.parent_path();
		if(boost::filesystem::create_directories(dir))	{
			ROS_INFO("Folder %s created.", dir.c_str());
			ROS_INFO("File %s created.", p.stem().c_str());
		}
		else	{
			ROS_ERROR("File cannot be opened.");	
		}
	}
	else	{
		ROS_INFO("File already exists.");
	}

	output.open(tick_output_filename_);
	if(!output.good())	{
		ROS_ERROR("File %s cannot be opened.", tick_output_filename_);
	}
	else	{
		ROS_INFO("File %s opened.", tick_output_filename_);
	}
  }

  void Flagger::spin()	{
	//
	bool start= true;
	printf("Ready.");
	printf("Press enter on start and stop of each run.\n");
	printf("Type q and hit enter to quit.\n");
//	printf("Press enter to indica

	
	int runNum = 0;
	char buffer[50];
	ros::Time tick;

	do	{
		getline(std::cin, input_str);
		if(input_str.size() ==0)	{
				tick = ros::Time::now();
				if(start)	{
					sprintf(buffer,"[%d.%d] Start run %d.", tick.sec, tick.nsec, runNum);
				}
				else	{
					sprintf(buffer,"[%d.%d] Stop run %d.", tick.sec, tick.nsec, runNum);
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
	printf("Flagger::Finished.\n");
	ros::shutdown();
  }
   
} // end namespace ar_pose
