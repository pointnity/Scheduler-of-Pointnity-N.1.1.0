#include <string>

#include <classad/classad.h>
#include <classad/classad_distribution.h>

using std::string;

int main(){
    string ad_string = "[a = 1; b = \"Cardini\"]";
    ClassAd ad;
    ClassAdParser parser;

    int val;

    if(!parser.ParseClassAd(ad_string, ad, true)){
       return 1;
