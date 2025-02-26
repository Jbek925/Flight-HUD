#include <mutex>
#ifndef ALT_MODULE_H
#define ALT_MODULE_H

class AltMod {
private:
    double altitude;
    double alt_feet;
    double incline_rate;
    char incline;
public: 
    AltMod() : altitude(0.0), alt_feet(0.0), incline('a') {}
    void set_inc(std::mutex& alt_mutex);
    char get_inc(std::mutex& alt_mutex);
    double get_incline_rate();
    double convert_to_feet(double altitude);
    void rand_alt(bool& running, std::mutex& alt_mutex, double& shared_alt);

};

#endif // ALT_MODULE_H
