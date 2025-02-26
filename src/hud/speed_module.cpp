#include "../../include/hud/Speed_module.h"
#include <iostream>
#include <sstream>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

void SpeedModule::set_speed(double speed) {
    this->speed = speed;
}

void SpeedModule::set_accel() {
    double accel;
    std::cout << "Set acceleration (m/s^2): \n";

    std::cin >> accel;

    if (std::cin.fail()) {  
        std::cerr << "Error: Invalid input. Please enter a valid number.\n";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
        set_accel();  
    } else {
        this->acceleration = accel;
    }
}

double SpeedModule::get_accel() const {
    return acceleration;
}

void SpeedModule::Random_sensor_data(double& shared_speed, bool& running,std::mutex& speed_mutex) {
    srand(time(0));
    double acc = get_accel();
    double speedinc = 0.0;
    while (running) {
        double random_speed = (40 + (rand()  % 11) + speedinc/2); 
        speedinc+=acc;
    {
        std::lock_guard<std::mutex> lock(speed_mutex);
        shared_speed = random_speed;
        set_speed(shared_speed);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

double SpeedModule::get_speed() const {
    return speed;
}

double SpeedModule::convert_to_knots() {
        double speed_knots = speed * 1.94384; 
        return speed_knots;
}



