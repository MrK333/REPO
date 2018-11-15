#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

typedef struct list {
    struct list *next;
    int value;
} list;

list *head;
int check = 0;

void push(int number) 
{
    list *new_element = (list *) malloc(sizeof(list));
    list *temp = NULL;
    new_element -> next = NULL;
    new_element -> value = number;
    if (!head)
    {
        head = new_element;
        return;
    }
    else
    {
        temp = head;
        while(temp -> next)
        { temp = temp -> next; }
        temp -> next = new_element;
    }
}

void clean() 
{
    list *temp;
    while(head != NULL){
        temp = head;
        head = (head) -> next;
        free(temp);
    }
}

void pop() 
{
    if (head != NULL) {
        list *help = head;
        list *help_2 = head -> next;
        
        while (help != NULL) {
            if (help_2 == NULL) {
                check = 1;
                break;
            }
            if (help_2 -> next == NULL) {
                free(help_2);
                help->next = NULL;
            }
            help = help -> next;
            help_2 = help_2 -> next;
        }
    } else printf("Lista jest pusta");
}

void peek() 
{
    list *temp = NULL;
    temp = head;
    if (!head)
    {
        printf("Lista jest pusta");
    } else {
        while (temp -> next)
        { temp = temp -> next; }
        printf("%d", temp -> value);
    }
}

void print() {
    if (!head)
    {
        printf("Lista jest pusta");
    } else {
        list *temp = head;
        while (temp) {
            printf("%d ", temp -> value);
            temp = temp -> next;
        }
    }
}

int main() 
{
    time_t t;
    srand((unsigned) time(&t));
    int n = 10;
    int a = 0;
    for (int i = 0; i < n; i++) {
        a = rand() % 24 + 1;
        push(a);
    }

    int x = 1;
    int choice;
    int elem;
    while (x) {
        check=0;
        system("cls");
        printf("Lista:\n");
        printf("1. Dodaj element\n2. Zdejmij ostatni element\n3. Wyswietl ostatni element\n4. Wyczysc liste\n5. Zakoncz program\n");
        scanf("%d", &choice);
        switch(choice) 
        {
            case 1:
                printf("Podaj element, ktory chcesz dodac: ");
                scanf("%d", &elem);
                push(elem);
                break;
            case 2:
                pop();
                if (check == 1) { clean(); }
                break;
            case 3:
                printf("Ostatni element: ");
                peek();
                printf("\nNacisnij dowolny klawisz\n");
                getch();
                break;
            case 4:
                clean();
                break;
            case 5:
                x = 0;
                break;
            default:
                printf("Nie ma takiej opcji\nNacisnij dowolny klawisz");
                getch();
                break;
        }
    }
    
    return 0;
}