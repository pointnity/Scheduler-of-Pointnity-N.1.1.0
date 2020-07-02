/********************************
 FileName: executor/clean_environment.h
 Version:  0.1
 Description: clean environment, include libvirt and lxc
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <string.h>
#include <fstream>

using std::ifstream;
using std::string;

int32_t CleanLibvirt() {
    // build connection
    // build connection
