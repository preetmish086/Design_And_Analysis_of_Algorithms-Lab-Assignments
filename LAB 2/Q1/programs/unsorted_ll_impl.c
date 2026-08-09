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

//Insert at the head : O(1)
void Insert(int key, int value)
{
    Node* n = createNode(key, value);
    n->next = head;
    head = n;
}

//Search: traverse from head until key matches : O(n)
Node* Search(int key)
{
    Node* cur = head;
    while (cur != NULL) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return NULL;
}

// Delete: given a pointer "target" to the node to remove.
// Because there is no "prev" pointer in a singly linked list,
// we must traverse the list from the head to locate the node
// right before "target" so we can re-link around it -> O(n).
void Delete(Node* target)
{
    if (target == NULL || head == NULL) { printf("Item not found!\n"); return; }

    if (head == target) {                 //deleting the head node
        head = head->next;
        free(target);
        return;
    }
    Node* prev = head;
    while (prev->next != NULL && prev->next != target)
        prev = prev->next;

    if (prev->next == target) {
        prev->next = target->next;
        free(target);
    } else {
        printf("Item not found!\n");
    }
}

//Min/Max: unsorted list, must scan all nodes : O(n)
Node* Minimum(void)
{
    if (head == NULL) return NULL;
    Node* min = head;
    for (Node* cur = head->next; cur != NULL; cur = cur->next)
        if (cur->key < min->key) min = cur;
    return min;
}
Node* Maximum(void)
{
    if (head == NULL) return NULL;
    Node* max = head;
    for (Node* cur = head->next; cur != NULL; cur = cur->next)
        if (cur->key > max->key) max = cur;
    return max;
}

//Predecessor/Successor of x's key: unsorted, must scan all nodes : O(n)
Node* Predecessor(Node* x)
{
    Node* pred = NULL;
    for (Node* cur = head; cur != NULL; cur = cur->next)
        if (cur->key < x->key && (pred == NULL || cur->key > pred->key))
            pred = cur;
    return pred;
}
Node* Successor(Node* x)
{
    Node* succ = NULL;
    for (Node* cur = head; cur != NULL; cur = cur->next)
        if (cur->key > x->key && (succ == NULL || cur->key < succ->key))
            succ = cur;
    return succ;
}

void Display(void)
{
    if (head == NULL) { 
        printf("Dictionary is empty!\n"); return; }
    printf("Dictionary items:\n");
    for (Node* cur = head; cur != NULL; cur = cur->next)
        printf("Key: %d, Value: %d\n", cur->key, cur->value);
}

int main()
{
    int choice, key, value;
    Node* ptr;

    while (1) {
        printf("\nDictionary Operations: (SINGLY LINKED - UNSORTED)\n");
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
                if (ptr) printf("Found value %d\n", ptr->value);
                else printf("Key %d not found\n", key);
                break;
            case 3:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(key);
                if (ptr) Delete(ptr); else printf("Key %d not found\n", key);
                break;
            case 4:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(key);
                if (ptr) {
                    Node* p = Predecessor(ptr);
                    if (p) printf("Predecessor: %d\n", p->key); else printf("None\n");
                } else printf("Key %d not found\n", key);
                break;
            case 5:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(key);
                if (ptr) {
                    Node* s = Successor(ptr);
                    if (s) printf("Successor: %d\n", s->key); else printf("None\n");
                } else printf("Key %d not found\n", key);
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