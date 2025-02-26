#include "../../include/hud/alt_module.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <mutex>
#include <thread>

void AltMod::set_inc(std::mutex& alt_mutex) {
    char inc;
    double inc_rate = 0;
    while (true) {
    std::cout << "set incline (a = ascending /d = descending /n = neurtral): ";
    std::cin >> inc;
    if (inc == 'a' || inc=='d') {
    std::cout << "enter rate of inc/decline (m/s): ";
    std::cin >> inc_rate;
    }

        if (std::cin.fail() || (inc != 'd' && inc != 'a' && inc != 'n')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid Input. Try again.";
        continue;
    }  else {
    this->incline_rate = inc_rate;
    this->incline = inc;
    break;

        }
    }
}

void AltMod::rand_alt(bool& running, std::mutex& alt_mutex, double& shared_alt) {
    int alt_var = 0;
    while(running) {
        double random_alt = 500 + alt_var + rand() % 51;
        {
        std::lock_guard<std::mutex> lock(alt_mutex);
        shared_alt = random_alt;
        if (incline == 'a') {
            alt_var += 0.5*incline_rate;
        } else if (incline == 'd'){
            alt_var -= 0.5*incline_rate;
        } else {
            alt_var = 0;
        }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

char AltMod::get_inc(std::mutex& alt_mutex) {
    {
    std::lock_guard<std::mutex> lock(alt_mutex);
    return incline;
    }
}

double AltMod::get_incline_rate(){
    return incline_rate;
}

double AltMod::convert_to_feet(double altitude) {
    alt_feet = altitude * 3.28084;
    return alt_feet;

}


