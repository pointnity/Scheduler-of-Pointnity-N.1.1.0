#include "classad/classad_distribution.h"
#include <iostream>

using namespace std;
#ifdef WANT_CLASSAD_NAMESPACE
using namespace classad;
#endif

string job_classad_text = 
"["
"Requirements = (other.memory >= 4000);"
"]";

string machine_classad_text = 
"["
"]";

int main(int, char **)
{
	// First we turn the textual description of the ClassAd into 
	// our internal representation of the ClassAd. 
	ClassAdParser  parser;
	ClassAd        *job_classad, *machine_classad;

	job_classad     = parser.ParseClassAd(job_classad_text, true);
	machine_classad = parser.ParseClassAd(machine_classad_text, true);
       
        machine_classad->InsertAttr("memory", 5000);
        if(!machine_classad->InsertAttr("memory", 4500)){ 
            printf("error\n");
        }

        int val;
        if(!machine_classad->EvaluateAttrInt("memory", val)) {
            printf("error\n"); 
        }
        printf("%d\n", val);

	// Next we print out the ClassAds. This requires unparsing them first.
