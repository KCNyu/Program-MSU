/*================================================================
 * Filename:AirManager.cpp
 * Author: KCN_yu
 * Createtime:Wed 06 Jan 2021 02:39:00 PM CST
 ================================================================*/

#include "AirManager.h"

using namespace std;

string Country_to_string(Country c) {
    string res;
    switch (c) {
        case 0:
            res = "England";
            break;
        case 1:
            res = "America";
            break;
        case 2:
            res = "Canada ";
            break;
        case 3:
            res = "Russia ";
            break;
        case 4:
            res = "France ";
            break;
        case 5:
            res = "Germany";
            break;
        case 6:
            res = "Japan  ";
            break;
        case 7:
            res = "China  ";
            break;
    }
    return res;
}
string Airline_to_string(Airline a) {
    string res;
    switch (a) {
        case 0:
            res = "AA";
            break;
        case 1:
            res = "MU";
            break;
        case 2:
            res = "BA";
            break;
        case 3:
            res = "FK";
            break;
        case 4:
            res = "QR";
            break;
        case 5:
            res = "SQ";
            break;
        case 6:
            res = "UA";
            break;
        case 7:
            res = "SU";
            break;
    }
    return res;
}
Country string_to_Country(char *s) {
    Country c;
    if (strcmp(s, "England\n") == 0)
        c = England;
    else if (strcmp(s, "America\n") == 0)
        c = America;
    else if (strcmp(s, "Canada\n") == 0)
        c = Canada;
    else if (strcmp(s, "Russia\n") == 0)
        c = Russia;
    else if (strcmp(s, "France\n") == 0)
        c = France;
    else if (strcmp(s, "Germany\n") == 0)
        c = Germany;
    else if (strcmp(s, "Japan\n") == 0)
        c = Japan;
    else if (strcmp(s, "China\n") == 0)
        c = China;
    else
        throw "ERROR";
    return c;
}
Airline string_to_Airline(char *s) {
    Airline a;
    if (strcmp(s, "AA\n") == 0)
        a = AA;
    else if (strcmp(s, "MU\n") == 0)
        a = MU;
    else if (strcmp(s, "BA\n") == 0)
        a = BA;
    else if (strcmp(s, "FK\n") == 0)
        a = FK;
    else if (strcmp(s, "QR\n") == 0)
        a = QR;
    else if (strcmp(s, "SQ\n") == 0)
        a = SQ;
    else if (strcmp(s, "UA\n") == 0)
        a = UA;
    else if (strcmp(s, "SU\n") == 0)
        a = SU;
    else
        throw "ERROR";
    return a;
}

/////////////////////////////////////////////////////////////////////////

FlightInfo::FlightInfo() {
    int f_r = rand() % 8;
    int f_t = rand() % 8;
    int f_a = rand() % 8;
    int f_h = rand() % 23;
    int f_m = rand() % 59;
    int f_d = rand() % 23;
    while (f_t == f_r)
        f_t = rand() % 8;

    from = (Country)f_r;
    to = (Country)f_t;
    airline = (Airline)f_a;
    string h, m;
    if (f_h < 10)
        h = '0' + to_string(f_h);
    else
        h = to_string(f_h);
    if (f_m < 10)
        m = '0' + to_string(f_m);
    else
        m = to_string(f_m);
    departure = h + ":" + m;
    duration = 2 + f_d * 0.9;
}
FlightInfo::FlightInfo(char cmd[][MAX_LEN]) {
    from = string_to_Country(cmd[1]);
    to = string_to_Country(cmd[2]);
    airline = string_to_Airline(cmd[3]);
    departure = cmd[4];
    duration = atof(cmd[5]);
}
Country FlightInfo::GetFrom_country() const { return from; }
Country FlightInfo::GetTo_country() const { return to; }
Airline FlightInfo::GetAirline_Airline() const { return airline; }
string FlightInfo::GetFrom() const { return Country_to_string(from); }
string FlightInfo::GetTo() const { return Country_to_string(to); }
string FlightInfo::GetAirline() const { return Airline_to_string(airline); }
string FlightInfo::GetDeparture() const { return departure; }
double FlightInfo::GetDuration() const { return duration; }
ostream &operator<<(ostream &os, const FlightInfo &info) {
    string tmp = to_string(info.GetDuration());
    tmp.resize(tmp.size() - 5);
    os << "FROM: " << info.GetFrom() << " ";
    os.width(4);
    os << "TO: " << setw(4) << info.GetTo() << " ";
    os.width(4);
    os << "AIRLINE: " << setw(2) << info.GetAirline() << " ";
    os.width(4);
    os << "DEPARTURE: " << setw(4) << info.GetDeparture() << " ";
    os << "DURATION: " << setw(4) << tmp << "hours";
    os << endl;
    return os;
}
string FlightInfo::print() const {
    stringstream ss;
    streambuf *buffer = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    cout << *this;
    string res(ss.str());
    cout.rdbuf(buffer);
    return res;
}

