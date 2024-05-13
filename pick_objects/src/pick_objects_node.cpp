#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "simple_navigation_goals");

  MoveBaseClient ac("move_base", true);

  while (!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 2.70;
  goal.target_pose.pose.position.y = 1.75;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Robot reached pickup destination");

  else
    ROS_INFO("The base failed to reach pickup destination");
  ros::Duration(5).sleep();

  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.position.y = 1.0;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending second goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Robot reached drop off destination");

  else
    ROS_INFO("The base failed to reach drop off destination ");
  ros::Duration(5.0).sleep();

  return 0;
}
