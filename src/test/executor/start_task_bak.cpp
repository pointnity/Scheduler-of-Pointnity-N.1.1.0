#include <iostream>
#include <string>
#include <string.h>

#include "common/clynn/rpc.h"
#include "include/proxy.h"

using namespace std;

static string usage = "./start_task task_id";

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "Usage is wrong." << endl;
        cout << "Usage is: " << usage << endl;