/////////////////////////////////////////////////////////////////////////

FlightAll::FlightAll() { nKol = 0; }
FlightInfo FlightAll::GetFlight(int i) const { return Flights[i]; }
Country FlightAll::GetFrom_country(int i) const {
    return Flights[i].GetFrom_country();
}
Country FlightAll::GetTo_country(int i) const {
    return Flights[i].GetTo_country();
}
Airline FlightAll::GetAirline_Airline(int i) const {
    return Flights[i].GetAirline_Airline();
}
int FlightAll::GetKol() const { return nKol; }
string FlightAll::GetFrom(int i) const { return Flights[i].GetFrom(); }
string FlightAll::GetTo(int i) const { return Flights[i].GetTo(); }
string FlightAll::GetAirline(int i) const { return Flights[i].GetAirline(); }
string FlightAll::GetDeparture(int i) const {
    return Flights[i].GetDeparture();
}
double FlightAll::GetDuration(int i) { return Flights[i].GetDuration(); }
bool FlightAll::Add(FlightInfo &info) {
    Flights.push_back(info);
    nKol++;
    return true;
}
ostream &operator<<(ostream &os, const FlightAll &flall) {
    for (int i = 0; i < flall.nKol; i++) {
        os.width(4);
        os << i << ".  ";
        os << flall.Flights[i] << endl;
    }
    return os;
}
string FlightAll::print() const {
    stringstream ss;
    streambuf *buffer = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    cout << *this;
    string res(ss.str());
    cout.rdbuf(buffer);
    return res;
}

/////////////////////////////////////////////////////////////////////////

void InitFlightTreeAll(FlightAll &flall, Tree<Country> &treeFrom,
        Tree<Country> &treeTo, Tree<Airline> &treeAirline,
        const int nFl) {
    for (int i = 0; i < nFl; i++) {
        FlightInfo f;
        flall.Add(f);

        Country c_from = flall.GetFrom_country(i);
        Country c_to = flall.GetTo_country(i);
        Airline a = flall.GetAirline_Airline(i);
        treeFrom.Add(&c_from, NULL, flall.GetKol() - 1);
        treeTo.Add(&c_to, NULL, flall.GetKol() - 1);
        treeAirline.Add(&a, NULL, flall.GetKol() - 1);
    }
}
void AvoidBindError(int &server_socket) {
    int on = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
}
void InitServerSocket(int &server_socket, sockaddr_in &server_addr) {
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SRV_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, reinterpret_cast<sockaddr *>(&server_addr),
                sizeof server_addr)) {
        cerr << "bind() error!" << endl;
        exit(-1);
    }

    if (listen(server_socket, LISTEN_MAX)) {
        cerr << "listen() error!" << endl;
        exit(-1);
    }
}
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int n;

