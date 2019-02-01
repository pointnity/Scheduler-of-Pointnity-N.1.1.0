/********************************
 FileName: JobsManager/group_pool.h


 Version:  0.1
 Description: Pool of Groups
*********************************/

#ifndef JOBS_MANAGER_GROUP_POOL_H
#define JOBS_MANAGER_GROUP_POOL_H

#include <map>

#include "common/clynn/rwlock.h"
#include "common/clynn/singleton.h"
#include "JobsManager/group.h"

using std::map;
using clynn::RWLock;

class GroupPool {
public:
    // TODO print all for test
    void PrintAll();

    // quota
    bool InitGroups(const string& conf);

    void SetTotalQuotaShares();

    void UpdateGroupsQuotaPct();

    bool IsExistByName(const string& name);

    // @brief: insert a group in map
    bool InsertIfAbsent(const GroupPtr& ptr);

    // @brief: delete a group from map by name 
    void Delete(const string& name);

    GroupPtr GetGroupPtr(const string& name);

    // add job to wait queue
