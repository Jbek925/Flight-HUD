// heading_module.h
#ifndef HEADING_MODULE_H
#define HEADING_MODULE_H
#include <vector>
#include <mutex>

class HeadingModule {
private:
    double heading_rad;
    std::vector<double> direct;
    std::vector<int> range;
    int pc_increase;

public:
    HeadingModule() {};
    void rand_heading(bool& running, double& shared_value, std::mutex& heading_mutex);
    void set_direct();
    std::vector<double> get_direct();
    void convert_heading(double& shared_value);
    double get_heading_rad();
    void set_pc_increase();
    int get_pc_increase();
};

#endif // HEADING_MODULE_H
