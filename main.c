#include <box/box.h>
#define UDP_PORT 9999
#define TCP_PORT 9998

void read_tcp(box_channel* c)
{

}

void accept_tcp(box_channel* c)
{
    while(1)
    {
        int tcp_socket = accept(c->sock, NULL, NULL);
        if(tcp_socket < 0) break;
        box_channel* c1 = box_channel_create(tcp_socket, read_tcp);
        box_add(c1);
    }
}

void read_stdin(box_channel* )
{
    fgets(buf, sizeof(buf), stdin);
}

void read_udp(box_channel* c)
{

}

int main()
{
    box_init();

    // 把文件描述符，加入到box
    box_channel* c = box_channel_create(0, read_stdin);
    box_add(c);

    // 创建一个UDP socket
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_PORT);
    addr.sin_addr.s_addr = 0;
    int ret = bind(udp_socket, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        printf("udp bind error\n");
        exit(1);
    }
    c = box_channel_create(udp_socket, read_udp);
    box_add(c);

    // 创建一个TCP Server
    int tcp_server = __box_start_server(TCP_PORT, "0.0.0.0", 10);
    c = box_channel_create(tcp_server, accept_tcp);
    box_add(c);

    box_run();
    box_fini();
}
