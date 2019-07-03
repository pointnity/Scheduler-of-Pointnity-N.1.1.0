/*******************************
 File name: submitter/user.cpp
 Version:  0.1
 Description: user 
*********************************/
#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <strstream>
#include <vector>
#include "submitter/user.h"
#include "include/classad_attr.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"

using log4cplus::Logger;
using std::string;
using std::strstream;
using std::vector;

static Logger logger = Logger::getInstance("submitter");

bool User::CreateUser(const string& user_config_ad){
    int32_t user_id;
    //app_config_ad is not null
    if(user_config_ad.empty()){
        LOG4CPLUS_ERROR(logger, "create user faile,user_config_ad is null");
	return false;
    }
    //get rpc to create app config
    try {
           Proxy<MasterClient> proxy = Rpc<MasterClient, MasterClient>::GetProxy("localhost:9999");
	   user_id = proxy().CreateUser(user_config_ad);
           if(user_id == -1) {
               //std::cout<< "rpc error"<<std::endl;
	       LOG4CPLUS_ERROR(logger, "create user faile, master error");
               return false;
           }
       }  catch (TException &tx) {
          //std::cout<< "rpc error"<<std::endl;
	  LOG4CPLUS_ERROR(logger, "create user faile,rpc error");
          return false;
       }
    LOG4CPLUS_INFO(logger, "create user finished");
    
    std::cout<<user_id<<std::endl;
    return true;
