#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(int argc, char **argv)
{
	FILE *pstr; char cmd[128],buff[512],*p;
        pid_t pID;
        int pidnum;
	printf("argc:%d", argc);
	if(argc != 2) {
	    printf("yes\n");
	    return -1;
        }
	char *name= argv[1];
	int ret=3;
	memset(cmd,0,sizeof(cmd));

	sprintf(cmd, "ps -ef|grep %s ",name);
	pstr=popen(cmd, "r");
	if(pstr==NULL){ 
	    return 1; 
	}
	memset(buff,0,sizeof(buff));
	fgets(buff,512,pstr);
	p=strtok(buff, " ");
	p=strtok(NULL, " "); //Whether this sentence is removed depends on whether the process ID number is the first field after the ps in the current system pclose(pstr);
	if(p==NULL)
	{ return 1; }
	if(strlen(p)==0)
	{ return 1; }
	if((pidnum=atoi(p))==0)
	{ return 1; }
	printf("pidnum: %d\n",pidnum);
	pID=(pid_t)pidnum;
	ret=kill(pID,0);//Instead of killing the process, verify that the process really exists, returning 0 means it really exists.
	printf("ret= %d \n",ret);
	if(0==ret)
	    printf("process: %s exist!\n",name);
	else 
	    printf("process: %s not exist!\n",name);
