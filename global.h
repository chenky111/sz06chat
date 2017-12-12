#ifndef GLOBAL_H
#define GLOBAL_H

#include <box/box.h>
extern char* userid;
extern int udp_socket;

#define UDP_PORT 9999
#define TCP_PORT 9998

typedef struct User
{
    char* userid;
    char* username;
    box_channel* c;
    struct User* next;
} User;

extern User* users;

static User* findUser(char* userid)
{
    User* user = users;
    while(user)
    {
        if(strcmp(user->userid, userid) == 0)
            return user;
        user= user->next;
    }
    return NULL;
}

static void addUser(char* userid, char* username, box_channel* c)
{
    User* user = findUser(userid);
    if(user == NULL)
    {
        user = box_malloc(sizeof(*user));
        user->next = users;
        user->c = c;
        user->userid = strdup(userid);
        user->username = strdup(username);
        users = user;
    }
    else
    {
        free(user->username);
        user->username = strdup(username);
    }
}

static void broadcast(char* buf)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_PORT);
    addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    sendto(udp_socket, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
}

// ifconfig | grep inet | grep -v inet6 | awk '{print $2}' | awk -F ":" '{print $2}'
static void create_userid()
{
    char buf[1024];
    FILE* fp = popen("ifconfig | grep inet | grep -v inet6 | awk '{print $2}' | awk -F \":\" '{print $2}'", "r");
    fgets(buf, sizeof(buf), fp);
    buf[strlen(buf)-1] = 0;

    //   userid = malloc(strlen(buf)+1);
    //   strcpy(userid, buf);

    userid = strdup(buf);
}

#endif // GLOBAL_H
