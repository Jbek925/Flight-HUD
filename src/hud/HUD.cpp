#include "../../include/hud/Speed_module.h"
#include "../../include/hud/alt_module.h"
#include "../../include/hud/heading_module.h"
#include "fuel_module.h"
#include "HUD.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstdlib>

void clearScreen() {
    for (int i = 0; i < 50; i++) {  // Print 50 blank lines
        std::cout << "\n";
    }
    std::cout << std::flush;
}

void HUD::hud_grid() {
    int alt_pos;
    int head_pos;

    while (running) {
        {
            std::lock_guard<std::mutex> lock(hud_mutex);
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    hudarr[i][j] = '.';
                }
            }

            alt_pos = round((9*(shared_altitude/1000)));
            head_pos = round((9*(shared_heading/360)));
            hudarr[10 - alt_pos][head_pos] = 'x';
            clearScreen();
        }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
}

void HUD::display_hud() {
    while (running) {
        {
            std::lock_guard<std::mutex> lock(hud_mutex);
            system("clear");
            
            std::cout << "Flight Radar HUD" << std::endl;
            std::cout << "----------------" << std::endl;
            std::cout << "Speed: " << shared_speed << " knots" << std::endl;
            std::cout << "Altitude: " << shared_altitude << " feet" << std::endl;
            std::cout << "Heading: " << shared_heading << "° (" 
                      << (shared_heading * 3.14159 / 180.0) << " radians)" << std::endl;
            std::cout << "Fuel: " << shared_fuel << "%" << std::endl;

            std::cout << "---------------- \n";
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                std::cout << hudarr[i][j] << " ";
                }
            std::cout << "\n" << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int HUD::int_hud() {
    AltMod alt_mod;
    HeadingModule heading_mod;
    SpeedModule speed_mod;
    fuel_module fuel_mod;
    
    alt_mod.set_inc(hud_mutex);
    heading_mod.set_direct();
    speed_mod.set_accel();
    range = heading_mod.get_direct();
    heading_mod.set_pc_increase();

    while (running) {
        std::thread grid_thread(std::bind(&HUD::hud_grid, this));
        std::thread alt_thread(&AltMod::rand_alt, &alt_mod, std::ref(running), std::ref(hud_mutex), std::ref(shared_altitude));
        std::thread heading_thread(&HeadingModule::rand_heading, &heading_mod, std::ref(running), std::ref(shared_heading), std::ref(hud_mutex));
        std::thread speed_thread(&SpeedModule::Random_sensor_data, &speed_mod, std::ref(shared_speed), std::ref(running), std::ref(hud_mutex));
        std::thread fuel_thread(
            &fuel_module::track_fuel, &fuel_mod,
            std::ref(hud_mutex),     
            std::ref(running),        
            std::ref(shared_speed),  
            std::ref(shared_fuel),    
            std::ref(shared_altitude) 
        );

        std::thread display_thread(&HUD::display_hud, this);

        alt_thread.join();
        heading_thread.join();
        speed_thread.join();
        grid_thread.join();
        fuel_thread.join();
        display_thread.join();
        running = false;
    }

    std::cout << "Simulation stopped." << std::endl;
    return 0;
}

