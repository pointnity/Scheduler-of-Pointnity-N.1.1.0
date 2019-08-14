/********************************
 FileName: test/executor/system_test.cpp
 Version:  0.1
 Description: get the physical resource info of the machine, test
*********************************/
#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "executor/system.h"

using std::string;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    //tesing::InitGoogleTest(&argc, argv);
    // load
    printf("LoadAvginOne: %lf\n", System::GetLoadAvginOne());
    printf("LoadAvginFive: %lf\n", System::GetLoadAvginFive());
    printf("LoadAvginFifteen: %lf\n", System::GetLoadAvginFifteen());

    // cpu
    printf("CpuNum: %d\n", System::GetCpuNum());
    printf("CpuTime: %ld\n", System::GetCpuTime());
    printf("CpuUsage: %lf\n", System::GetCpuUsage());
    sleep(1);
