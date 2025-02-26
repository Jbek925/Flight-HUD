#include<thread>
#include <cstdlib>

class HUD {
private:
    std::mutex hud_mutex;
    bool running = true;
    double shared_speed = 0.0;
    double shared_altitude = 0.0;
    double shared_heading = 0.0;
    double shared_fuel = 100.0;
    char hudarr[10][10];
    std::vector<double> range = {0,0};
public:
    void display_hud();
    int int_hud();
    void hud_grid();
};
