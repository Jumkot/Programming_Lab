#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coder.h"
#include "command.h"

void print_usage(char* argv[]);

int main(int argc, char* argv[])
{
    if (argc != 4)
        print_usage(argv);

    if ((strcmp(argv[1], "encode") == 0)) {
        if (encode_file(argv[2], argv[3]) == -1) {
            printf("Ошибка: невозможно кодировать %s в %s\n", argv[2], argv[3]);
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[1], "decode") == 0) {
        if (decode_file(argv[2], argv[3]) == -1) {
            printf("Ошибка: невозможно декодировать %s в %s\n", argv[2], argv[3]);
            exit(EXIT_FAILURE);
        }
    } else {
        print_usage(argv);
    }

    return 0;
}

void print_usage(char* argv[])
{
    fprintf("Usage:\n");
    fprintf("%s encode <in-file-name> <out-file-name>\n", argv[0]);
    fprintf("%s decode <in-file-name> <out-file-name>\n", argv[0]);
    exit(EXIT_FAILURE);
}