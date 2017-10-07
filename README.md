# ros_voxel_filter
for pointcloud2 filter
put it into your catkin_ws folder and:


catkin_make



source ./devel/setup.bash 



rosrun voxel_filter voxel_filtenode 





these are the topics:


topic publish:/camera/depth/points_filter


topic subscribe:/rtabmap/cloud_map
