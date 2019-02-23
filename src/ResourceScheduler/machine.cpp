/********************************
 FileName: ResourceScheduler/machine.cpp
 
 
 Version:  0.1
 Description: machine 
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>


#include "include/classad_attr.h"
#include "ResourceScheduler/machine.h"


using log4cplus::Logger;
using std::stringstream;
using std::vector;

using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("ResourceScheduler");

Machine::Machine(const ClassAdPtr& machine_ad) {
    m_machine_ad = machine_ad;
    m_id = -1;
}

string Machine::GetMachineEndpoint(){
    return m_endpoint;
}

void Machine::Update(const ClassAdPtr& machine_ad){
    m_machine_ad = machine_ad;   
}

bool Machine::ParseMachineAd() {
    if(m_machine_ad->EvaluateAttrString(ATTR_Machine_IP, m_ip) == false){
        return false;
    } else if (m_machine_ad->EvaluateAttrInt(ATTR_Port, m_port) == false) {
        return false;
    }
    stringstream ss;
    ss << m_ip << ":" << m_port;
    m_endpoint = ss.str();
    return true;
}

bool Machine::GetMachineByImageInfo(const string& user, const string& name, const int32_t size) {
    string image_info_str;
    stringstream size_ss;
    size_ss << size;
    string image_attr = user + "&" + name + "&" + size_ss.str();

    if(m_machine_ad->EvaluateAttrString(ATTR_Image,image_info_str) == false){
        return false;
    }
    if(image_info_str.empty()) {
	return false;
    }
    //for one image_attr
    if(image_info_str.find(":") == string::npos && image_info_str.find("&") != string::npos) {
        if(image_attr == image_info_str) {
            return true;
        } else {
		return false;	
	}

    } else if(image_info_str.find(":") != string::npos && image_info_str.find("&") != string::npos) {
	    vector<string> image_info_list;
	    boost::split(image_info_list, image_info_str, boost::is_any_of( ":" ), boost::token_compress_on);
    	    if(image_info_list.size() == 0) {
