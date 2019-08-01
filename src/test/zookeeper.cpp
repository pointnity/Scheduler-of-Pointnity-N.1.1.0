#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>

void watcher(zhandle_t *zzh, int32_t type, int32_t state, const char *path, void *watcherCtx){}

int32_t main(int argc, char* argv[]){
