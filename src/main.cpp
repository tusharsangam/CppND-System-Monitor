#include "ncurses_display.h"
#include "system.h"
//#include<iostream>
int main() {
  System system;
  
  //  for ( Process& p : system.Processes())
  // {
  //   std::cout<< p.Pid()<< " " << p.CpuUtilization() << std::endl;
  //  }
  //std::cout<< system.Processes().size() << std::endl;

  
  
  NCursesDisplay::Display(system, 20);
}