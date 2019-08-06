/********************************
 FileName: test/scheduler/submit-job.cpp
 Version:  0.1
 Description: submit a job to scheduler (with xml file)
*********************************/

#include <iostream>
#include <string>
#include <fstream>  
#include <streambuf>  
      
    std::ifstream t("file.txt");  
    std::string str((std::istreambuf_iterator<char>(t)),  
