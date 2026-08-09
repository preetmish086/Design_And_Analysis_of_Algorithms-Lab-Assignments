#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, value;
    struct Node *next, *prev;
} Node;

Node* head = NULL;
Node* tail = NULL;

Node* createNode(int key, int value)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key; n->value = value; n->next = n->prev = NULL;
    return n;
}

// Insert while keeping the list sorted : O(n) 
void Insert(int key, int value)
{
    Node* n = createNode(key, value);

    if (head == NULL) { 
        head = tail = n; return; }

    if (key < head->key) {                 //new head 
        n->next = head; head->prev = n; head = n;
        return;
    }
    Node* cur = head;
    while (cur->next != NULL && cur->next->key < key) 
        cur = cur->next;

    n->next = cur->next;
    n->prev = cur;
    if (cur->next != NULL) 
        cur->next->prev = n;
    else 
        tail = n;                          // n became the new tail 
    cur->next = n;
}

// Search : O(n) 
Node* Search(int key)
{
    for (Node* cur = head; cur != NULL && cur->key <= key; cur = cur->next)
        if (cur->key == key) return cur;
    return NULL;
}

// Delete: prev/next pointers are already known : O(1) 
void Delete(Node* target)
{
    if (target == NULL) { 
        printf("Item not found!\n"); return; }

    if (target->prev != NULL) 
        target->prev->next = target->next;
    else 
        head = target->next;

    if (target->next != NULL) 
        target->next->prev = target->prev;
    else 
        tail = target->prev;

    free(target);
}

Node* Minimum(void) { return head; }        // O(1) 
Node* Maximum(void) { return tail; }        // O(1), due to the tail pointer 

Node* Predecessor(Node* x) { return x->prev; }  // O(1) once we are at x 
Node* Successor(Node* x)   { return x->next; }  // O(1) once we are at x

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
        printf("\nDictionary Operations: (DOUBLY LINKED - SORTED)\n");
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
}