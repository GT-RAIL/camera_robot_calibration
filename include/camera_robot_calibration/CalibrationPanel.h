/*!
 * \file CalibrationPanel.cpp
 * \brief RViz plugin for interactive calibration.
 *
 * \author David Kent, GT - dekent@gatech.edu
 * \date August 9, 2018
 */

#ifndef CAMERA_ROBOT_CALIBRATION_CALIBRATION_PANEL_H_
#define CAMERA_ROBOT_CALIBRATION_CALIBRATION_PANEL_H_

// ROS
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>
#include <rviz/panel.h>
#include <std_srvs/Empty.h>

// Qt
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

namespace camera_robot_calibration
{

/*!
 * \class CalibrationPanel
 * \brief RViz plugin for calibration.
 */
class CalibrationPanel : public rviz::Panel
{

// this class uses Qt slots and is a subclass of QObject, so it needs the Q_OBJECT macro
Q_OBJECT

public:
  /*!
   * \brief Create a new CalibrationPanel.
   *
   * Creates a new CalibrationPanel and adds the correct widgets and service connections.
   *
   * \param parent The parent widget for this panel (defaults to NULL).
   */
  CalibrationPanel(QWidget *parent = NULL);

private:
  /*! The public ROS node handle. */
  ros::NodeHandle node_;

  ros::ServiceClient read_tfs_client_;
  ros::ServiceClient reset_frames_client_;
  ros::ServiceClient compute_frames_client_;

  QLabel *model_generation_status_;
  QPushButton *save_measurement_button_, *reset_button_, *compute_tf_button_;

// used as UI callbacks
private
  Q_SLOTS:

  /*!
   * \brief Save the current frame measurements.
   */
  void saveMeasurement();

  /*!
   * \brief Delete all frame measurements.
   *
   * Deletes all saved measurements. A confirmation dialog is given.
   */
  void reset();

  /*!
   * \brief Compute transforms from all saved measurements.
   */
  void computeTransform();
};

}

#endif  // CAMERA_ROBOT_CALIBRATION_CALIBRATION_PANEL_H_
