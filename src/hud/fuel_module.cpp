#include "fuel_module.h"
#include<iostream> 
#include<chrono>
#include<thread>

void fuel_module::track_fuel(std::mutex& fuel_mutex, bool& running, double& shared_speed, double& shared_fuel, double& shared_altitude) {
    while(running) {
    {   
        std::lock_guard<std::mutex> lock(fuel_mutex);
        shared_fuel -= (shared_speed + shared_altitude) / 1000;
        if (shared_fuel <= 0) {
            shared_fuel = 0;
            running = false;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
}

