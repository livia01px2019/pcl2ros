#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl/filters/voxel_grid.h>

ros::Publisher pub;

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;

  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);

  // Container for data
  pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 

  pcl::PCDReader reader;
  reader.read("/home/livia/catkin_ws/src/my_pcl_tutorial/src/table_scene_lms400.pcd", *cloud);
  printf("pointcloud width: %d", cloud->width);

  // Convert to ROS data type
  sensor_msgs::PointCloud2 output;
  pcl_conversions::moveFromPCL(*cloud, output);
  output.header.frame_id = "world";

  // Publish the data
  ros::Rate loop_rate(1);

  while (ros::ok())
  {
    // Publish the data
    pub.publish (output);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
