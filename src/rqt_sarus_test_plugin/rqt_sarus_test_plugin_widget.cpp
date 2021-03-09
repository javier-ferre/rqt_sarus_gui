#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin_widget.h>
#include "ui_rqt_sarus_test_plugin_widget.h"
#include <ros/ros.h>
#include <std_msgs/String.h>

TestPluginWidget::TestPluginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPluginWidget)
{
    ui->setupUi(this);
}

TestPluginWidget::~TestPluginWidget()
{
    // Write exit code here

    delete ui;
}

void TestPluginWidget::init_ROS_Node(ros::NodeHandle& nh)
{
    // Write initialization code here (publishers, subscribers)
    buttonPublisher = nh.advertise<std_msgs::String>("button_topic",1);
}

void TestPluginWidget::on_pushButton_clicked()
{
    // Button clicked callback
    std_msgs::String message;
    message.data = "Button clicked!";
    buttonPublisher.publish(message);
}
