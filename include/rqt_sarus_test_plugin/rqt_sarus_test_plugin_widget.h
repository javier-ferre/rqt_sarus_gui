#ifndef RQT_SARUS_TEST_PLUGIN_WIDGET
#define RQT_SARUS_TEST_PLUGIN_WIDGET

#include <QWidget>
#include <ros/ros.h>
#include <std_msgs/String.h>

namespace Ui {
class TestPluginWidget;
}

class TestPluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestPluginWidget(QWidget *parent = nullptr);
    ~TestPluginWidget();
    void init_ROS_Node(ros::NodeHandle& nh);

private slots:
    void on_pushButton_clicked();

private:
    Ui::TestPluginWidget *ui;
    ros::Publisher buttonPublisher;
};

#endif // RQT_SARUS_TEST_PLUGIN_WIDGET
