/********************************
 FileName: ResourceScheduler/match_maker


 Version:  0.1
 Description: match machine with job
*********************************/

#ifndef SRC_RESOURCE_SCHEDULER_MATCH_MAKER_H
#define SRC_RESOURCE_SCHEDULER_MATCH_MAKER_H

#include <vector>
#include <string>
#include "common/clynn/singleton.h"

using std::vector;
using std::string;

class MatchMaker {
public:
    int Negotiation(const string& job, vector<string>& machines);
