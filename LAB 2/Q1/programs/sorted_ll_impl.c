#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, value;
    struct Node* next;
} Node;

Node* head = NULL;

Node* createNode(int key, int value)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key; 
    n->value = value; 
    n->next = NULL;
    return n;
}

//Insert while keeping the list sorted : O(n) (find spot + link)
void Insert(int key, int value)
{
    Node* n = createNode(key, value);

    if (head == NULL || key < head->key) {   // becomes new head 
        n->next = head;
        head = n;
        return;
    }
    Node* cur = head;
    while (cur->next != NULL && cur->next->key < key)
        cur = cur->next;

    n->next = cur->next;
    cur->next = n;
}

//Search: walk from head, we could stop early on average, worst case O(n)
Node* Search(int key)
{
    Node* cur = head;
    while (cur != NULL && cur->key <= key) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return NULL;
}

//Delete: still need the node before "target" (singly linked) : O(n)
void Delete(Node* target)
{
    if (target == NULL || head == NULL) { 
        printf("Item not found!\n"); return; }
    if (head == target) { 
        head = head->next; 
        free(target); return; }

    Node* prev = head;
    while (prev->next != NULL && prev->next != target) 
        prev = prev->next;

    if (prev->next == target) { 
        prev->next = target->next; free(target); }
    else printf("Item not found!\n");
}

Node* Minimum(void) { return head; }                 /* O(1): smallest is always the head */

Node* Maximum(void)                                   /* O(n): walk to the last node */
{
    if (head == NULL) return NULL;
    Node* cur = head;
    while (cur->next != NULL) cur = cur->next;
    return cur;
}

// Predecessor: no "prev" pointer exists, so re-traverse from head : O(n) 
Node* Predecessor(Node* x)
{
    if (head == NULL || head == x) return NULL;
    Node* cur = head;
    while (cur->next != NULL && cur->next != x) cur = cur->next;
    return (cur->next == x) ? cur : NULL;
}

// Successor: once we are at x, next is O(1); but reaching x costs O(n)
Node* Successor(Node* x) { return x->next; }

void Display(void)
{
    if (head == NULL) { 
        printf("Dictionary is empty!\n"); return; }
    printf("Dictionary items (sorted):\n");
    for (Node* cur = head; cur != NULL; cur = cur->next)
        printf("Key: %d, Value: %d\n", cur->key, cur->value);
}

int main()
{
    int choice, key, value; Node* ptr;
    while (1) {
        printf("\nDictionary Operations: (SINGLY LINKED - SORTED)\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Predecessor\n");
        printf("5. Successor\n6. Minimum\n7. Maximum\n8. Display\n9. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) return 0;

        switch (choice) {
            case 1:
                printf("Enter key: "); scanf("%d", &key);
                printf("Enter value: "); scanf("%d", &value);
                Insert(key, value);
                break;
            case 2:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(key);
                if (ptr) printf("Found value %d\n", ptr->value); else printf("Not found\n");
                break;
            case 3:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(key);
                if (ptr) Delete(ptr); else printf("Not found\n");
                break;
            case 4:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(key);
                if (ptr) {
                    Node* p = Predecessor(ptr);
                    if (p) printf("Predecessor: %d\n", p->key); else printf("None\n");
                } else printf("Not found\n");
                break;
            case 5:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(key);
                if (ptr) {
                    Node* s = Successor(ptr);
                    if (s) printf("Successor: %d\n", s->key); else printf("None\n");
                } else printf("Not found\n");
                break;
            case 6:
                ptr = Minimum();
                if (ptr) printf("Minimum: %d\n", ptr->key); else printf("Empty!\n");
                break;
            case 7:
                ptr = Maximum();
                if (ptr) printf("Maximum: %d\n", ptr->key); else printf("Empty!\n");
                break;
            case 8: Display(); break;
            case 9: return 0;
            default: printf("Invalid choice!\n");
        }
    }