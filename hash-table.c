#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Person {
    char* name;
    char* phone;
    char* document;
    struct Person* next;
} Person;

typedef struct HashTable {
    Person** items;
    int size;
    int count;
} HashTable;

HashTable* create_hash_table(int size)
{
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));

    table->size = size;
    table->count = 0;
    table->items = (Person**) calloc(table->size, sizeof(Person*));

    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;
}

Person* create_person(char* name, char* phone, char* document)
{
    Person* person = (Person*) malloc(sizeof(Person));
    
    person->name = name;
    person->phone = phone;
    person->document = document;
    person->next = NULL;

    return person;
}

unsigned long calculate_hash(char* key, int tableSize) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % tableSize;
}

void insert_item(HashTable* table, char* name, char* phone, char* document)
{
    Person* person = create_person(name, phone, document);

    unsigned long hash = calculate_hash(document, table->size);

    Person* existingItem = table->items[hash];

    if (existingItem == NULL)
        table->items[hash] = person;
    else {

        while (existingItem->next != NULL) {
            existingItem = existingItem->next;
        }

        existingItem->next = person;
    }

    table->count++;
}

Person* search_item(HashTable* table, char* document)
{
    unsigned long hash = calculate_hash(document, table->size);

    Person* person = table->items[hash];

    while (person != NULL) {
        if (strcmp(person->document, document) == 0) {
            return person;
        }

        person = person->next;
    }

    return NULL;
}

void edit_item(Person* person, char* name, char* phone)
{
    person->name = name;
    person->phone = phone;
}

void remove_item(HashTable* table, char* document)
{
    unsigned long hash = calculate_hash(document, table->size);

    Person* current = table->items[hash];
    Person* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->document, document) == 0) {

            if (previous == NULL)
                table->items[hash] = current->next;
            else
                previous->next = current->next;

            free(current);

            table->count--;

            return;
        }

        previous = current;
        current = current->next;
    }
}

void print_table(HashTable* table)
{
    printf("A tabela possui tamanho %d e contém %d itens.\n", table->size, table->count);
    for (int i = 0; i < table->size; i++) {
        Person* person = table->items[i];

        if (person == NULL) {
            printf("O hash [%d] está vazio.\n", i);
        } else {
            printf("O hash [%d] contém os itens a seguir:\n", i);

            while (person != NULL) {
                printf("\tNome: %s, Telefone: %s, CPF: %s\n", person->name, person->phone, person->document);
                person = person->next;
            }
        }
    }
}

void print_item(Person* person)
{
    if (person == NULL) {
        printf("Pessoa não encontrada.\n");
        return;
    }

    printf("Nome: %s\n", person->name);
    printf("Telefone: %s\n", person->phone);
    printf("CPF: %s\n", person->document);
}