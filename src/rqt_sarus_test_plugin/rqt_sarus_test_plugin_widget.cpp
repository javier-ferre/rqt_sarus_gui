#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin_widget.h>
#include "ui_rqt_sarus_test_plugin_widget.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <QTimer>
#include <QTime>
#include <QString>
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PointStamped.h"

// Leds style
QString LedOn("QRadioButton::indicator {width: 15px; height: 15px; border-radius: 7px;} QRadioButton::indicator:unchecked { background-color: lime; border: 2px solid gray;} QRadioButton::indicator:checked { background-color: lime; border: 2px solid gray;}");
QString LedOff("QRadioButton::indicator {width: 15px; height: 15px; border-radius: 7px;} QRadioButton::indicator:unchecked { background-color: black; border: 2px solid gray;} QRadioButton::indicator:checked { background-color: black; border: 2px solid gray;}");

TestPluginWidget::TestPluginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPluginWidget)
{
    ui->setupUi(this);

    timer_1 = new QTimer(this);
    QObject::connect(timer_1, SIGNAL(timeout()), this, SLOT(Update_Display()));
    timer_1->start(500);

    timer_1s = new QTimer(this);
    QObject::connect(timer_1s, SIGNAL(timeout()), this, SLOT(Update_Time()));
    timer_1s->start(1000);

    ui->led->setStyleSheet(LedOn);
    ui->led_2->setStyleSheet(LedOff);
    ui->led_3->setStyleSheet(LedOn);

}

TestPluginWidget::~TestPluginWidget()
{
    // Write exit code here

    delete ui;
}


void TestPluginWidget::Update_Display() {

    std::string speed;

    int currentDron;
    currentDron = ui->drone_ID->currentIndex();

    ui->speedX->setText(droneSpeed_x);
    ui->speedY->setText(droneSpeed_y);
    ui->speedZ->setText(droneSpeed_z);
    ui->altitude->setText(dronePos_z);
}

void TestPluginWidget::Update_Time() {
    ui->current_time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void TestPluginWidget::ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx){
    this->droneSpeed_x = QString::number(vx->twist.linear.x);
}

void TestPluginWidget::ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy){
    this->droneSpeed_y = QString::number(vy->twist.linear.y);
}

void TestPluginWidget::ros_speedz_callback(const geometry_msgs::TwistStamped::ConstPtr &vz){
    this->droneSpeed_z = QString::number(vz->twist.linear.z);
}

void TestPluginWidget::ros_posz_callback(const geometry_msgs::PointStamped::ConstPtr &pz){
    this->dronePos_z = QString::number((pz->point.z)*(-1));
}

void TestPluginWidget::init_ROS_Node()
{
    // Write initialization code here

    // PUBLISHERS
    buttonPublisher = ros_node_handle.advertise<std_msgs::String>("my_data",1);

    // SUBSCRIBERS
    speedx = ros_node_handle.subscribe("/drone107/motion_reference/speed", 1, &TestPluginWidget::ros_speedx_callback, this);
    speedy = ros_node_handle.subscribe("/drone107/motion_reference/speed", 1, &TestPluginWidget::ros_speedy_callback, this);
    speedz = ros_node_handle.subscribe("/drone107/motion_reference/speed", 1, &TestPluginWidget::ros_speedz_callback, this);
    pos_z = ros_node_handle.subscribe("/drone107/sensor_measurement/altitude", 1, &TestPluginWidget::ros_posz_callback, this);
}

void TestPluginWidget::on_pushButton_clicked()
{
    // Button clicked callback
    std_msgs::String message;
    message.data = "Button clicked!";
    buttonPublisher.publish(message);
}

void TestPluginWidget::on_addDrone_clicked()
{
    num_Drones++;
    ui->drone_ID->addItem(QString::number(num_Drones));
    ui->n_drones->setText(QString::number(num_Drones));
}

void TestPluginWidget::on_removeDrone_clicked()
{
    if (num_Drones > 0){
        num_Drones--;
        ui->drone_ID->removeItem(num_Drones);
    }
    ui->n_drones->setText(QString::number(num_Drones));
}
