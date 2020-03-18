#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
 // TODO: See src/process.cpp
  Process(int pid);
  void setUser();
  void setCommand();
  bool operator<(Process& a);
  bool operator>(Process& a);
  // TODO: Declare any necessary private members
 private:
 int pid;
 std::string command;
 std::string user;
 long int uptime{0};
 


};

#endif