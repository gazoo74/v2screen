#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#include "vodisp.h"
#include "stamp.h"

#define FBNAME    "/tmp/vodisp.map"

void do_test();
void signal_process(int);

int signal_int = 0;

int main(int argc, char *argv[])
{
    if(argc > 3) {
        printf("usage: vodisp [bitmap/test/framebuffer] [input file]\n");
        return 0;
    }

    vodisp_connect();
    if (argc == 1) {
        printf("display is ready.\n");
        return 0;
    }

    if (strstr(argv[1], "bitmap")) {
        vodisp_load_bitmap(argv[2], vodisp_get_framebuffer(NULL));
        vodisp_write_frame(vodisp_get_framebuffer(NULL));
    }

    if (!strcmp(argv[1], "test")) {
        do_test();
        return 0;
    }

    if (!strcmp(argv[1], "framebuffer")) {
        vodisp_get_framebuffer(FBNAME);   // alloc framebuffer here.

        if (argc == 3) {
            printf("write %s to framebuffer.\n", argv[2]);
            vodisp_load_bitmap(argv[2], vodisp_get_framebuffer(FBNAME));
            return 0;
        }

        printf("enable background render thread.\n");
        vodisp_set_auto_refresh(1);

        signal(SIGINT, signal_process);
        while (!signal_int)
            sleep(1);
        vodisp_set_auto_refresh(0);
        printf("disable background render thread.\n");
    }

    return 0;
}

void signal_process(int sig)
{
    if (sig == SIGINT)
        signal_int = 1;
}

void do_test()
{
    char *frame;
    int i;

    frame = vodisp_get_framebuffer(NULL);
    if (frame == NULL)
        return;

    // FIXME: fix the byte order.
    while (1) {
        // red
        for (i = 0; i < FRAMESIZE; i += 3) {
            frame[i    ] = 0x00;
            frame[i + 1] = 0x00;
            frame[i + 2] = 0xff;
        }
        vodisp_write_frame(frame);
        sleep(1);

        // green
        for (i = 0; i < FRAMESIZE; i += 3) {
            frame[i    ] = 0x00;
            frame[i + 1] = 0xff;
            frame[i + 2] = 0x00;
        }
        vodisp_write_frame(frame);
        sleep(1);

        // blue
        for (i = 0; i < FRAMESIZE; i += 3) {
            frame[i    ] = 0xff;
            frame[i + 1] = 0x00;
            frame[i + 2] = 0x00;
        }
        vodisp_write_frame(frame);
        sleep(1);

        for (i = 0; i < 256; i += 64) {
            // display gray scale.
            memset(frame, i, FRAMESIZE);
            vodisp_write_frame(frame);
            sleep(1);
        }
    }
}
