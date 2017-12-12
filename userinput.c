#include <box/box.h>
#include "global.h"

char* userid = NULL;

void change_name(char* name)
{
    // 其实要发送广播
    //"name|userid-from|username"

    if(userid == NULL)
    {
        create_userid();
    }

    char buf[8192];
    sprintf(buf, "name|%s|%s", userid, name);

    // 发送
    broadcast(buf);
//    struct
//    sendto(udp_socket, buf, strlen(buf), 0, 广播地址);
}

void read_stdin(box_channel* c)
{
    char buf[8192];
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf)-1] = 0;

    if(strlen(buf)  == 0)
    {
        printf("不要乱敲\n");
        return;
    }

    char* cmd = strtok(buf, "|");
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtod(NULL, "\0");
        change_name(name);
    }
    else if(strcmp(cmd, "list") == 0)
    {

    }
    else if(strcmp(cmd, "msg") == 0)
    {

    }
    else if(strcmp(cmd, "msg-all") == 0)
    {

    }
    else if(strcmp(cmd, "file") == 0)
    {

    }
    else if(strcmp(cmd, "dir") == 0)
    {

    }
    else if(strcmp(cmd, "file-all") == 0)
    {

    }

    else if(strcmp(cmd, "dir-all") == 0)
    {

    }
    else
    {
        printf("unknown cmd\n");
        return;
    }


}

