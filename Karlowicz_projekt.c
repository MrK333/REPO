#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int choice, condition = 1;
float VAT = 0.23;
int n = 0;

typedef struct contractor{
    char name[30];
    char NIP[12];
    char account_number[26];
}contractor;

typedef struct product{
    char* name;
    int amount;
    float price_netto;
    float value_netto;
}product;

typedef struct DATA{
    char* name;
    char* NIP;
    char* account_number;
    char* invoice_number;
    char* date;
    char* payment_method;
    char* payment_date;
    float invoice_value;
    float summary_vat_value;
    float summary_netto_value;
    product sold_position[3];
}Data;

typedef struct LIST invoice;
struct LIST{
    Data data;
    invoice* next;
};

invoice* add_element(){
   	invoice *element;
	char bufor[30 + 1];
	char *name, *NIP, *account_number, *invoice_number, *payment_method, *payment_date, *invoice_date, *product_name;
	int amount;
	float price_netto, value_netto, summary_netto_value, summary_vat_value, invoice_value;
	element = (invoice*)malloc(sizeof(invoice));
	system("cls");
	printf("Wprowadz nazwe klienta: ");
	gets(bufor);
	gets(bufor);
	name = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(name, bufor);

	printf("Wprowadz NIP: ");
	gets(bufor);
	NIP = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(NIP, bufor);

	printf("Wprowadz nr faktury: ");
	gets(bufor);
	invoice_number = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(invoice_number, bufor);

	printf("Wprowadz date: ");
	gets(bufor);
	invoice_date = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(invoice_date, bufor);

    printf("Wprowadz date platnosci: ");
	gets(bufor);
	payment_date = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(payment_date, bufor);


	printf("Podaj ilosc pozycji, ktore chcesz dodac: ");
	scanf("%d", &n);
    while(n > 3){
    printf("Za duzo pozycji. Podaj liczbe niewieksza niz 3: ");
    scanf("%d", &n);
    }
        for(int i = 0; i<n; i++){
        printf("Wprowadz nazwe produktu: ");
        //if(i != 0) gets(bufor);
        gets(bufor);
        gets(bufor);
        product_name = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
        strcpy(product_name, bufor);
        element->data.sold_position[i].name = product_name;

        printf("Wprowadz ilosc produktow: ");
        scanf("%d", &amount);
        element->data.sold_position[i].amount = amount;

        printf("Wprowadz jednostkowa cene netto produktu: ");
        scanf("%f", &price_netto);
        element->data.sold_position[i].price_netto = price_netto;
        element->data.sold_position[i].value_netto = element->data.sold_position[i].price_netto * element->data.sold_position[i].amount;
        element->data.summary_netto_value += element->data.sold_position[i].value_netto;
        }

    element->data.summary_vat_value = element->data.summary_netto_value * VAT;
    element->data.invoice_value = element->data.summary_vat_value + element->data.summary_netto_value;
	element->data.payment_method = payment_method;
	element->next = NULL;
	element->data.name = name;
	element->data.NIP = NIP;
	element->data.account_number = account_number;
	element->data.invoice_number = invoice_number;
	element->data.date = invoice_date;
	element->data.payment_date = invoice_date;

	return element;
}

invoice* search_element(invoice *head, char *invoice_number){
	invoice *help;
	help = head;
	while (help != NULL && strcmp(help->data.invoice_number, invoice_number != 0))
		help = help->next;

	return help;
}

void add_first(invoice **head){
	invoice *tmp = add_element();
	if (*head != NULL)
		tmp->next = *head;
	*head = tmp;
}

