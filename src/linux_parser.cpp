#include <dirent.h>
#include <string>
#include <vector>
#include <signal.h>
#include <unordered_map>

#include "linux_parser.h"
#include "processor.h"
#include "system.h"
using std::stof;
using std::string;
using std::to_string;
using std::vector;



// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >>kernel;
  }
  return kernel;
}

bool LinuxParser::isRunning(int pid){
  return 0 == kill(pid, 0);
}
// BONUS: Update this to use std::filesystem
void LinuxParser::Pids(std::vector<Process>& processes) {
  processes.clear();
  DIR* directory = opendir(LinuxParser::kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        if(LinuxParser::isRunning(pid)){
            processes.emplace_back(pid);

        }
        
      }
    }
  }
  closedir(directory);
  
}



// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memtotal{0.0}, memfree{0.0};
  string line, ignore;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>ignore  >> memtotal >>ignore;
    std::getline(stream, line);
    std::istringstream linestream2(line);
    linestream2 >>ignore  >> memfree >>ignore;
  }
  
  return (memtotal - memfree)/memtotal; 

}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
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

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

int LinuxParser::procs::total_procs;
int LinuxParser::procs::active_procs;

float LinuxParser::ProcessorUtilization(long& prev_total, long& prev_idle){
  std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
    std::string line, ignore;
    long int user, nice, system, idle, iowait,irq, softirq, steal, guest, guest_nice, nonidletime, totald, idled, totaltime;
    float percent{0.0f};     
    if(stream.is_open()){
        std::getline(stream, line); 
        std::istringstream iss(line);
        //std::cout << line<<std::endl;

        iss >> ignore >>  user >>  nice >>  system >>  idle >>  iowait >> irq >>  softirq >>  steal >>  guest >>  guest_nice;
        
        while(std::getline(stream, line)){
          if((int)line.find("processes") > -1){
            std::istringstream iss(line);
            iss>> ignore >> LinuxParser::procs::total_procs;
            std::getline(stream, line);
            
            if((int)line.find("procs_running") > -1){
              std::istringstream iss(line);
              iss>> ignore >> LinuxParser::procs::active_procs;
              break;            
            }
          }
        }
         user -=  guest;
         nice -=  guest_nice;
         idle +=  iowait;
         system +=  irq+softirq;
         guest +=   guest_nice;

        //std:: cout << user << " " << nice << " " <<  idle << " " << system << " "<< guest << std::endl;
         nonidletime =  user +  nice +  system +  steal +   guest;
        
         totaltime =  nonidletime +  idle;

         totald =  totaltime - prev_total;
         idled =  idle - prev_idle;

       

        percent = ( totald -  idled) / float( totald);


         //std::cout << percent<< " " << totald-idled << " "<< totald<<std::endl;

        prev_total =  totaltime ;
        prev_idle =  idle;       
    }
    return percent;
}



// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  std::string line, ignore;
  int processes;
  if(stream.is_open()){
    while(std::getline(stream, line)){
      if((int)line.find("processes") > -1){
        std::istringstream iss(line);
        iss>> ignore >> processes;
        return processes;
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  std::string line, ignore;
  int processes;
  if(stream.is_open()){
    while(std::getline(stream, line)){
      if((int)line.find("procs_running") > -1){
        std::istringstream iss(line);
        iss>> ignore >> processes;
        return processes;
      }
    }
  }
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function

string LinuxParser::Command(int pid[[maybe_unused]]) { 
  
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kCmdlineFilename);
  std::string line("");
  if(stream.is_open()){
    std::getline(stream, line);
  }  
  return line;
  
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
void LinuxParser::Ram(int pid, long& memsize) { 
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatusFilename);
  std::string line ,ignore;
  if(stream.is_open()){
    while(std::getline(stream, line)){
      if((int)line.find("VmSize") > -1){
        std::istringstream iss(line);
        iss >> ignore >> memsize;
        memsize /= 1024;
        return;
      }
    }  
  }
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
//#include<iostream>
void LinuxParser::Uid(int pid, string& uid) { 
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatusFilename);
  std::string line,ignore, ignore2, ignore3;
  if(stream.is_open()){
    while(std::getline(stream, line)){
        if((int)line.find("Uid") > -1){
          std::istringstream iss(line);
          //std::cout << line << std::endl;
          iss >> ignore >> ignore2  >> uid;
          return;
        }
    }
  }

 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
void LinuxParser::User(std::string& uid, std::string& username) { 
  std::ifstream stream(LinuxParser::kPasswordPath);
  std::string line;
  if(stream.is_open()){
    while(std::getline(stream, line)){
        if((int)line.find(uid) > -1){
          std::istringstream iss(line);
          std::getline(iss, username, ':');
          //iss >> username;
          return;
        }
    }
  }
  return; 
  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long getfulltime(){
    std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
    std::string line, ignore;
    long int user, nice, system, idle, iowait,irq, softirq, steal, guest, guest_nice;
     
    if(stream.is_open()){
        std::getline(stream, line); 
        std::istringstream iss(line);
    
        iss >> ignore >>  user >>  nice >>  system >>  idle >>  iowait >> irq >>  softirq >>  steal >>  guest >>  guest_nice;
    }
    return user +  nice +  system +  idle ;

  }

//#include<iostream>
// TODO: Read and return CPU utilization
long Hertz = sysconf(_SC_CLK_TCK);
long LinuxParser::findProcessUptime(int pid){
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatFilename);
  std::string line, ignorestr;
  long uptime, ignore;
  
  
  if(stream.is_open()){
    std::getline(stream, line);
    //14,15,16,17, 22
    std::istringstream iss(line);
    iss >> ignore >> ignorestr >> ignorestr;
    size_t i = 4;
    while(i < 23){ 
      if(i == 22){
        iss >> uptime;
        return uptime/Hertz;
      }else{
         iss >> ignore;
      }
      i++;
    }
  }
}


void LinuxParser::CpuUtilization(int& pid, float& utilization, long& prev_proctime) { 
  std::ifstream stream(LinuxParser::kProcDirectory+std::to_string(pid)+LinuxParser::kStatFilename);
  std::string line, ignorestr;
  long utime, stime, cutime, cstime, starttime, ignore, uptime;
  
  
  if(stream.is_open()){
    std::getline(stream, line);
    //14,15,16,17, 22
    std::istringstream iss(line);
    iss >> ignore >> ignorestr >> ignorestr ;
   
    size_t i = 4;
    while(i < 23){ 
      if(i == 14){
        iss >> utime >> stime >> cutime >> cstime;
         i = 17;
      }else if(i == 22){
        iss >> starttime;
        break;
      }else{
         iss >> ignore;
      }
      i++;
    }
    
    

    //Processor::idle +  Processor::user + Processor::system + Processor::idle + Processor::iowait + Processor::irq + Processor::softirq + Processor::steal + Processor::guest + Processor::guest_nice;
    
    uptime = LinuxParser::UpTime();
    
    long total_time =  utime +stime +cutime + cstime;

    
    starttime = starttime/float(Hertz);
    

     

    utilization = (100.0* (total_time/Hertz)/ float(uptime  - starttime) );
    

    prev_proctime = starttime;
    //prev_cpu_usage = seconds;
    
    //std::cout << line << std::endl;
    //std::cout << utime << " "<< stime << " "<< cutime << " "<<  cstime << " "<< starttime << " "<<std::endl;
    
  }
 }