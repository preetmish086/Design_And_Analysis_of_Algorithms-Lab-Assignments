#include <stdio.h>
#include <string.h>

#define ALPHA 26
#define MAX 1000

typedef struct {
    char ch;
    int freq;
} Node;

Node heap[ALPHA];
int heapSize = 0;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(Node x) {
    int i = heapSize++;
    heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (heap[p].freq >= heap[i].freq)
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

Node extractMax() {
    Node result = heap[0];

    heap[0] = heap[--heapSize];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;

        if (l < heapSize &&
            heap[l].freq > heap[largest].freq)
            largest = l;

        if (r < heapSize &&
            heap[r].freq > heap[largest].freq)
            largest = r;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return result;
}

typedef struct {
    Node node;
    int availableAt;
} Cooldown;

int main() {
    char s[MAX];
    int K;

    printf("Enter string: ");
    scanf("%s", s);

    printf("Enter K: ");
    scanf("%d", &K);

    int freq[ALPHA] = {0};

    for (int i = 0; s[i]; i++)
        freq[s[i] - 'a']++;

    for (int i = 0; i < ALPHA; i++) {
        if (freq[i] > 0) {
            Node x = {'a' + i, freq[i]};
            insert(x);
        }
    }

    Cooldown queue[ALPHA];
    int front = 0, rear = 0;

    char result[MAX];
    int len = 0;

    while (len < strlen(s)) {

        /* Release characters */
        if (front < rear &&
            queue[front].availableAt <= len) {

            insert(queue[front].node);
            front++;
        }

        if (heapSize == 0) {
            printf("Impossible to reorganise.\n");
            return 0;
        }

        Node current = extractMax();

        result[len++] = current.ch;

        current.freq--;

        if (current.freq > 0) {
            queue[rear].node = current;
            queue[rear].availableAt = len + K - 1;
            rear++;
        }
    }

    result[len] = '\0';

    printf("Reorganised string = %s\n", result);

    return 0;
}