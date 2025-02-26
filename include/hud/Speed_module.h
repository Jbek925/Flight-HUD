#include <sstream>
#include <vector>
#include <string>

#ifndef SPEED_MODULE_H
#define SPEED_MODULE_H

class SpeedModule {
private:
    double speed;
    double speed_knots;
    double acceleration;

public:
    SpeedModule() : speed(0.0) {}
    void Random_sensor_data(double& shared_speed, bool& running, std::mutex& speed_mutex);
    void set_speed(double speed);
    double get_speed() const;
    void set_accel();
    double get_accel() const;
    double convert_to_knots();

};

#endif // SPEED_MODULE_H

