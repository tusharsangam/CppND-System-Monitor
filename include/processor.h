#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
   
  float Utilization();  // TODO: See src/processor.cpp
   
  // TODO: Declare any necessary private members
  
 private:
    long int prev_idle {0};
    long int prev_total{0};
    
};
#endif