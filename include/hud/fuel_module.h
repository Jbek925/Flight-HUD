// fuel_module.h
#ifndef FUEL_MODULE_H
#define FUEL_MODULE_H
#include <mutex>

class fuel_module {
    public:
    void track_fuel(std::mutex& fuel_mutex, bool& running, double& shared_speed, double& shared_fuel, double& shared_altitude);
};

#endif // FUEL_MODULE_H
