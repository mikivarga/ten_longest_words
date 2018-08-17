#include "word.h"

void word_init(word_t arr_word[], size_t arr_size)
{
    while (arr_size)
        arr_word[--arr_size].len_word = 0;
}

void word_show(word_t arr_word[], size_t arr_size, char *p)
{
    size_t i;

    for (i = 0; i < arr_size && arr_word[i].len_word; i++)
        printf("%.*s\n", (int)arr_word[i].len_word, arr_word[i].word);
}

static inline void save_word(word_t *index_arr, char word[], size_t len_word)
{
    index_arr->len_word = len_word;
    index_arr->word = word;
}

static size_t free_index(word_t arr_word[], size_t arr_size, size_t len_word)
{
    size_t i;

    for (i = 1; arr_word[i].len_word <= len_word && i < arr_size; i++)
        arr_word[i - 1] = arr_word[i];

    return --i;
}

static int cmpword(const void *p1, const void *p2)
{
    return (((word_t *)p1)->len_word > ((word_t *)p2)->len_word);
}

void word_add(word_t arr_word[], char *word, ssize_t len_word, size_t arr_size)
{
    static size_t arr_index = 0;

    if (arr_index < arr_size) {
        save_word(&arr_word[arr_index++], word, len_word);
        if (arr_index == arr_size)
            qsort(arr_word, arr_size, sizeof(word_t), cmpword);
    } else {
        size_t free_place_index;

        if (arr_word[0].len_word > len_word)
            return;

        free_place_index = free_index(arr_word, arr_size, len_word);
        save_word(&arr_word[free_place_index], word, len_word);      
    }
}