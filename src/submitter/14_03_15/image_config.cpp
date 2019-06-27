/*******************************
 File name: submitter/image_config.cpp
 Author:   Tangxuehai
 Version:  0.1
 Description: image config 
*********************************/

#include <strstream>
#include <vector>
#include "submitter/image_config.h"
#include "include/classad_attr.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using log4cplus::Logger;
using std::string;
using std::strstream;
using std::vector;

static Logger logger = Logger::getInstance("submitter");

bool ImageConfigI::CreateImageConfig(){
    //image_config_ad is not null
    if(image_config_ad.empty()){
        LOG4CPLUS_ERROR(logger, "create image faile,image_config_ad is null");
	return false;
    }
    //get rpc to create image config
    /*
    try {
           Proxy<MasterClient> proxy = Rpc<MasterClient, MasterClient>::GetProxy("localhost:9999");
	   image_id = proxy().CreateImage(image_config_ad);
           if(image_id == -1) {
               //std::cout<< "rpc error"<<std::endl;
	       LOG4CPLUS_ERROR(logger, "create image faile, master error");
               return false;
           }
       }  catch (TException &tx) {
          //std::cout<< "rpc error"<<std::endl;
	  LOG4CPLUS_ERROR(logger, "create image faile,rpc error");
          return false;
       }
    LOG4CPLUS_INFO(logger, "create image finished");
    */
    //std::cout<<image_id<<std::endl;
    return true;
}

bool ImageConfigI::DeleteImageConfig(const int32_t image_id){
    //get rpc to delete image config
    /*
    try {
           Proxy<MasterClient> proxy = Rpc<MasterClient, MasterClient>::GetProxy("localhost:9999");
           if(!proxy().DeleteImage(image_id)) {
               //std::cout<< "rpc error"<<std::endl;
               LOG4CPLUS_ERROR(logger, "delete image faile,rpc error");
               return false;
           }
       }  catch (TException &tx) {
          //std::cout<< "rpc error"<<std::endl;
          LOG4CPLUS_ERROR(logger, "delete image faile,rpc error");
