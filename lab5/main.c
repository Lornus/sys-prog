#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./layer4.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Two argumentes are expected\n");
        return 1;
    }

    if (strcmp(argv[1], "-t") == 0) {
        layer4_transmit(argv[2]);
    } else if (strcmp(argv[1], "-r") == 0) {
        layer4_receive(argv[2]);
    } else {
        fprintf(stderr, "Unknown flag:\nTry -t for sending and -r for receiving\n");
        return 1;
    }

    return 0;
}