again:
    if ((n = accept(sockfd, addr, addrlen)) < 0) {
        if ((errno == ECONNABORTED) || (errno == EINTR))
            goto again;
        else {
            cerr << "accept error" << endl;
            exit(1);
        }
    }
    return n;
}
void PrintInfoClient(const sockaddr_in &clit_addr,
        const socklen_t &clit_addr_len) {
    char client_IP[INET_ADDRSTRLEN];
    cout << "-------------------------------------" << endl;
    cout << "clit_addr_len = " << clit_addr_len << endl;
    printf("client ip:%s port:%d\n",
            inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, client_IP,
                sizeof(client_IP)),
            ntohs(clit_addr.sin_port));
    cout << "-------------------------------------" << endl;
}
void ReceivedInfoClient(const sockaddr_in &clit_addr){
    char client_IP[INET_ADDRSTRLEN];
    printf("received from: %s PORT:%d\n",
            inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, client_IP,
                sizeof(client_IP)),
            ntohs(clit_addr.sin_port));
    cout << "=====================================" << endl;
}
ssize_t Read(int fd, void *buf, size_t count) {
    ssize_t read_len;
    if ((read_len = read(fd, buf, count)) == 0) {
        cout << "Client launched chat" << endl;
        return -1;
    }
    cout << "=====================================" << endl;
    cout << "Client: " << static_cast<char *>(buf);
    return read_len;
}
void BlockSIGCHLD(sigset_t &set) {
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);
}
void catch_child(int signum) {
    pid_t pid;
    while ((pid = waitpid(0, nullptr, WNOHANG)) > 0){
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "catch the child: " << pid << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
}
void SigAction(sigset_t &set) {
    struct sigaction act;
    act.sa_handler = catch_child;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, nullptr);
    sigprocmask(SIG_UNBLOCK, &set, nullptr);
}
void WriteMsg(FlightAll &flall, Tree<Country> &treeFrom, Tree<Country> &treeTo,
        Tree<Airline> &treeAirline, int fd, char *message) {
    if (strcmp(message, "SHOW\n") == 0) {
        strcpy(message, flall.print().c_str());
    } else if (strncmp(message, "FROM", 4) == 0) {
        Country c = string_to_Country(message + 5);
        strcpy(message, treeFrom.Search_print(&c, flall).c_str());
    } else if (strncmp(message, "TO", 2) == 0) {
        Country c = string_to_Country(message + 3);
        strcpy(message, treeTo.Search_print(&c, flall).c_str());
    } else if (strncmp(message, "AIRLINE", 7) == 0) {
        Airline a = string_to_Airline(message + 8);
        strcpy(message, treeAirline.Search_print(&a, flall).c_str());
    }  else if (strncmp(message, "ADD", 3) == 0) {
        char cmd[MAX_LEN][MAX_LEN];
        char** cmd_tmp = (char**)calloc(sizeof(char*),64);
        bzero(cmd,sizeof(cmd));
        int i = 0;
        cmd_tmp[i++] = strtok(message," ");
        while((cmd_tmp[i] = strtok(NULL," ")) != NULL){
            i++;
        }
        for(int k = 1; k < 6; k++){
            sprintf(cmd[k],"%s\n",cmd_tmp[k]);
            if(k > 3){
                strcpy(cmd[k],cmd_tmp[k]);
            }
        }
        free(cmd_tmp);
        FlightInfo f(cmd);
        flall.Add(f);
        int index = flall.GetKol()-1;
        Country c_from = flall.GetFrom_country(index);
        Country c_to = flall.GetTo_country(index);
        Airline a = flall.GetAirline_Airline(index);
        treeFrom.Add(&c_from, NULL, index);
        treeTo.Add(&c_to, NULL, index);
        treeAirline.Add(&a, NULL, index);
        strcpy(message, "add recevied!\n");
    }
    else {
        strcpy(message, "recevied!\n");
    }

    size_t w_len = write(fd, message, strlen(message));

    if (w_len != strlen(message)) {
        cout << "write() error!" << endl;
        exit(-1);
    }
}
