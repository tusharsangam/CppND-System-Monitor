#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    std::ifstream stream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
    std::string line, ignore;
    float percent{0.0f};
    long int user, nice, system, idle, iowait,irq, softirq, steal, guest, guest_nice, totaltime, nonidletime, totald, idled;
     
    if(stream.is_open()){
        std::getline(stream, line); 
        std::istringstream iss(line);
        //std::cout << line<<std::endl;
        iss >> ignore >> user >>nice >>system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
        
        user -= guest;
        nice -= guest_nice;
        idle += iowait;
        system += irq+softirq;
        guest +=  guest_nice;

        //std:: cout << user << " " << nice << " " <<  idle << " " << system << " "<< guest << std::endl;
        nonidletime = user + nice + system + steal +  guest;
        
        totaltime = nonidletime+idle;

        totald = totaltime - prev_total;
        idled = idle - prev_idle;

       

        percent = (totald - idled) / float(totald);


         //std::cout << percent<< " " << totald-idled << " "<< totald<<std::endl;

        prev_total = totaltime ;
        prev_idle = idle;       
    }
    return percent; 
}