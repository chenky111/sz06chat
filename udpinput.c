
#include "global.h"

void read_udp(box_channel* c)
{
    char buf[8192];
    int ret = read(c->sock, buf, sizeof(buf));
    buf[ret ] = 0;

    printf("recv buf: %s\n", buf);

}
