#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN    1000
#define TABLESIZE 1000

/* one slot in the hash table */
typedef struct Entry {
    char kmer[50];
    int  count;
    struct Entry *next;   /* for handling collisions */
} Entry;

/* the hash table */
Entry *table[TABLESIZE];

/* hash function - converts a string to an index */
int hash(char *str) {
    int h = 0;
    while (*str) {
        h = (h * 31 + *str) % TABLESIZE;
        str++;
    }
    return h;
}
/* search for a kmer in the table */
Entry *search(char *kmer) {
    int idx = hash(kmer);
    Entry *e = table[idx];
    while (e != NULL) {
        if (strcmp(e->kmer, kmer) == 0)
            return e;   /* found it */
        e = e->next;
    }
    return NULL;   /* not found */
}

/* insert or update a kmer in the table */
void insert(char *kmer) {
    Entry *e = search(kmer);
    if (e != NULL) {
        e->count++;   /* kmer exists - increment count */
        return;
    }

    /* kmer not found - create new entry */
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    strcpy(newEntry->kmer, kmer);
    newEntry->count = 1;

    /* insert at front of chain */
    int idx = hash(kmer);
    newEntry->next = table[idx];
    table[idx] = newEntry;
}
int main() {
    char sequence[MAXLEN];
    int k;

    printf("Enter DNA sequence : ");
    scanf("%s", sequence);
    printf("Enter k            : ");
    scanf("%d", &k);
    
    int L = strlen(sequence);
    int totalKmers = L - k + 1;

    printf("\nSequence : %s\n", sequence);
    printf("K        : %d\n", k);
    printf("Total kmers : %d\n\n", totalKmers);
/* initialize table to NULL */
    for (int i = 0; i < TABLESIZE; i++)
        table[i] = NULL;

    /* extract and count all kmers */
    char kmer[50];
    for (int i = 0; i <= L - k; i++) {
        strncpy(kmer, sequence + i, k);
        kmer[k] = '\0';
        insert(kmer);
    }

   /* collect all entries into an array for sorting */
    Entry *entries[TABLESIZE];
    int count = 0;

    for (int i = 0; i < TABLESIZE; i++) {
        Entry *e = table[i];
        while (e != NULL) {
            entries[count++] = e;
            e = e->next;
        }
    }

    /* bubble sort by count descending */
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (entries[j]->count < entries[j+1]->count) {
                Entry *temp = entries[j];
                entries[j] = entries[j+1];
                entries[j+1] = temp;
            }
        }
    }

    /* print sorted results */
    printf("===== Kmer Frequency Table =====\n");
    printf("  %-10s  %s\n", "Kmer", "Count");
    printf("  ----------  -----\n");
    for (int i = 0; i < count; i++)
        printf("  %-10s  %d\n", entries[i]->kmer, entries[i]->count);
    printf("================================\n");
    printf("Unique kmers : %d\n", count);
    printf("Total kmers  : %d\n", totalKmers);
    
    return 0;
}
