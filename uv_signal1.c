#include <uv.h>
#include <stdlib.h>
#include <stdio.h>

void sigIntClbk(uv_signal_t* handler, int signum)
{
    printf("Sigint ...");
    uv_stop(handler->loop);
}

void sigTstpClbk(uv_signal_t* handler, int signum)
{
    printf("Sigtstp ...");
    uv_stop(handler->loop);
}

int main()
{
    uv_loop_t* loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    uv_signal_t sigInt;
    uv_signal_init(loop, &sigInt);
    uv_signal_start(&sigInt, sigIntClbk, SIGINT);

    uv_signal_t sigTstp;
    uv_signal_init(loop, &sigTstp);
    uv_signal_start(&sigTstp, sigTstpClbk, SIGTSTP);

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);

    //printf("Out...");
    return 0;
}
