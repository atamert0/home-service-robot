#!/bin/sh

xterm  -e "
roslaunch turtlebot_gazebo turtlebot_world.launch  world_file:=$(rospack find turtlebot_gazebo)/worlds/my_world.world" &
sleep 5

xterm  -e "
roslaunch turtlebot_gazebo amcl_demo.launch  map_file:=$(rospack find turtlebot_gazebo)/maps/map.yaml" & 
sleep 5

xterm  -e "
roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 10

xterm  -e " rosrun pick_objects pick_objects_node " &
