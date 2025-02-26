//
//  main.cpp
//  Flight-HUD
//
//  Created by Jake Bekker on 26/02/2025.
//
#include "Speed_module.h"
#include "alt_module.h"
#include "heading_module.h"
#include "fuel_module.h"
#include "HUD.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>


HUD HUD;
std::mutex hud_mutex;

int main() {
    HUD.int_hud();
    return 0;
}
