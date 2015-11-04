#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{

    if(argc < 4 || strcmp(argv[1], "--help") == 0)
        printf("%s pi num-sigs sig-num [sig-num-2]\n", argv[0]);

    pid_t pid = atol(argv[1]);
    int numSigs = atoi(argv[2]);
    int sig = atoi(argv[3]);

    /*Send signals to receiver*/
    printf("%s: sending signal %d to process %ld %d times\n", argv[0], sig, (long) pid, numSigs);

    int j;
    for(j = 0; j < numSigs; j++)
        if(uv_kill(pid, sig) < 0)
            printf("sig(%d) - %s\n", sig, uv_err_name(uv_kill(pid, sig)));

    /*If a fourth command-line argument was specified, send that signal*/

    if(argc > 4) {
        sig = atoi(argv[4]);
        if(uv_kill(pid, sig ) < 0)
            printf("sig(%d) - %s\n", sig, uv_err_name(uv_kill(pid, sig)));
    }

    printf("%s: exiting\n", argv[0]);

    return 0;
}
