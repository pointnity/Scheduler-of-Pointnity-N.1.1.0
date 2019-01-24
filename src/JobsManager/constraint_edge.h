/********************************
 FileName: JobsManager/constraint_edge.h


 Version:  0.1
 Description: constraints in the form of edges
*********************************/

#ifndef JOBS_MANAGER_CONSTRAINT_EDGE_H
#define JOBS_MANAGER_CONSTRAINT_EDGE_H

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class ConstraintEdge {
public:
    ConstraintEdge(int32_t s, int32_t e, int32_t w) {
        m_start = s;
        m_end = e;
        m_weight = w; 
    }
