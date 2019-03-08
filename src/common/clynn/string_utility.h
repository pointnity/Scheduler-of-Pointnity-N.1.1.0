/********************************
 FileName: commom/string_utility.h


 Version:  0.1
 Description: string encapsulation
*********************************/

#ifndef SRC_COMMON_STRING_UTILITY_H
#define SRC_COMMON_STRING_UTILITY_H

#include <string>
#include <vector>
#include <assert.h>

using std::string;
using std::vector;

class StringUtility
{
public:
    static void Split(const string& str, vector<string>& ret_strs, string sep = ",") {
        if (str.empty()) {
