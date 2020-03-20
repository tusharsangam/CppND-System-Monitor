#include <string>
#include<math.h>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long given_seconds) {
    size_t hours = 0,  minutes = 0, seconds = 0;
    hours = floor(given_seconds / 3600);
    minutes = floor((given_seconds - (hours * 3600)) / 60);
    seconds = given_seconds - (hours * 3600) - (minutes * 60);
    return string(""+std::to_string(hours)+ " : "+std::to_string(minutes)+" : "+std::to_string(seconds)); 
}