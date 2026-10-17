// Top hashtags
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUTS 10000
#define TAG_LENGTH 64
typedef struct Entry {
    char tag[TAG_LENGTH];
    size_t count;
    int used;
} Entry;
static size_t hashTag(const char *text) {
    size_t hash = (size_t)2166136261u;
    while (*text != '\0') {
        hash ^= (unsigned char)*text++;
        hash *= (size_t)16777619u;
    }
    return hash;
}
static void normalize(char *tag) {
    for (size_t i = 0; tag[i] != '\0'; ++i) tag[i] = (char)tolower((unsigned char)tag[i]);
}
int main(void) {
    unsigned int inputCount;
    size_t n, capacity = 1, unique = 0;
    char tag[TAG_LENGTH];
    printf("Number of hashtag entries (0-%d): ", MAX_INPUTS);
    if (scanf("%u", &inputCount) != 1 || inputCount > MAX_INPUTS) {
        puts("Invalid count.");
        return 1;
    }
    n = inputCount;
    while (capacity < (n == 0 ? 1 : n * 2)) capacity *= 2;
    Entry *table = calloc(capacity, sizeof(*table));
    if (table == NULL) {
        puts("Memory allocation failed.");
        return 1;
    }
    puts("Enter hashtags one at a time (case-insensitive; # prefix is optional):");
    for (size_t i = 0; i < n; ++i) {
        if (scanf("%63s", tag) != 1) {
            free(table);
            return 1;
        }
        normalize(tag);
        size_t slot = hashTag(tag) & (capacity - 1);
        while (table[slot].used && strcmp(table[slot].tag, tag) != 0) {
            slot = (slot + 1) & (capacity - 1);
        }
        if (!table[slot].used) {
            table[slot].used = 1;
            strcpy(table[slot].tag, tag);
            ++unique;
        }
        ++table[slot].count;
    }
    if (unique == 0) {
        puts("No hashtags were entered.");
    } else {
        size_t selected[10], shown = unique < 10 ? unique : 10;
        puts("Top hashtags:");
        for (size_t rank = 0; rank < shown; ++rank) {
            size_t best = capacity;
            for (size_t i = 0; i < capacity; ++i) {
                if (table[i].used) {
                    int already = 0;
                    for (size_t j = 0; j < rank; ++j) {
                        if (selected[j] == i) already = 1;
                    }
                    if (!already && (best == capacity || table[i].count > table[best].count || (table[i].count == table[best].count && strcmp(table[i].tag, table[best].tag) < 0))) {
                        best = i;
                    }
                }
            }
            selected[rank] = best;
            printf("%u. %s - %u occurrence(s)\n", (unsigned int)rank + 1, table[best].tag, (unsigned int)table[best].count);
        }
    }
    free(table);
    return 0;
}
