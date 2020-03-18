#include "ncurses_display.h"
#include "system.h"
#include<iostream>
int main() {
  System system;
  
  // for ( Process& p : system.Processes())
  // {
  //  std::cout << p.CpuUtilization() << std::endl;
  // }
  
  
  NCursesDisplay::Display(system, 15);
}