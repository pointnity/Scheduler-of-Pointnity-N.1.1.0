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
            return;
        }

        string tmp;
        string::size_type pos_begin = str.find_first_not_of(sep);
        string::size_type comma_pos = 0;

        while (pos_begin != string::npos) {
            comma_pos = str.find(sep, pos_begin);
            if (comma_pos != string::npos) {
                tmp = str.substr(pos_begin, comma_pos - pos_begin);
                pos_begin = comma_pos + sep.length();
            } else {
                tmp = str.substr(pos_begin);
                pos_begin = comma_pos;
            }

            if (!tmp.empty()) {
                ret_strs.push_back(tmp);
                tmp.clear();
            }
        }
        return;
    }

    static string Replace(const string& str, const string& src, const string& dest) {
        string ret;

        string::size_type pos_begin = 0;
        string::size_type pos = str.find(src);
        while (pos != string::npos) {
            // cout <<"replacexxx:" << pos_begin <<" " << pos <<"\n";
            ret.append(str.data() + pos_begin, pos - pos_begin);
            ret += dest;
