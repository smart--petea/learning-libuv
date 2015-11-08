#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

void crunch_away(uv_idle_t* handle)
{
    //Compute extra-terrestrial life
    //fold proteins
    //computer another digit of PI
    //or similar
    fprintf(stderr, "Computing PI...\n");
    //just to avoid overwhelming your terminal emulator
    //uv_idle_stop(handle);
}

int main()
{
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    uv_idle_t idler;
    uv_idle_init(loop, &idler);
    uv_idle_start(&idler, crunch_away);

    uv_run(loop, UV_RUN_DEFAULT);

    uv_stop(loop);
    free(loop);
    return 0;
}
