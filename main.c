#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash-table.c"

int read_int();
char* read_string();
void show_menu_options();
void get_menu_option(int* option);
void handle_menu_options(int option);
void handle_option_create_table();
void handle_option_display_table();
void handle_option_add_item();
void handle_option_get_item();
void handle_option_edit_item();
void handle_option_remove_item();

HashTable* table = NULL;

void main() {
    printf("Estrutura de Dados I\n");
    printf("Implementação de Tabelas Hash\n\n");

    int option;

    while (option != -1)
    {
        system("clear");
        show_menu_options();
        get_menu_option(&option);
        printf("\n");
        handle_menu_options(option);
        if (option != -1) getchar();
    }
}

int read_int() {
    int number;
    scanf("%d", &number);
    getchar();
    return number;
}

char* read_string() {
    char* string = (char*) malloc(100 * sizeof(char));
    scanf("%[^\n]", string);
    getchar();
    return string;
}

char* prompt(const char* prompt) {
    printf("%s", prompt);
    return read_string();
}

void show_menu_options() {
    printf("Menu\n");
    printf("1 - Criar a tabela hash\n");
    printf("2 - Exibir a tabela hash\n");
    printf("3 - Adicionar um novo item a tabela\n");
    printf("4 - Obter um item na tabela\n");
    printf("5 - Alterar um item na tabela\n");
    printf("6 - Remover um item da tabela\n");
    printf("-1 - Encerrar o programa\n");
}

void get_menu_option(int* option) {
    printf("Digite a opção desejada: ");
    *option = read_int();
}

void handle_menu_options(int option) {
    switch (option) {
        case 1:
            handle_option_create_table();
            break;
        case 2:
            handle_option_display_table();
            break;
        case 3:
            handle_option_add_item();
            break;
        case 4:
            handle_option_get_item();
            break;
        case 5:
            handle_option_edit_item();
            break;
        case 6:
            handle_option_remove_item();
            break;
        case -1:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}

void handle_option_create_table() {
    if (table != NULL) {
        printf("A tabela já foi criada\n");
        return;
    }

    printf("Digite o tamanho da tabela: ");
    int size = read_int();

    table = create_hash_table(size);
    printf("Tabela criada com sucesso\n");
}

void handle_option_display_table() {
    if (table == NULL) {
        printf("A tabela ainda não foi criada, utilize a opção 1.\n");
        return;
    }

    print_table(table);
}

void handle_option_add_item() {
    if (table == NULL) {
        printf("A tabela ainda não foi criada, utilize a opção 1.\n");
        return;
    }

    char* document = prompt("Digite o CPF: ");
    char* name = prompt("Digite o nome: ");
    char* phone = prompt("Digite o telefone: ");

    insert_item(table, name, phone, document);
    printf("Item inserido com sucesso\n");
}

void handle_option_get_item() {
    if (table == NULL) {
        printf("A tabela ainda não foi criada, utilize a opção 1.\n");
        return;
    }

    char* document = prompt("Digite o CPF: ");
    Person* person = search_item(table, document);

    print_item(person);
}

void handle_option_edit_item() {
    if (table == NULL) {
        printf("A tabela ainda não foi criada, utilize a opção 1.\n");
        return;
    }

    char* document = prompt("Digite o CPF para localizar o registro: ");
    Person* person = search_item(table, document);

    print_item(person);
    printf("\n");

    char* name = prompt("Digite o novo nome: ");
    char* phone = prompt("Digite o novo telefone: ");

    edit_item(person, name, phone);
    printf("Item alterado com sucesso\n");
}

void handle_option_remove_item() {
    if (table == NULL) {
        printf("A tabela ainda não foi criada, utilize a opção 1.\n");
        return;
    }

    char* document = prompt("Digite o CPF: ");
    remove_item(table, document);
    printf("Item removido com sucesso\n");
}