void save_to_file(invoice *head, contractor *set1){
char bufor[30 + 1];
    FILE *in, *settings;
    settings = fopen("settings.db", "rt");
    invoice *tmp;
        in = fopen("invoices.db", "a+t");
		    tmp = head;
			while (tmp != NULL)
			{
				fprintf(in, "\n\nNr faktury: %s\n", tmp->data.invoice_number);

		/*		fscanf(settings, "%s", bufor);
                set1->name=(char*)malloc(sizeof(char)* (strlen(bufor) + 1));
                strcpy(set1->name, bufor); */

				fprintf(in, "Sprzedawca: %s\n", set1->name);
				fprintf(in, "NIP: %s\n", set1->NIP);
				fprintf(in, "Nr konta: %s\n", set1->account_number);
				fprintf(in, "\nNabywca: %s\n", tmp->data.name);
				fprintf(in, "NIP: %s\n", tmp->data.NIP);
				fprintf(in, "\nData wystawienia: %s\n", tmp->data.date);
				fprintf(in, "Metoda platnosci: przelew\n");
				fprintf(in, "Data platnosci: %s\n", tmp->data.payment_date);

				for(int i = 0; i < n; i++){
                    if(tmp->data.sold_position[i].amount != NULL)
                fprintf(in, "\nNazwa produktu: %s\n", tmp->data.sold_position[i].name);
                fprintf(in, "Ilosc: %d\n", tmp->data.sold_position[i].amount);
                fprintf(in, "Jednostkowa cena netto: %.2fPLN\n", tmp->data.sold_position[i].price_netto);
                fprintf(in, "Wartosc netto: %.2fPLN\n", tmp->data.sold_position[i].value_netto);
				}
                fprintf(in, "\nSumaryczna wartosc netto: %.2fPLN\n", tmp->data.summary_netto_value);
				fprintf(in, "Stawka VAT 23%\n");
				fprintf(in, "Sumaryczna wartosc VAT: %.2fPLN\n", tmp->data.summary_vat_value);
				fprintf(in, "\nRazem brutto: %.2fPLN\n", tmp->data.invoice_value);
				tmp = tmp->next;
			}
    printf("Lista zostala zapisana");
    fclose(in);
    fclose(settings);
}


void read_from_file(invoice **head){
	FILE *read = NULL;
	char bufor[30 + 1];
	invoice *tmp, *help;

	read = fopen("invoices.db", "rt");
	if (read == NULL)
		printf("Blad otwarcia pliku");
	else
	{
		while (fscanf(read, "%s", bufor) != EOF)
		{
			//alokowanie pamieci na nowy element
			tmp = (invoice*)malloc(sizeof(invoice));
			tmp->next = NULL;

            fscanf(read, "%s", bufor);
			tmp->data.invoice_number = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->data.invoice_number, bufor);

			fscanf(read, "%s", bufor);
			tmp->data.name = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->data.name, bufor);

			fscanf(read, "%s", bufor);
			tmp->data.NIP = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->data.NIP, bufor);

			fscanf(read, "%s", bufor);
			tmp->data.account_number = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->data.account_number, bufor);

			fscanf(read, "%s", bufor);
			tmp->data.date = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->data.date, bufor);

			fscanf(read, "%s", bufor);
			tmp->data.payment_date = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
			strcpy(tmp->data.payment_date, bufor);

			if (*head == NULL)
				*head = tmp;
			else
			{
				help = *head;
				while (help->next != NULL)
					help = help->next;
				help->next = tmp;
			}
		}
		printf("Plik zostal wczytany");
	}
	fclose(read);
}

void show_list(invoice *head, contractor *set1){
	invoice *tmp;
    system("cls");
	tmp = head;
	if (tmp == NULL)
		printf("Brak faktur do wyswietlenia\n");
	else
	{
		while (tmp != NULL)
		{
			printf("\n\nNr faktury: %s\n", tmp->data.invoice_number);
            printf("Sprzedawca: %s\n", set1->name);
            printf("NIP: %s\n", set1->NIP);
            printf("Nr konta: %s\n", set1->account_number);
            printf("\nNabywca: %s\n", tmp->data.name);
            printf("NIP: %s\n", tmp->data.NIP);
            printf("\nData wystawienia: %s\n", tmp->data.date);
            printf("Metoda platnosci: przelew\n");
            printf("Data platnosci: %s\n", tmp->data.payment_date);

				for(int i = 0; i < n; i++){
                    if(tmp->data.sold_position[i].amount != NULL)
            printf("\nNazwa produktu: %s\n", tmp->data.sold_position[i].name);
            printf("Ilosc: %d\n", tmp->data.sold_position[i].amount);
            printf("Jednostkowa cena netto: %f\n", tmp->data.sold_position[i].price_netto);
            printf("Wartosc netto: %f\n", tmp->data.sold_position[i].value_netto);
				}
			tmp = tmp->next;
		}
	}
	getchar();
}

