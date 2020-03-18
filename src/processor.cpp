#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    return LinuxParser::ProcessorUtilization(prev_total, prev_idle);
}