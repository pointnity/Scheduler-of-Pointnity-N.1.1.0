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
    virConnectPtr conn = virConnectOpen("qemu:///system");
    if (NULL == conn) {
        printf("Failed to open connection to qemu:///system\n");
        return -1;
    }

    // get domain list
    int num_domains = virConnectNumOfDomains(conn);
    if (-1 == num_domains) {
        printf("Failed to get num of domains\n");
        return -1;
    }
    int *active_domains = (int*)malloc(sizeof(int) * num_domains);
    num_domains = virConnectListDomains(conn, active_domains, num_domains);
    if (-1 == num_domains) {
        printf("Failed to get domain list\n");
        return -1;
    }

    // shutdown domain list
    for (int i = 0; i < num_domains; i++) {
        virDomainPtr dom = virDomainLookupByID(conn, active_domains[i]);
        if (NULL == dom) {
            printf("Failed to find domain %d\n", active_domains[i]);
            continue;
        }
