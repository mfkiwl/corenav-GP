#include <ros/ros.h>
#include <core_navigation/CoreNav.h>

int main(int argc, char** argv){
        ros::init(argc, argv, "inertial propagation");
        ros::NodeHandle n("~");

        CoreNav coreNav;
        if(!coreNav.Initialize(n)) {
                ROS_ERROR("%s: Failed to initialize the nav. filter.",
                          ros::this_node::getName().c_str());
                return EXIT_FAILURE;
        }
        while(ros::ok())
        {
            if(coreNav.propagate_flag)
            {
                // ROS_INFO("Propagate flag: Before Propagate\n");
                coreNav.Propagate(coreNav.imu,coreNav.odo,coreNav.cmd,coreNav.encoderLeft,coreNav.encoderRight,coreNav.joint);
                // ROS_INFO("Propagate flag: After Propagate\n");
                coreNav.propagate_flag =false;
            }

            if(coreNav.update_flag)
            {
                // ROS_INFO("Update Flag: before update\n");
                coreNav.Update(coreNav.odo,coreNav.joint);
                // ROS_INFO("Update Flag: after update\n");
                coreNav.update_flag =false;
            }
            ros::spinOnce();
        }
        //ros::spin();

        return EXIT_SUCCESS;
}
