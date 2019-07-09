#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(int argc, char **argv)
{
	FILE *pstr; char cmd[128],buff[512],*p;
        pid_t pID;
        int pidnum;
