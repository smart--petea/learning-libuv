#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

void sigHandler(uv_signal_t *handle, int signum)
{
    static int count = 0;
    printf("sigHandler\n");

    if(signum == SIGINT)
    {
        count++;
        printf("Caught SIGINT (%d)\n", count);
        return;                 /*Resume execution at point of interruption*/
    }

    /*Must be SIGQUIT - print a message and terminate the process*/

    printf("Caught SIGQUIT - that's all folks!\n");

    uv_signal_stop(handle);
    exit(0);
}

int main(int argc, char *argv[])
{
   uv_loop_t *loop = malloc(sizeof(uv_loop_t));
   uv_loop_init(loop);

   uv_signal_t sig1;
   uv_signal_init(loop, &sig1);
   uv_signal_start(&sig1, sigHandler, SIGQUIT);

   uv_signal_t sig2;
   uv_signal_init(loop, &sig2);
   uv_signal_start(&sig2, sigHandler, SIGINT);

   uv_run(loop, UV_RUN_DEFAULT);

   uv_loop_close(loop);
   free(loop);


   return 0;
}
