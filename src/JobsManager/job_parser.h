/********************************
 FileName: JobsManager/job_parser.h


 Version:  0.1
 Description: parse job from xml file, init job and tasks
*********************************/

#ifndef JOBS_MANAGER_JOB_PARSER_H
#define JOBS_MANAGER_JOB_PAESER_H

#include <string>
#include <list>
#include <algorithm>
#include "common/classad/classad_complement.h"
#include "JobsManager/job_enum.h"
#include "JobsManager/job.h"
#include "JobsManager/constraint_edge.h"

using std::list;
using std::string;
using std::vector;

class JobParser {
public:
    JobParser();
    ~JobParser();
    int32_t SubmitNewJob(const string& job_xml, int32_t job_id);
    // TODO test
    void PrintAllTasks();
    // int SubmitNewJobByAdString(const string& job_ad, int& job_id);

private:
    // After the XML parsing + function is nested, the XML string itself changes, so it is changed to an outer function
    bool ParseJobAd(const string& job_xml);
    bool ParseJobAdHo(const string& job_xml);
    bool ParseJobAdHe(const string& job_xml);
    // bool ParseJobAdByAdString(const string& job_ad);
    JobPtr CreateJobPtr();
    bool GetJobPrio(const string& str_job_prio, JobRawPrio& prio_type);
