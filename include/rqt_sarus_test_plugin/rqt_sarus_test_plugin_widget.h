#ifndef RQT_SARUS_TEST_PLUGIN_WIDGET
#define RQT_SARUS_TEST_PLUGIN_WIDGET

#include <QWidget>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PointStamped.h"

namespace Ui {
class TestPluginWidget;
}

class TestPluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestPluginWidget(QWidget *parent = nullptr);
    ~TestPluginWidget();

    void init_ROS_Node();

private slots:
    void on_pushButton_clicked();
    void Update_Display();
    void Update_Time();

    void on_addDrone_clicked();

    void on_removeDrone_clicked();

private:
    Ui::TestPluginWidget *ui;

    // Node Handle
    ros::NodeHandle ros_node_handle;

    //Publishers
    ros::Publisher buttonPublisher;

    //Subscribers
    ros::Subscriber speedx;
    ros::Subscriber speedy;
    ros::Subscriber speedz;
    ros::Subscriber pos_z;

    // Subscribers callbacks
    void ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx);
    void ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy);
    void ros_speedz_callback(const geometry_msgs::TwistStamped::ConstPtr &vz);
    void ros_posz_callback(const geometry_msgs::PointStamped::ConstPtr &z);

    // Variables
    QString droneSpeed_x;
    QString droneSpeed_y;
    QString droneSpeed_z;
    QString dronePos_z;
    int num_Drones = 0;

    QTimer *timer_1;
    QTimer *timer_1s;

    QString terminal_msg;
    QString terminal_time;
};

#endif // RQT_SARUS_TEST_PLUGIN_WIDGET
