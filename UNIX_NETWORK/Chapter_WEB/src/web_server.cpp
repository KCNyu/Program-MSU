/*================================================================
* Filename:web_server.cpp
* Author: KCN_yu
* Createtime:Sat 19 Jun 2021 02:18:04 PM CST
================================================================*/

#include "../inc/web_server.h"
using namespace std;

WebServer::WebServer(int pt):port(pt){
    epfd = epoll_create(MAXSIZE);
    if (epfd == -1) {
        cerr << "epoll_create error" << endl;
        exit(1);
    }
    InitListenfd();
}
void WebServer::RunServer(){
    // ask the fd in epoll
    while(true) {
        int ret = epoll_wait(epfd, events, MAXSIZE, 0);
        if(ret == -1) {
            cerr << "epoll_wait error" << endl;
        }

        // Traverse the fd which has changes
        for(int i = 0; i < ret; i++) {
            struct epoll_event *pev = &events[i];
            // only solve the read events
            if(!(pev->events & EPOLLIN)) {
                continue;
            }
            if(pev->data.fd == lfd) {
                AcceptFd();
            } else {
                printf("====== BEFORE DO READ RET %d ======\n", ret);
                ReadFd(pev->data.fd);
                printf("======= AFTER DO READ RET %d ======\n", ret);
            }
        }
    }
}
// get new connect
void WebServer::AcceptFd(){
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int cfd = accept(lfd , reinterpret_cast<struct sockaddr*>(&client), &len);
    if(cfd == -1) {
        cerr << "accept error" << endl;
        exit(1);
    }

    // print info of client
    char ip[64] = {0};
    printf("New Client IP: %s, Port: %d, cfd = %d\n",
           inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof(ip)),
           ntohs(client.sin_port), cfd);

    // set cfd nonblock
    int flag = fcntl(cfd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(cfd, F_SETFL, flag);

    // add cfd in epoll
    struct epoll_event ev;
    ev.data.fd = cfd;
    // set ET mode
    ev.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
    if(ret == -1) {
        cerr << "epoll_ctl add cfd error" << endl;
        exit(1);
    }
}
void WebServer::InitListenfd(){

    // Init listenfd socket
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        cerr << "socket error" << endl;
        exit(1);
    }

    // set listenfd
    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    // reuse the port
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // listenfd bind to local IP and port
    int ret = bind(lfd, reinterpret_cast<struct sockaddr*>(&serv), sizeof(serv));
    if(ret == -1) {
        cerr << "bind error" << endl;
        exit(1);
    }

    // set listen
    ret = listen(lfd, 64);
    if(ret == -1) {
        cerr << "listen error" << endl;
        exit(1);
    }

    // add listenfd to epoll
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
    if(ret == -1) {
        cerr << "epoll_ctl add lfd error" << endl;
        exit(1);
    }
}
int WebServer::GetLine(int sock, char* buf, int size){
    int i = 0;
    char c = '\0';
    int n;
    while ((i < size - 1) && (c != '\n')) {
        n = recv(sock, &c, 1, 0);
        if (n > 0) {
            if (c == '\r') {
                n = recv(sock, &c, 1, MSG_PEEK);
                if ((n > 0) && (c == '\n')) {
                    recv(sock, &c, 1, 0);
                } else {
                    c = '\n';
                }
            }
            buf[i] = c;
            i++;
        } else {
            c = '\n';
        }
    }
    buf[i] = '\0';

    return i;
}
void WebServer::ReadFd(int cfd){
    char line[1024] = {0};

    int len = GetLine(cfd, line, sizeof(line));
    if(len == 0) {
        cout << "Client Disconnect..." << endl;
        Disconnect(cfd);
    } else {
        cout << "====== HEAD ======" << endl;
        cout << "GET DATA: " << line << endl;

        while (1) {
            char buf[1024] = {0};
            len = GetLine(cfd, buf, sizeof(buf));
			if (buf[0] == '\n') {
				break;
			} else if (len == -1)
				break;
        }
        cout << "====== END ======" << endl;
    }

    if(strncasecmp("GET", line, 3) == 0) {
        HttpRequest(cfd, line);
        Disconnect(cfd);
    }
}
void WebServer::Disconnect(int cfd){
    int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
    if(ret == -1) {
        cerr << "epoll_ctl del cfd error" << endl;
        exit(1);
    }
    close(cfd);
}
void WebServer::HttpRequest(int cfd, const char* request){

    // analyze http request
    char method[12], path[1024], protocol[12];
    sscanf(request, "%[^ ] %[^ ] %[^ ]", method, path, protocol);
    printf("method = %s, path = %s, protocol = %s\n", method, path, protocol);

    const char *file = path+1;

    if(strcmp(path, "/") == 0) {
        file = "./";
    }

    struct stat st;
    int ret = stat(file, &st);
    if(ret == -1) {
        SendError(cfd, 404, "Not Found", "NO such file or direntry");
        return;
    }

    if(S_ISDIR(st.st_mode)) {
        SendRespondHead(cfd, 200, "OK", GetFileType(".html"), -1);
        SendDir(cfd, file);
    } else if(S_ISREG(st.st_mode)) {
        SendRespondHead(cfd, 200, "OK", GetFileType(file), st.st_size);
        SendFile(cfd, file);
    }

}
void WebServer::SendError(int cfd, int status, const char *title, const char *text){
	char buf[4096] = {0};

	sprintf(buf, "%s %d %s\r\n", "HTTP/1.1", status, title);
	sprintf(buf+strlen(buf), "Content-Type:%s\r\n", "text/html");
	sprintf(buf+strlen(buf), "Content-Length:%d\r\n", -1);
	sprintf(buf+strlen(buf), "Connection: close\r\n");
	send(cfd, buf, strlen(buf), 0);
	send(cfd, "\r\n", 2, 0);

    bzero(buf, sizeof(buf));

	sprintf(buf, "<html><head><title>%d %s</title></head>\n", status, title);
	sprintf(buf+strlen(buf), "<body bgcolor=\"#87CEEB\"><h2 align=\"center\">%d %s</h4>\n", status, title);
	sprintf(buf+strlen(buf), "%s\n", text);
	sprintf(buf+strlen(buf), "<hr>\n</body>\n</html>\n");
	send(cfd, buf, strlen(buf), 0);

}
void WebServer::SendRespondHead(int cfd, int no, const char* desp, const char* type, long len)
{
    char buf[1024] = {0};
    // status
    sprintf(buf, "http/1.1 %d %s\r\n", no, desp);
    send(cfd, buf, strlen(buf), 0);
    // message head
    sprintf(buf, "Content-Type:%s\r\n", type);
    sprintf(buf+strlen(buf), "Content-Length:%ld\r\n", len);
    send(cfd, buf, strlen(buf), 0);
    // blank line
    send(cfd, "\r\n", 2, 0);
}
void WebServer::SendDir(int cfd, const char* dirname){
}
void WebServer::SendFile(int cfd, const char* filename){
    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        SendError(cfd, 404, "Not Found", "NO such file or direntry");
        exit(1);
    }

    char buf[4096] = {0};
    int len = 0, ret = 0;
    while( (len = read(fd, buf, sizeof(buf))) > 0 ) {
        ret = send(cfd, buf, len, 0);
        if (ret == -1) {
            if (errno == EAGAIN) {
                cerr << "send error" << endl;
                continue;
            } else if (errno == EINTR) {
                cerr << "send error" << endl;
                continue;
            } else {
                cerr << "send error" << endl;
                exit(1);
            }
        }
    }
    if(len == -1)  {
        cerr << "read file error" << endl;
        exit(1);
    }

}
const char* WebServer::GetFileType(const char *name){
    const char* dot;

    // from right to research '.'
    dot = strrchr(name, '.');
    if (dot == nullptr)
        return "text/plain; charset=utf-8";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp( dot, ".wav" ) == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";
}
