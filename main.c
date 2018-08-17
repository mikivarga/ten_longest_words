#include "word.h"

#define LEN_ARR 10

void longest_words(char *p, size_t file_size)
{
    word_t arr_word[LEN_ARR];

    for(int i = 0; i < 1000; i++)
    {
        char *current_word = p, *word_boundary = NULL;
        word_init(arr_word, LEN_ARR);

        while (current_word < p + file_size) {
            size_t word_len;

            word_boundary = strchr(current_word, '\n');
            word_len = (word_boundary) ? 
                word_boundary - current_word :
                p + file_size + 1 - current_word;

            word_add(arr_word, current_word, word_len, LEN_ARR);
            current_word += word_len + 1;
        }
    }
    word_show(arr_word, LEN_ARR, p);
}

int main(void)
{
    const char file[] = "/usr/share/dict/american-english";
    struct stat sb;
    char *p;
    int fd;
    
    fd = open(file, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        return 1;
    }
    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "%s is not a file\n", file);
    }
    p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    longest_words(p, sb.st_size);
    if (munmap(p, sb.st_size) == -1)
    {
        perror("munmap");
        return 1;
    }
    return 0;
}