void delete_element(invoice **head){
	invoice *tmp, *help;
	char *invoice_number;
	char bufor[30 + 1];

	system("cls");
	printf("Podaj nr faktury: ");
	gets(bufor);
	invoice_number = (char*)malloc(sizeof(char)* (strlen(bufor) + 1));
	strcpy(invoice_number, bufor);

	tmp = search_element(*head, invoice_number);
	if (tmp == NULL)
		printf("Nie ma takiej faktury");
	else
	{
		if (tmp == *head) free(tmp);
		else
		{
			help = *head;
			while ((strcmp(help->next->data.invoice_number, tmp->data.invoice_number) != 0))
				help = help->next;
			help->next = tmp->next;
			if (tmp->data.name)
				free(tmp->data.name);
			if (tmp->data.NIP)
				free(tmp->data.NIP);
            if (tmp->data.account_number)
                free(tmp->data.account_number);
            if (tmp->data.invoice_number)
				free(tmp->data.invoice_number);
            if (tmp->data.date)
				free(tmp->data.date);
			if (tmp->data.payment_method)
				free(tmp->data.payment_method);
		/*	if (tmp->data.payment_date)
				free(tmp->payment_date);
			if (tmp->data.sold_position[])
                free(tmp->data.sold_position[]); */
			free(tmp);
		}
	}
}

void delete_all(){
    FILE *in;
    in = fopen("invoices.db", "wt");
    fclose(in);
    printf("Pomyslnie usunieto wszystkie faktury\n");
}

void save_settings(contractor *set1){
	FILE *settings;
    settings = fopen("settings.db", "wt");

    system("cls");
    printf("Podaj nazwe firmy: ");
    fgets(set1->name, 30+1, stdin);
    fgets(set1->name, 30+1, stdin);
    printf("Podaj NIP: ");
    fgets(set1->NIP, 12+1, stdin);
    printf("Podaj nr konta: ");
    fgets(set1->account_number, 26+1, stdin);
    //fgets(set1->account_number, 26+1, stdin);

    fprintf(settings, "%s", set1->name);
    fprintf(settings, "%s", set1->NIP);
    fprintf(settings, "%s", set1->account_number);

    fclose(settings);
}

void menu(invoice *head, contractor *set1){
    do{
        system("cls");
        printf("1--> Dodaj lub edytuj swoje dane\n");
        printf("2--> Wystaw fakture\n");
        printf("3--> Wyswietl liste faktur z biezacej sesji programu\n");
        printf("4--> Usun wszystkie zapisane faktury\n");
        printf("5--> Zakoncz program i zapisz sesje\n");
        printf("\nWybierz opcje: ");

        scanf("%d", &choice);
        switch(choice){
        case 1: save_settings(set1);
                system("pause");
                break;
        case 2: add_first(&head);
                system("pause");
                break;
        case 3: show_list(head, set1);
                system("pause");
                break;
     /* case 6: printf("Podaj nr faktury");
                char invoice_number[30];
                gets(invoice_number);
                read_from_file(invoice_number);
                gets(invoice_number);
                search_element(head, invoice_number);
                system("pause");
                break; */
     /* case 7: delete_element(&head);
                system("pause");
                break; */
        case 4: delete_all();
                system("pause");
                break;
        case 5: save_to_file(head, set1);
                condition = 0;
                break;
        case 10: read_from_file(head);
        break;
        default:
                while((choice = getchar()) != '\n' && choice != EOF);
                printf("Nie wybrano zadnej opcji\n");
                system("pause");
                continue;
        }
    }while(condition);
}

int main(){
    system("color 70");
    contractor *set1;
    set1 = (contractor*)malloc(sizeof(contractor));
    invoice *head = NULL;
    menu(head, set1);
    free(set1);

    return 0;
}

