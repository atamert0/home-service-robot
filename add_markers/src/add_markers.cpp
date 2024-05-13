#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseActionResult.h>

visualization_msgs::Marker marker;
ros::Publisher marker_pub;

void marker_mover(const move_base_msgs::MoveBaseActionResult msg){
    if(msg.status.status == 3){
        if(msg.header.seq == 0){
            ROS_INFO("Object picking up");
            ros::Duration(5).sleep();
            marker.color.a = 0.0;
            ROS_INFO("Object picked up");
            
        }
        else if(msg.header.seq == 1){
            ROS_INFO("Object dropping off");
            ros::Duration(5).sleep();
            marker.pose.position.x = 1.0;
            marker.pose.position.y = 1.0;
            marker.color.a = 1.0;
            ROS_INFO("Object dropped off");
        }
        else{
            ROS_INFO("More than 2 navigation goals have been executed. No longer moving marker.");
        }
    }
    marker_pub.publish(marker);
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  uint32_t shape = visualization_msgs::Marker::SPHERE;

    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "add_markers";
    marker.id = 0;
    marker.type = shape;
    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = 2.70;
    marker.pose.position.y = 1.75;
    marker.pose.position.z = 0;

    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

ros::Subscriber sub1 = n.subscribe("/move_base/result", 1, marker_mover);

    ros::spin();

    r.sleep();
  }
