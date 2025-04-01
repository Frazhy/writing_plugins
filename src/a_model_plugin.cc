#include <functional>
#include <gazebo/common/common.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <ignition/math/Vector3.hh>

namespace gazebo {
class AModelPlugin : public ModelPlugin {
public:
  void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {
    // Store the pointer to the model
    this->model = _parent;
    
    this->iterations = 10 * 1000;
    if (_sdf->HasElement("iterations")) {
        this->iterations = _sdf->Get<int>("iterations");
    }

    this->linear_vel = 0.4;
    if (_sdf->HasElement("linear_vel")) {
        this->linear_vel = _sdf->Get<float>("linear_vel");
    }
    
    // Listen to the update event. This event is broadcast every
    // simulation iteration.
    this->updateConnection = event::Events::ConnectWorldUpdateBegin(
        std::bind(&AModelPlugin::OnUpdate, this));
  }

  // Called by the world update start event
public:
  void OnUpdate() {
    // Apply a small linear velocity to the model.

    if (this->counter < this->iterations) {
      this->model->SetLinearVel(ignition::math::Vector3d(this->linear_vel, 0, 0));
      //this->model->SetLinearAccel(ignition::math::Vector3d(0, 0, 0.4));
    }
    else if (this->counter < 2*this->iterations){
        this->model->SetLinearVel(ignition::math::Vector3d(0, this->linear_vel, 0));
        //this->model->SetLinearAccel(ignition::math::Vector3d(0, 0, 0.4));
    }
    else if (this->counter < 3*this->iterations){
        this->model->SetLinearVel(ignition::math::Vector3d(-this->linear_vel, 0, 0));
        //this->model->SetLinearAccel(ignition::math::Vector3d(0, 0, 0.4));
    }
    else if (this->counter < 4*this->iterations){
        this->model->SetLinearVel(ignition::math::Vector3d(0, -this->linear_vel, 0));
        //this->model->SetLinearAccel(ignition::math::Vector3d(0, 0, 0.4));
    }
    else {
        this->counter = 0;
    }
    this->counter++;
  }

  // Pointer to the model
private:
  physics::ModelPtr model;

private:
  int counter;
  int iterations;
  float linear_vel;
  // Pointer to the update event connection
private:
  event::ConnectionPtr updateConnection;
};

// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(AModelPlugin)
} // namespace gazebo