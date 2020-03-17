#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(){
    operating_system = LinuxParser::OperatingSystem();
    kernel_ =  LinuxParser::Kernel();
}


// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return System::operating_system; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kUptimeFilename);
    std::string line; 
    long int uptime{0};
    if(stream.is_open()){
      std::getline(stream, line);
      std::istringstream iss(line);
      iss >> uptime;
      //return uptime;
    }
    return uptime;
 }