#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <stdlib.h>
using namespace std;


// Read from the file into the string
string readFileIntoString(char * filename)
{
ifstream ifile(filename);
// Read the file into the ostringstream object BUF
ostringstream buf;
char ch;
ostringstream buf;
char ch;
while(buf&&ifile.get(ch))
buf.put(ch);
