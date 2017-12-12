
#include "global.h"

User* users = NULL;

// 保存用户信息
static void change_name(char* userid, char* name)
{
    addUser(userid, name);
}

void read_udp(box_channel* c)
{
    char buf[8192];
    int ret = read(c->sock, buf, sizeof(buf));
    buf[ret ] = 0;

    printf("recv buf: %s\n", buf);

    if(userid == NULL)
    {
        printf("my userid is null\n");
        return;
    }

    // 判断是否自己发的消息
    char* cmd = strtok(buf, "|");
    char* userid_from = strtok(NULL,  "|");
    if(strcmp(userid_from, userid) == 0)
    {
        return;
    }

    // 如果是改名
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtok(NULL, "|");
        change_name(userid, name);
    }

}
