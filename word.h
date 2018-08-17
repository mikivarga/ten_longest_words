#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define MAXLEN 128

typedef struct
{
    ssize_t len_word;
    char *word;
} word_t;

void word_init(word_t arr_word[], size_t arr_size);
void word_show(word_t arr_word[], size_t arr_size, char *p);
void word_add(word_t arr_word[], char *word, ssize_t len_word, size_t arr_size);

#endif