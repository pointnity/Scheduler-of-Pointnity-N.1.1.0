/*
 * lxc: linux Container library

#ifdef __cplusplus
extern "C" {
#endif

struct lxc_conf;
struct lxc_list;

extern int lxc_config_read(const char *file, struct lxc_conf *conf);
extern int lxc_config_readline(char *buffer, struct lxc_conf *conf);

extern int lxc_config_define_add(struct lxc_list *defines, char* arg);
