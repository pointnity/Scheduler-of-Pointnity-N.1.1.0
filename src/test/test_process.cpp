#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string>
#include<iostream>

using std::string;
using std::cout;
using std::endl;

int main(){
    string process_name = "init";
    char buf[256];
    string cmd;
    int count;
    cmd = "ps -C " + process_name  + " |wc -l";
    if((fp=popen(cmd.c_str(), "r")) == NULL) {
