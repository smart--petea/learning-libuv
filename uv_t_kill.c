#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int s, sig;

    if(argc != 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s sig-num pid\n", argv[0]);
        return 0;
    }

    sig = atoi(argv[2]);

    s = uv_kill(atol(argv[1]), sig);

    if(sig != 0) {
        if(s == -1) {
            printf("kill");
            return 1;
        }
    } else {
        if(s == 0) {
            printf("Process exists and we can send it a signal\n");
        } else {
            if(errno == EPERM)
                printf("Process exists, but we don't have "
                        "permission to send it a signal\n");
            else if(errno == ESRCH)
                printf("Process does not exist\n");
            else {
                printf("kill");
                return 1;
            }
        }
    }

    exit(EXIT_SUCCESS);
}
