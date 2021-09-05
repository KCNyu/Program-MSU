#define MAX_MESG_LEN   1024

#define LEVEL_DEBUG 0
#define LEVEL_INFO  1
#define LEVEL_WARN  2
#define LEVEL_ERROR 3

static const char * LOG_STR[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
};

//可变参数
//输出日期，时间，日志级别，源码文件，行号，信息
//'\'后面不要加注释
#define LOG(level, format, ...) do{ \
    if (level >= LEVEL_DEBUG) {\
        time_t now = time(NULL);                      \
        char msg[MAX_MESG_LEN];                        \
        char buf[32];                                   \
        sprintf(msg, format, ##__VA_ARGS__);             \
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now)); \
        fprintf(stdout, "[%s] [%s] [%s] [%s:%d] %s", LOG_STR[level], buf, __FILE__, __FUNCTION__, __LINE__, msg); \
        fflush (stdout); \
    }\
     if (level == LEVEL_ERROR) {\
        exit(-1); \
    } \
} while(0)

#define LOG_INFO(format, ...)                                                                           \
{                                                                                                       \
    time_t t = time(0);                                                                                 \
    struct tm ttt = *localtime(&t);                                                                     \
    fprintf(stdout, "[INFO] [%4d-%02d-%02d %02d:%02d:%02d] [%s] [%s:%d] " format "",                     \
            ttt.tm_year + 1900, ttt.tm_mon + 1, ttt.tm_mday, ttt.tm_hour,        \
            ttt.tm_min, ttt.tm_sec, __FILE__, __FUNCTION__ , __LINE__, ##__VA_ARGS__);                            \
}
