#include "ncurses_display.h"
#include "system.h"
#include<iostream>
int main() {
  System system;
  // for (size_t i = 0; i < 5; i++)
  // {
  //   /* code */
  //   std::cout<<system.Cpu().Utilization()<<std::endl;
  //   std::cin.get();
  // }
  // for ( Process& p : system.Processes())
  // {
  //  std::cout << p.CpuUtilization() << std::endl;
  // }
  
  
  NCursesDisplay::Display(system, 15);
}