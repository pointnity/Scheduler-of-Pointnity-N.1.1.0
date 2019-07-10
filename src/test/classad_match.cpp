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
