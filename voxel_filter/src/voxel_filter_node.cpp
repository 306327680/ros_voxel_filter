#include<ros/ros.h> //ros标准库头文件  
#include<iostream> //C++标准输入输出库  
#include <stdio.h>  
/*  
  以下是pointcloud2转化的必要的头文件  
*/  
#include <sensor_msgs/PointCloud2.h>  
#include <pcl/point_types.h>  
#include <pcl/filters/voxel_grid.h>  
#include <pcl_conversions/pcl_conversions.h>  
#include <pcl/point_cloud.h>  
  
static const std::string pointstopic = "/rtabmap/cloud_map";//设置订阅topic名称  
  
ros::Publisher points_pub;//定义ROS消息发布器  
/*以下为滤波函数，首先需要将sensor_msg::PointCloud2格式转化成pcl::PCLPointCloud2格式，然后再使用VoxelGrid滤波 */  
void pointsdo(const sensor_msgs::PointCloud2ConstPtr& msg)      
  {  
  
    pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;  
    pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);  
    pcl::PCLPointCloud2 msg_filtered;  
    pcl_conversions::toPCL(*msg, *cloud);  
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;  
    sor.setInputCloud(cloudPtr);                   //设置需要过滤的点云给滤波对象  
    sor.setLeafSize(0.5,0.5,0.1);               //设置滤波时创建的体素大小为2cm立方体，通过设置该值可以直接改变滤波结果，值越大结果越稀疏
    sor.filter(msg_filtered);                      //执行滤波处理，存储输出msg_filtered  
    sensor_msgs::PointCloud2 point_output;  
    pcl_conversions::fromPCL(msg_filtered, point_output);  
    points_pub.publish(point_output);  
  }  
  
int main(int argc, char** argv)  
   {  
     ros::init(argc, argv, "realcam_node");  
     ros::NodeHandle nh;  
     ros::Subscriber sub = nh.subscribe (pointstopic, 1, pointsdo);  
     points_pub=nh.advertise<sensor_msgs::PointCloud2>("/camera/depth/points_filter", 1);  
     ros::spin();  
     return 0;  
   }  
