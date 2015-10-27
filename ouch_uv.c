#include <uv.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

static void sigHandler(uv_signal_t* sig, int signum)
{
    printf("Ouch!\n");
}

int main(int argc, char *argv[])
{
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    if(loop)
        uv_loop_init(loop);
    else
    {
        printf("Can't init loop\n");
        exit(1);
    }

    uv_signal_t sig1;
    uv_signal_init(loop, &sig1);
    uv_signal_start(&sig1, sigHandler, SIGINT); //uv_signal_stop is not stoped

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);

    return 0;
}
