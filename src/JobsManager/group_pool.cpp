/********************************
 FileName: JobsManager/group_pool.cpp


 Version:  0.1
 Description: Pool of Groups
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"
#include "common/rapidxml/rapidxml_print.hpp"
#include "JobsManager/group_pool.h"

using std::vector;
using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;
using namespace rapidxml;

static Logger logger = Logger::getInstance("JobsManager");

// In the Rapidxml process, you cannot operate to store other pointers, although they do not appear to be connected.To avoid strange bugs,
struct sGroup {
    string name;
    int32_t quota;
    double maxlimit; 
};

// TODO just for test
void GroupPool::PrintAll() {
    ReadLocker locker(m_map_lock);
    printf("job_group_pool.cpp\n");
    printf("************ Groups ************\n");
    printf("privilege factor: %f\n", m_privilege_factor);
    for (map<string, GroupPtr>::iterator it = m_group_map.begin();
         it != m_group_map.end(); ++it) {
        (it->second)->Print();
    }
    printf("********************************\n");
}

bool GroupPool::InitGroups(const string& conf) {
    // init xml file
    xml_document<> doc;
    try {
        file<> fdoc  (conf.c_str());
        doc.parse<0>(fdoc.data());
    } catch (parse_error& ex) {
        LOG4CPLUS_ERROR(logger, "synex error in " << ex.what() << ".");
        return false;
    } catch (std::runtime_error& ex) {
        LOG4CPLUS_ERROR(logger, "task xml error:" << ex.what() << ".");
        return false;
    }
 
    // xml_root groups
    xml_node<> *root_node = doc.first_node("groups");
    if (!root_node) {
        LOG4CPLUS_ERROR(logger, "no groups specified.");
        return false;
    }

    xml_node<char> *factor_node = root_node->first_node("privilege_factor");
    if (!factor_node) {
        LOG4CPLUS_ERROR(logger, "Failed to parse group privilege_factor ");
        return false;
    }
    m_privilege_factor = atof(factor_node->value()); // illegal -> 0
    if (m_privilege_factor <= 1) {
