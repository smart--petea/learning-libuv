#define _GNU_SOURCE
#include <uv.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "signal_functions.h"       /*Declaration of printSigset*/

static int sigCnt[NSIG];            /*Counts deliveries of each signal*/

static void handler(uv_signal_t* handler, int signum) {
    if(signum == SIGINT)
    {
        printf("Hey I got SIGINT\n");
        uv_stop(handler->loop);
    }
    else
        sigCnt[signum]++;
}

int main(int argc, char* argv[])
{
    sigset_t pendingMask, blockingMask, emptyMask;
    int n, numSecs;

    printf("%s: PID is %ld\n", argv[0], (long) getpid());

    uv_loop_t* loop = malloc(sizeof(uv_loop_t));
    if(!loop)  {
        printf("can't allocate memory for uv_loop\n");
    }
    uv_loop_init(loop);

    uv_signal_t sig[NSIG - 1];
    for(n = 1; n < NSIG; n++) /*Same handler for all signals*/
    {
        uv_signal_init(loop, &sig[n - 1]);
        uv_signal_start(&sig[n - 1], handler, n);
    }

    if(argc > 1)
    {
        numSecs = atoi(argv[1]);
        sigfillset(&blockingMask);
        if(sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
        {
            printf("can't block all signals");
            return 1;
        }

        printf("%s: sleeping for %d seconds\n", argv[0], numSecs);
        sleep(numSecs);

        if(sigpending(&pendingMask) == -1)
        {
            printf("can't get pending signals\n");
            return 1;
        }

        sigemptyset(&emptyMask); /*Unblock all signals*/
        if(sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
        {
            printf("can't unblock from signals\n");
            return 1;
        }
    }

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);

    for(n = 1; n < NSIG; n++)
        if(sigCnt[n] != 0)
            printf("%s: signal %d caught %d time%s\n", argv[0], n, sigCnt[n], (sigCnt[n] == 1) ? "" : "s");

    return 0;
}
