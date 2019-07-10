#include <stdio.h>
#include <boost/shared_ptr.hpp>
#include <list>
#include <classad/classad.h>
#include <classad/classad_distribution.h>
#include "include/attributes.h"

int main(int argc, char ** argv) {

    ClassAd ad;
    ad.InsertAttr(ATTR_NEED_VCPU, 1);
    ad.InsertAttr(ATTR_NEED_MEMORY, 1024);
    ClassAdParser parser;
    printf("%s\n", EXP_TASK_RANK.c_str());
    ExprTree* expr = parser.ParseExpression(EXP_TASK_RANK);
    ad.Insert(ATTR_TASK_RANK, expr);
    ExprTree* re_expr = parser.ParseExpression(EXP_TASK_REQUIREMENT);
    ad.Insert(ATTR_TASK_REQUIREMENT, re_expr);
   
    ClassAd c1;
    c1.InsertAttr(ATTR_ALL_VCPU, 4);
