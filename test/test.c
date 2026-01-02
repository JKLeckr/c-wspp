#include <c-wspp.h>

// test file

int main(int argc, char** argv)
{
    int res = 0;
    wspp_ws* ws = wspp_new("ws://localhost:38281");
    wspp_connect(ws);
    int loop = 0;
    while(!wspp_poll(ws)) {
        if (loop > 5000) {
            res = 1;
            break;
        }
    }
    wspp_close(ws, 0, "Done");
    return res;
}
