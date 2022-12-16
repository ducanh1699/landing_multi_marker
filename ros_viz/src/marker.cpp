#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseStamped.h>

geometry_msgs::PoseStamped current_pose, set_point, target;
geometry_msgs::Point p, sp, t;
void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    current_pose = *msg;
}
void setpoint_cb(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    set_point = *msg;
}
void target_cb(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    target = *msg;
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "points_and_lines");
    ros::NodeHandle nh;

    ros::Subscriber local_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose", 100, pose_cb);
    ros::Subscriber set_point_sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 100, setpoint_cb);
    ros::Subscriber target_sub = nh.subscribe<geometry_msgs::PoseStamped>("/target_position", 100, target_cb);
    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 100);

    ros::Rate r(5);

    visualization_msgs::Marker points, line_strip, line_list, target_ls;
    points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = target_ls.header.frame_id = "map";
    points.header.stamp = line_strip.header.stamp = line_list.header.stamp = target_ls.header.stamp = ros::Time::now();
    points.ns = line_strip.ns = line_list.ns = target_ls.ns = "points_and_lines";
    points.action = line_strip.action = line_list.action = target_ls.action = visualization_msgs::Marker::ADD;

    points.id = 0;
    line_strip.id = 1;
    line_list.id = 2;
    target_ls.id = 3;

    points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_list.type = visualization_msgs::Marker::LINE_LIST;
    target_ls.type = visualization_msgs::Marker::LINE_LIST;

    points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = target_ls.pose.orientation.w = 1.0;

    points.scale.x = 0.05;
    points.scale.y = 0.05;
    points.scale.z = 0.05;

    line_strip.scale.x = 0.03;

    line_list.scale.x = 0.03;

    target_ls.scale.x = 0.03;

    // Points are green
    points.color.b = 1.0f;
    points.color.a = 1.0;
    // Line strip is red
    line_strip.color.r = 1.0;
    line_strip.color.a = 1.0;
    // line_list is blue
    line_list.color.g = 1.0;
    line_list.color.a = 1.0;

    target_ls.color.r = 1.0;
    target_ls.color.g = 1.0;
    target_ls.color.a = 1.0;

    points.lifetime = ros::Duration();
    line_strip.lifetime = ros::Duration();
    line_list.lifetime = ros::Duration();
    target_ls.lifetime = ros::Duration();
    while (ros::ok())
    {
        p = current_pose.pose.position;
        sp = set_point.pose.position;
        t = target.pose.position;
        // line_strip.points.push_back(p);
        points.points.push_back(p);
        line_strip.points.push_back(p);
        
        line_list.points.push_back(sp);
        sp.z += 0.01;
        line_list.points.push_back(sp);

        target_ls.points.push_back(t);
        t.z += 0.01;
        target_ls.points.push_back(t);

        // marker_pub.publish(points);
        marker_pub.publish(line_strip); 
        marker_pub.publish(line_list);   
        marker_pub.publish(target_ls);   
        
        ros::spinOnce();
        r.sleep();
    }
}