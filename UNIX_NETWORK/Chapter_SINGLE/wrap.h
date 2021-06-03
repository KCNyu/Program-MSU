#ifndef _WRAP_H_
#define _WRAP_H_

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void sys_err(const char *str);
int Socket(int domain, int type, int protocol);
int Listen(int sockfd, int backlog);

#endif
