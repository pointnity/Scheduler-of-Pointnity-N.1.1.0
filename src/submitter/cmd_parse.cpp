/*******************************
 File name: submitter/cmd_parse.cpp
 Version:  0.1
 Description: cmd parse
*********************************/

#include "submitter/cmd_parse.h"
#include "submitter/image.h"
#include "submitter/app.h"
#include "submitter/job.h"

#include <iostream>
#include <gflags/gflags.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using log4cplus::Logger;
using std::cout;
using std::endl;

static Logger logger = Logger::getInstance("submitter");

DECLARE_string(operation);// create or delete...
DECLARE_string(xml_path); //classad string 

DECLARE_int32(job_id);

void CmdParse::UserCmdParse(){
/*    if(FLAGS_operation == "create"){
	UserPtrI::Instance()->CreateUser(FLAGS_xml_path);
    }else if(FLAGS_operation == "delete"){
	UserPtrI::Instance()->DeleteUser(FLAGS_user_id);
    }else if(FLAGS_operation == "update"){
//	UserPtrI::Instance()->UpdateUser(FLAGS_str_ad);
    }else if(FLAGS_operation == "query"){
	UserPtrI::Instance()->QueryUser(FLAGS_user_id);
    }else if(FLAGS_operation == "query_list"){
	UserPtrI::Instance()->QueryUserList();
    }else{
	LOG4CPLUS_ERROR(logger, "user cmd parse error, unknown run type");
	cout<< "User run type usage:"<<endl;
	cout<< "create: create user on system"<<endl;
	cout<< "delete: delete user from system"<<endl;
	cout<< "update: update user on system"<<endl;
	cout<< "query: query user on system"<<endl;
	cout<< "query_list: query user list on system"<<endl;
    }
