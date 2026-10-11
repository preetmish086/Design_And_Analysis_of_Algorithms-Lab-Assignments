#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left, *right;
} Node;

Node *heap[MAX];
int heapSize = 0;

void swap(Node **a, Node **b) {
    Node *t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent]->freq <= heap[i]->freq)
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

void heapifyDown(int i) {
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heapSize &&
            heap[left]->freq < heap[smallest]->freq)
            smallest = left;

        if (right < heapSize &&
            heap[right]->freq < heap[smallest]->freq)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
}

void insert(Node *node) {
    heap[heapSize] = node;
    heapifyUp(heapSize);
    heapSize++;
}

Node *extractMin() {
    Node *result = heap[0];

    heap[0] = heap[--heapSize];

    if (heapSize > 0)
        heapifyDown(0);

    return result;
}

Node *newNode(char symbol, int freq) {
    Node *node = malloc(sizeof(Node));

    node->symbol = symbol;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

void printCodes(Node *root, char code[], int depth) {
    if (!root->left && !root->right) {
        code[depth] = '\0';

        printf("%c : %s\n", root->symbol, code);
        return;
    }

    if (root->left) {
        code[depth] = '0';
        printCodes(root->left, code, depth + 1);
    }

    if (root->right) {
        code[depth] = '1';
        printCodes(root->right, code, depth + 1);
    }
}

int main() {
    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char symbol;
        int freq;

        printf("Enter symbol and frequency: ");
        scanf(" %c %d", &symbol, &freq);

        insert(newNode(symbol, freq));
    }

    while (heapSize > 1) {
        Node *x = extractMin();
        Node *y = extractMin();

        Node *z = newNode('\0', x->freq + y->freq);

        z->left = x;
        z->right = y;

        insert(z);
    }

    Node *root = extractMin();

    char code[MAX];

    printf("\nHuffman codes:\n");
    printCodes(root, code, 0);

    return 0;
}