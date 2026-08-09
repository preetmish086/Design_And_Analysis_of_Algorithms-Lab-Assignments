#include <stdio.h>

#define MAX 100

typedef struct {
    int key;
    int value;
} Item;

typedef struct {
    Item items[MAX];
    int size;
} Dictionary;

//function prototypes
void Insert(Dictionary* D, Item x);
int  BinarySearchIndex(Dictionary* D, int key); //returns index or -1
Item* Search(Dictionary* D, int key);
void Delete(Dictionary* D, Item* x);
Item* Minimum(Dictionary* D);
Item* Maximum(Dictionary* D);
Item* Predecessor(Dictionary* D, Item* x);
Item* Successor(Dictionary* D, Item* x);
void Display(Dictionary* D);

// Standard binary search, returns the index of the key, or -1 : O(log n)
int BinarySearchIndex(Dictionary* D, int key)
{
    int low = 0, high = D->size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (D->items[mid].key == key) return mid;
        else if (D->items[mid].key < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

Item* Search(Dictionary* D, int key)
{
    int idx = BinarySearchIndex(D, key);
    return (idx == -1) ? NULL : &D->items[idx];
}

//Insert while keeping the array sorted : O(n) because of the shift
void Insert(Dictionary* D, Item x)
{
    if (D->size >= MAX) { printf("Dictionary is full!\n"); return; }

    //find the position where x should go
    int pos = 0;
    while (pos < D->size && D->items[pos].key < x.key) pos++;

    //shift everything from pos onward, one step to the right
    for (int i = D->size; i > pos; i--)
        D->items[i] = D->items[i - 1];

    D->items[pos] = x;
    D->size++;
}

//Delete: x points inside the array. Shift the tail left to close the gap : O(n)
void Delete(Dictionary* D, Item* x)
{
    if (x == NULL || D->size == 0) 
    { 
        printf("Item not found!\n"); 
        return; 
    }
    int pos = x - D->items;              //pointer arithmetic gives the index, O(1)
    for (int i = pos; i < D->size - 1; i++)
        D->items[i] = D->items[i + 1];
    D->size--;
}

Item* Minimum(Dictionary* D) { 
    return (D->size == 0) ? NULL : &D->items[0]; 
}

Item* Maximum(Dictionary* D) { 
    return (D->size == 0) ? NULL : &D->items[D->size - 1]; 
}

//Because the array is sorted, once we know x's index, pred/succ are O(1)
Item* Predecessor(Dictionary* D, Item* x)
{
    int pos = x - D->items;
    return (pos <= 0) ? NULL : &D->items[pos - 1];
}
Item* Successor(Dictionary* D, Item* x)
{
    int pos = x - D->items;
    return (pos >= D->size - 1) ? NULL : &D->items[pos + 1];
}

void Display(Dictionary* D)
{
    if (D->size == 0) { 
        printf("Dictionary is empty!\n"); 
        return; }
    printf("Dictionary items (sorted):\n");
    for (int i = 0; i < D->size; i++)
        printf("Key: %d, Value: %d\n", D->items[i].key, D->items[i].value);
}

int main()
{
    Dictionary D; D.size = 0;
    int choice, key; Item item, *ptr;

    while (1) {
        printf("\nDictionary Operations: (SORTED ARRAY)\n");
        printf("1. Insert\n2. Search\n3. Delete\n4. Predecessor\n");
        printf("5. Successor\n6. Minimum\n7. Maximum\n8. Display\n9. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) return 0;

        switch (choice) {
            case 1:
                printf("Enter key: "); scanf("%d", &item.key);
                printf("Enter value: "); scanf("%d", &item.value);
                Insert(&D, item);
                break;
            case 2:
                printf("Enter key to search: "); scanf("%d", &key);
                ptr = Search(&D, key);
                if (ptr) printf("Found: value %d\n", ptr->value);
                else printf("Key %d not found\n", key);
                break;
            case 3:
                printf("Enter key to delete: "); scanf("%d", &key);
                ptr = Search(&D, key);
                if (ptr) Delete(&D, ptr); else printf("Key %d not found\n", key);
                break;
            case 4:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(&D, key);
                if (ptr) {
                    Item* p = Predecessor(&D, ptr);
                    if (p) printf("Predecessor: %d\n", p->key); else printf("None\n");
                } else printf("Key %d not found\n", key);
                break;
            case 5:
                printf("Enter key: "); scanf("%d", &key);
                ptr = Search(&D, key);
                if (ptr) {
                    Item* s = Successor(&D, ptr);
                    if (s) printf("Successor: %d\n", s->key); else printf("None\n");
                } else printf("Key %d not found\n", key);
                break;
            case 6:
                ptr = Minimum(&D);
                if (ptr) printf("Minimum: %d\n", ptr->key); else printf("Empty!\n");
                break;
            case 7:
                ptr = Maximum(&D);
                if (ptr) printf("Maximum: %d\n", ptr->key); else printf("Empty!\n");
                break;
            case 8: Display(&D); break;
            case 9: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}