#include "../../include/hud/heading_module.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <limits>

void HeadingModule::convert_heading(double& shared_value) {
    heading_rad = (shared_value * 3.141592653589793 / 180.0); 
}


void HeadingModule::set_direct() {
    
    std::string direct_i;
    std::vector<double> direct_dg;
    
    std::cout<<"Set Turn direction (range in degrees {a-b} \n";
    
    try{
        std::cin >> direct_i;
    } catch (const std::exception&e) {
        std::cerr << e.what() << "\n Invalid input format. Please use the format 'start-end'.\n";
        set_direct();
        return;
    }
    
    std::stringstream ss(direct_i);
    std::string token;
    while (std::getline(ss, token, '-')) {
        try {
            direct_dg.push_back(std::stod(token));
        } catch (const std::exception& e) {
            std::cerr << "Conversion error: " << e.what() << std::endl;
            direct_dg.clear();
            set_direct();
        }
    }
this->direct = direct_dg;
}

std::vector<double> HeadingModule::get_direct() {
    return direct;
}

void HeadingModule::set_pc_increase() {
    int pcin = 0;
    std::cout << "enter speed of turn (1-100) \n";
    std::cin >> pcin;
    if (std::cin.fail() || pcin < 1 || pcin > 100) {
        std::cerr << "must be an integer between 0 and 100.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        set_pc_increase();
        return;
    }
    pc_increase = pcin;
}

void HeadingModule::rand_heading(bool& running, double& shared_value, std::mutex& heading_mutex) {
    std::vector<double> range = get_direct();
    int pc_inc = get_pc_increase();
    double increment_value = ((pc_inc/100.0)*(range[1] - range[0]));
    double current_heading = range[0];
    
    while (running) {
            current_heading += increment_value + ((rand() % 100) / 100.0);
            if (current_heading >= range[1]) {
                current_heading = range[1];
                running = false;
            } else {
                if (std::cin.rdbuf()->in_avail() > 0) {
                    char c;
                    std::cin >> c;
                    if (c == 'f' || c == 'F') {
                        running = false;
                        break;
                    }
                }
                current_heading = (rand() % 8);            }
            {
                std::lock_guard<std::mutex> lock(heading_mutex);
                shared_value = current_heading;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
    
int HeadingModule::get_pc_increase() {
    return pc_increase;
}

    
double HeadingModule::get_heading_rad() {
        return heading_rad;
}
