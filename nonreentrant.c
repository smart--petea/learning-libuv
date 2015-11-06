#include <unistd.h>
#include <crypt.h>
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

static char *cryptArgv2;
static char *str2;      /*Set from argv[2] */
static int handled = 0; /*Counts number of calls to handler*/

static void handler(int sig)
{
    cryptArgv2 = crypt(str2, "xx");
    handled++;
}

int main(int argc, char* argv[])
{
    char *cr1;
    int callNum, mismatch;
    struct sigaction sa;

    if(argc != 3)
        usageErr("%s str1 str2\n", argv[0]);

    str2 = argv[2];             /*Make argv[2] available to handler*/
    cr1 = strdup(crypt(argv[1], "xx")); /*Copy statically allocated string to another buffer*/
    printf("crypt = %s\n", cr1);

    if(cr1 == NULL)
        errExit("strdup");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");

    /*Repeteadly call crypt() using argv[1]. If interrrupted by a signal handler, the the static storate returned by
     * crypt() will
     * be overwritten by the results of encrypting argv[2], and
     * strcmp() will detect a mismathc with the value in 'cr1'.*/

    char *cryptArgv1, *cryptArgv2;
    for(callNum = 1, mismatch = 0; ; callNum++)
    {
        cryptArgv1 = crypt(argv[1], "xx");
        printf("\n\ncr1 = %s\n", cr1);
        printf("cryptArgv1 = %s\n", cryptArgv1);
        printf("cryptArgv2 = %s\n", cryptArgv2);

        if(strcmp(cryptArgv1, cr1) != 0)
        {
            return 0;
            mismatch++;
            printf("Mismatch on call %d (mismatch=%d handled=%d)\n", callNum, mismatch, handled);
        }
    }

    return 0;
}

