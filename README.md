# Kmer Frequency Counter

A C program that counts all kmers of length k in a DNA sequence
using a hash table with chaining for collision resolution.

## What it does
- Extracts all kmers of size k using a sliding window
- Stores kmer counts in a hash table (array of linked lists)
- Handles hash collisions using chaining
- Sorts and displays kmers by frequency (most to least)

## How to compile
gcc kmer_counter.c -o kmer_counter

## How to run
./kmer_counter

## Example
Input    : ATGATGATGATGCCCGGG, k=3
Output   :
Kmer        Count
----------  -----
ATG         4
TGA         3
GAT         3
GGG         1
...

## Concepts used
- Hash tables with chaining in C
- Dynamic memory allocation (malloc)
- Linked lists in C
- Sliding window algorithm
- Bubble sort

## Author
K Vaishali
MSc Bioinformatics
