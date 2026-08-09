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
Item* Search(Dictionary *D, int key);
void Delete(Dictionary* D, Item *x);
Item* Minimum(Dictionary *D);
Item* Maximum(Dictionary* D);
Item* Predecessor(Dictionary* D, Item *x);
Item* Successor(Dictionary* D, Item *x);
void Display(Dictionary *D);

//Search- scans the whole array wfor a matching key : O(n)
Item* Search(Dictionary* D, int key)
{
    for(int i=0; i<D->size; i++)
    {
        if(D->items[i].key==key)
            return &D->items[i];
    }
    return NULL;
}

//Insert- append at the end: O(1)
void Insert(Dictionary* D, Item x)
{
    if(D->size < MAX)
    {
        D->items[D->size] = x;
        D->size++;
    }
    else
    {
        printf("Dictionary is full!\n");
    }
}

//Delete- no need to search again as we have the pointer x pointing to the item we want to delete. overwriting the slot with the last element then shrinking the size by 1: O(1)
void Delete(Dictionary* D, Item* x)
{
    if(x == NULL || D->size==0)
    {
        printf("Item not found!\n");
        return;
    }
    *x = D->items[D->size-1];
    D->size--;
}

//Minimum- must check every element: O(n)
Item* Minimum(Dictionary* D)
{
    if(D->size == 0)
        return NULL;
    Item* min = &D->items[0];
    for(int i=1; i<D->size; i++)
    {
        if(D->items[i].key < min->key)
            min = &D->items[i];
    }
    return min;
}

//Maximum- must check every element: O(n)
Item* Maximum(Dictionary* D)
{
    if(D->size == 0)
        return NULL;
    Item* max = &D->items[0];
    for(int i=1; i<D->size; i++)
    {
        if(D->items[i].key > max->key)
            max = &D->items[i];
    }
    return max;
}

//Predecessor of x is the largest key that is still less than x->key: O(n)
Item* Predecessor(Dictionary* D, Item* x)
{
    Item* pred = NULL;
    for(int i=0; i<D->size; i++)
    {
        if(D->items[i].key < x->key)
        {
            if(pred == NULL || D->items[i].key > pred->key)
                pred = &D->items[i];
        }
    }
    return pred;
}

//Successor of x is the smallesr key that is still greater thsan x->key: O(n)
Item* Successor(Dictionary* D, Item* x)
{
    Item* succ = NULL;
    for(int i=0; i<D->size; i++)
    {
        if(D->items[i].key > x->key)
        {
            if(succ == NULL || D->items[i].key < succ->key)
                succ = &D->items[i];
        }
    }
    return succ;
}

void display(Dictionary* D)
{
    if(D->size == 0)
    {
        printf("Dictionary is empty!\n");
        return;
    }
    printf("Dictionary items:\n");
    for(int i=0; i<D->size; i++)
    {
        printf("Key: %d, Value: %d\n", D->items[i].key, D->items[i].value);
    }
}

int main()
{
    Dictionary D;
    D.size=0;

    int choice, key;

    Item item;
    Item* ptr;

    while(1)
    {
        printf("\nDictionary Operations: (UNSORTED ARRAY)\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Predecessor\n");
        printf("5. Successor\n");
        printf("6. Minimum\n");
        printf("7. Maximum\n");
        printf("8. Display\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &item.key);
                printf("Enter value to insert: ");
                scanf("%d", &item.value);
                Insert(&D, item);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                ptr = Search(&D, key);
                if(ptr == NULL)
                    printf("Key %d not found in the dictionary\n", key);
                else
                    printf("Key %d found with value %d\n", ptr->key, ptr->value);
                break;
                
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                ptr = Search(&D, key);
                if(ptr != NULL)
                    Delete(&D, ptr);
                else 
                    printf("Key %d not found\n", key);
                break;
                
            case 4:
                printf("Enter key to find predecessor: ");
                scanf("%d", &key);
                ptr = Search(&D, key);
                if(ptr != NULL)
                {
                    Item* pred = Predecessor(&D, ptr);
                    if(pred)
                        printf("Predecessor of key %d is %d with value %d\n", ptr->key, pred->key, pred->value);
                    else
                        printf("No predecessor found for key %d\n", ptr->key);
                }
                else
                    printf("Key %d not found in the dictionary\n", key);
                break;

            case 5:
                printf("Enter key to find successor: ");
                scanf("%d", &key);
                ptr = Search(&D, key);
                if(ptr != NULL)
                {
                    Item* succ = Successor(&D, ptr);
                    if(succ != NULL)
                        printf("Successor of key %d is %d with value %d\n", ptr->key, succ->key, succ->value);
                    else
                        printf("No successor found for key %d\n", ptr->key);
                }
                else
                    printf("Key %d not found in the dictionary\n", key);
                break;
                
            case 6:
                ptr = Minimum(&D);
                if(ptr != NULL)
                    printf("Minimum key is %d with value %d\n", ptr->key, ptr->value);
                else
                    printf("Dictionary is empty!\n");
                break;
                
            case 7:
                ptr = Maximum(&D);
                if(ptr != NULL)
                    printf("Maximum key is %d with value %d\n", ptr->key, ptr->value);
                else
                    printf("Dictionary is empty!\n");
                break;
                
            case 8:
                display(&D);
                break;
                
            case 9:
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}