extern int lxc_create_console(struct lxc_conf *);
extern void lxc_delete_console(struct lxc_console *);
extern int lxc_console_mainloop_add(struct lxc_epoll_descr *, struct lxc_handler *);
