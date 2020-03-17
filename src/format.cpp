#include <string>
#include<math.h>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    double hours, minutes, secs;
    hours = seconds/3600.0;
    minutes = modf(hours, &hours);
    minutes = minutes*60.0;
    secs = modf(minutes, &minutes);
    secs = secs*60.0;
    return string(""+std::to_string((int)hours)+ " : "+std::to_string((int)minutes)+" : "+std::to_string((int)secs)); 
}