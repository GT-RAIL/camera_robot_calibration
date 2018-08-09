/*!
 * \file CalibrationPanel.cpp
 * \brief RViz plugin for interactive calibration.
 *
 * \author David Kent, GT - dekent@gatech.edu
 * \date August 9, 2018
 */

// RAIL Pick and Place Tools
#include "camera_robot_calibration/CalibrationPanel.h"

using namespace std;
using namespace camera_robot_calibration;

CalibrationPanel::CalibrationPanel(QWidget *parent)
    : rviz::Panel(parent)
{
  read_tfs_client_ = node_.serviceClient<std_srvs::Empty>("read_tfs");
  reset_frames_client_ = node_.serviceClient<std_srvs::Empty>("reset_frames");
  compute_frames_client_ = node_.serviceClient<std_srvs::Empty>("compute_frames");

  string ee_name, camera_name, marker_name, base_name;
  node_.param<string>("/capture_points/robot_ee_frame_name", ee_name, "lwr_arm_link_7");
  node_.param<string>("/capture_points/camera_frame_name", camera_name, "camera_link");
  node_.param<string>("/capture_points/marker_frame_name", marker_name, "marker_frame");
  node_.param<string>("/capture_points/base_frame_name", base_name, "base_link");

  QHBoxLayout *save_layout = new QHBoxLayout();
  string save_text = "save the current measurements of " + ee_name + " and\n" + marker_name + " with respect to " + camera_name + ".";
  QLabel *save_label = new QLabel(save_text.c_str());  //TODO: read parameters for frames
  save_label->setAlignment(Qt::AlignLeft);
  save_measurement_button_ = new QPushButton("Save Measurement");
  save_measurement_button_->setEnabled(true);
  save_layout->addWidget(save_measurement_button_);
  save_layout->addWidget(save_label);
  save_layout->setAlignment(Qt::AlignLeft);

  // list of current objects
  QHBoxLayout *reset_layout = new QHBoxLayout();
  QLabel *reset_label = new QLabel("delete all collected measurements.");
  reset_label->setAlignment(Qt::AlignLeft);
  reset_button_ = new QPushButton("Clear Measurements");
  reset_button_->setEnabled(true);
  reset_layout->addWidget(reset_button_);
  reset_layout->addWidget(reset_label);
  reset_layout->setAlignment(Qt::AlignLeft);

  // list of current objects
  QHBoxLayout *compute_layout = new QHBoxLayout();
  string compute_text = "compute transformation from" + base_name + " to\n" + camera_name + "from all measurements.";
  QLabel *compute_label = new QLabel(compute_text.c_str());  //TODO: read parameters for frames
  compute_label->setAlignment(Qt::AlignLeft);
  compute_tf_button_ = new QPushButton("Compute");
  compute_tf_button_->setEnabled(true);
  compute_layout->addWidget(compute_tf_button_);
  compute_layout->addWidget(compute_label);
  compute_layout->setAlignment(Qt::AlignLeft);

  // build the final layout
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addLayout(save_layout);
  layout->addLayout(reset_layout);
  layout->addLayout(compute_layout);

  // connect event callbacks
  QObject::connect(save_measurement_button_, SIGNAL(clicked()), this, SLOT(saveMeasurement()));
  QObject::connect(reset_button_, SIGNAL(clicked()), this, SLOT(reset()));
  QObject::connect(compute_tf_button_, SIGNAL(clicked()), this, SLOT(computeTransform()));

  // set the final layout
  this->setLayout(layout);
}


void CalibrationPanel::saveMeasurement()
{
  std_srvs::Empty empty;
  if (!read_tfs_client_.call(empty))
  {
    ROS_INFO("Couldn't call read tfs client!");
  }
}

void CalibrationPanel::reset()
{
  // confirmation dialog
  string delete_text = "Are you sure you want to delete all saved measurements?";
  QMessageBox::StandardButton confirm = QMessageBox::question(this, "Clear measurements?", delete_text.c_str(),
      QMessageBox::Yes | QMessageBox::No);
  if (confirm == QMessageBox::Yes)
  {
    std_srvs::Empty empty;
    if (!reset_frames_client_.call(empty))
    {
      ROS_INFO("Couldn't call reset frames client!");
    }
  }
}

void CalibrationPanel::computeTransform()
{
  std_srvs::Empty empty;
  if (!compute_frames_client_.call(empty))
  {
    ROS_INFO("Couldn't call compute frames client!");
  }
}

// tell pluginlib about this class (must outside of any namespace scope)
PLUGINLIB_EXPORT_CLASS(camera_robot_calibration::CalibrationPanel, rviz::Panel)
