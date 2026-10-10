#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAXCODE 256

typedef struct Node {
    char ch;
    int freq, minChar;
    struct Node *left, *right;
} Node;

typedef struct {
    char ch;
    int len;
} Code;

Node *newNode(char ch, int freq, int minChar,
              Node *left, Node *right) {
    Node *p = malloc(sizeof(Node));
    if (!p) exit(1);
    p->ch = ch;
    p->freq = freq;
    p->minChar = minChar;
    p->left = left;
    p->right = right;
    return p;
}

int less(Node *a, Node *b) {
    if (a->freq != b->freq)
        return a->freq < b->freq;
    return a->minChar < b->minChar;
}

void lengths(Node *p, int depth, Code codes[], int *n) {
    if (!p->left && !p->right) {
        codes[*n].ch = p->ch;
        codes[*n].len = depth ? depth : 1;
        (*n)++;
        return;
    }
    lengths(p->left, depth + 1, codes, n);
    lengths(p->right, depth + 1, codes, n);
}

void sortCodes(Code a[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[j].len < a[i].len ||
               (a[j].len == a[i].len && a[j].ch < a[i].ch)) {
                Code t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
}

void increment(char s[]) {
    int i = (int)strlen(s) - 1;
    while (i >= 0 && s[i] == '1')
        s[i--] = '0';
    if (i >= 0)
        s[i] = '1';
}

int main(void) {
    Node *heap[MAX];
    Code codes[MAX];
    int n, count = 0;

    printf("Enter number of symbols (1-%d): ", MAX);
    scanf("%d", &n);
    if (n < 1 || n > MAX) return 1;

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        printf("Enter character and frequency: ");
        scanf(" %c %d", &ch, &freq);
        if (freq <= 0) return 1;
        heap[count++] = newNode(ch, freq,
                                (unsigned char)ch, NULL, NULL);
    }

    while (count > 1) {
        int x = 0, y = 1;
        if (less(heap[y], heap[x])) {
            int t = x; x = y; y = t;
        }

        for (int i = 2; i < count; i++) {
            if (less(heap[i], heap[x])) {
                y = x;
                x = i;
            } else if (less(heap[i], heap[y])) {
                y = i;
            }
        }

        Node *left = heap[x], *right = heap[y];
        Node *parent = newNode(
            '\0', left->freq + right->freq,
            left->minChar < right->minChar ?
            left->minChar : right->minChar,
            left, right);

        if (x > y) { int t = x; x = y; y = t; }
        heap[y] = heap[count - 1];
        count--;
        heap[x] = heap[count - 1];
        count--;
        heap[count++] = parent;
    }

    lengths(heap[0], 0, codes, &n);
    sortCodes(codes, n);

    char code[MAXCODE] = "0";
    int previous = codes[0].len;

    printf("\nCanonical Huffman Codebook:\n");
    printf("%c : %s\n", codes[0].ch, code);

    for (int i = 1; i < n; i++) {
        increment(code);
        int len = (int)strlen(code);
        while (len < codes[i].len) {
            code[len++] = '0';
            code[len] = '\0';
        }
        previous = codes[i].len;
        printf("%c : %s\n", codes[i].ch, code);
    }

    return 0;
}
