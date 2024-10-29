#ifndef IMAGE2RTSP_IMAGE2RTSP_HPP
#define IMAGE2RTSP_IMAGE2RTSP_HPP

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <image_transport/image_transport.hpp>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include "sensor_msgs/msg/image.hpp"

using namespace std;

class Image2rtsp : public rclcpp::Node{
public:
    Image2rtsp();
    GstRTSPServer *rtsp_server;

private:
    string source;
    string topic;
    string mountpoint;
    string bitrate;
    string framerate;
    string caps_1;
    string caps_2;
    string port;
    string pipeline;
    string pipeline_head;
    string pipeline_tail;
    bool local_only;
    bool camera;
    GstAppSrc *appsrc;

    void video_mainloop_start();
    void rtsp_server_add_url(const char *url, const char *sPipeline, GstElement **appsrc);
    void topic_callback(const sensor_msgs::msg::Image::ConstSharedPtr & msg);
    GstRTSPServer *rtsp_server_create(const string &port, const bool local_only);
    GstCaps *gst_caps_new_from_image(const sensor_msgs::msg::Image::ConstSharedPtr & msg);
    image_transport::Subscriber image_subscription_;
};

static void media_configure(GstRTSPMediaFactory *factory, GstRTSPMedia *media, GstElement **appsrc);
static void *mainloop(void *arg);
static gboolean session_cleanup(Image2rtsp *node, rclcpp::Logger logger, gboolean ignored);

#endif // IMAGE2RTSP_IMAGE2RTSP_HPP
