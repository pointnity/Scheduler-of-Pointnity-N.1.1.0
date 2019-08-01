#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>

void watcher(zhandle_t *zzh, int32_t type, int32_t state, const char *path, void *watcherCtx){}

int32_t main(int argc, char* argv[]){
    zoo_set_debug_level(ZOO_LOG_LEVEL_INFO);
    zhandle_t *zh = zookeeper_init("localhost:2181", watcher, 10000, 0, 0, 0);
    char buffer[512];
    if(!zh) {
        return errno;
