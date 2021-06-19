#ifndef WEB_SERVER_H

#define WEB_SERVER_H
#include <arpa/inet.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXSIZE 1024

class WebServer {
    private:
        int port;
        int epfd;
        int lfd;
        struct epoll_event events[MAXSIZE];

    public:
        WebServer(int port);
        void RunServer();
        void InitListenfd();
        void AcceptFd();
        void ReadFd(int cfd);
        void Disconnect(int cfd);
        void HttpRequest(int cfd, const char *request);
        void SendRespondHead(int cfd, int no, const char *desp, const char *type,
                long len);
        void SendError(int cfd, int status, const char *title, const char *text);
        void SendDir(int cfd, const char *dirname);
        void SendFile(int cfd, const char *filename);
        const char *GetFileType(const char *name);
        int GetLine(int sock, char *buf, int size);
        void encode_str(char *to, int tosize, const char *from);
        int hexit(char c);
        void decode_str(char *to, char *from);
        virtual ~WebServer() = default;
};

#endif /* WEB_SERVER_H */
