#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

//#include <iostream>
//constructor
Process::Process(int pid):pid(pid){
    setUser();
    setCommand();
}

void Process::setCommand(){
    command = LinuxParser::Command(pid);
}
void Process::setUser(){
   
    user = "Tushar";
    LinuxParser::Uid(pid, user);
    
    LinuxParser::User(user, user);
    //std::cout << "User "<< user << "\n";
}
// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() { return command; }

// TODO: Return this process's memory utilization
string Process::Ram() { long memsize{0}; LinuxParser::Ram(pid, memsize);  return std::to_string(memsize); }

// TODO: Return the user (name) that generated this process
string Process::User() { return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }