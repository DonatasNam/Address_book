#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedlist.h"

struct Address *create_node(char *name, char *surname, char *phone, char *email)
{
    struct Address *node = NULL;
    node = (struct Address *) malloc(sizeof(struct Address));
    if (node == NULL) {
        return node;
    }
    strcpy(node->name, name);
    strcpy(node->surname, surname);
    strcpy(node->phone, phone);
    strcpy(node->email, email);
    node->next = NULL;
    return node;
}

void add_to_list(struct Address **list, struct Address *person)
{
    struct Address* temp = *list;
    if (temp == NULL) {
        *list = person;
        return; 
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = person;
}

void print_list(struct Address *list)
{
    int count=0;
    struct Address *temp = list;
    while (temp != NULL) {
        count++;
        printf("Ln: %d ",count);
        print_node(temp);
        temp = temp->next;
    }
}

void print_node(struct Address *node)
{
    printf("%s %s %s %s\n", node->name, node->surname, node->phone, node->email);
}

void delete_list(struct Address **list) 
{
    struct Address *to_delete = *list;
    while (*list != NULL) {
        *list = to_delete->next;
        free(to_delete);
        to_delete = *list;
    }
    *list = NULL;
}

char* read_input(){
    char *input = malloc(200);
    if(input == NULL){return input;}
    fgets(input,199,stdin);
    return input;
}

void addr_from_input(struct Address **list){
    struct Address **add = list;
    char* input= read_input();
    char n[50], s[50], p[50], e[50];
    sscanf(input,"%s %s %s %s",n,s,p,e);
    struct Address *addr= create_node(n,s,p,e);
    add_to_list(add, addr);
    free(input);
}

void load_addresses(FILE *file, struct Address **list)
{   char n[50], s[50], p[50], e[50];
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        if(strcmp(line, "\n") == 0) {
            exit(1);
        }
        sscanf(line,"%s %s %s %s",n,s,p,e);
        struct Address *person = create_node(n,s,p,e);
        if (person != NULL) {
            add_to_list(list, person);
        }
    }
}

void search_by_data(struct Address *list)
{
    struct Address *temp = list;
    printf("Input user data: ");
    char* put= read_input();
    char n[50];
    sscanf(put,"%s",n);
    while (temp != NULL) {
        if(strncmp(n, temp->name,strlen(temp->name))==0){
            print_node(temp);
            break;
        }else if(strncmp(n, temp->surname,strlen(temp->surname))==0){
            print_node(temp);
            break;
        }else if(strncmp(n, temp->phone,strlen(temp->phone))==0){
            print_node(temp);
            break;
        }else if(strncmp(n, temp->email,strlen(temp->email))==0){
            print_node(temp);
            break;
        }
        temp = temp->next;

    }
    
    return;
    free(put);
}

void search_by_number(struct Address *list)
{
    struct Address *temp = list;
    int input;
    int count =0;
    printf("\n Input a number: ");
    scanf("%d", &input);
    while (temp != NULL) {
        count++;
        if (input == count){
            printf("Ln: %d ", count);
            print_node(temp);
            break;
        }
        temp = temp->next;
    }
    return;
}

void search(struct Address *list)
{
    char i[50];
    struct Address *tem = list;
    char* in= read_input();
    sscanf(in,"%s",i);
    if(strncmp(i, "number", 5) == 0){
        search_by_number(tem);
        return;
    }
    if(strncmp(i, "data", 5) == 0) {
        search_by_data(tem);
        return;
    }
    free(in);
    return;
}

void insert_node(struct Address *list, struct Address *person){
    struct Address *temp = list; 
    
    person->next= temp->next;       
    temp->next= person;
    return;

}

void insert(struct Address **list){
    struct Address *temp = *list;
    char* input= read_input();
    char n[50], s[50], p[50], e[50];
    sscanf(input,"%s %s %s %s",n,s,p,e);
    struct Address *addr= create_node(n,s,p,e);
    printf("after who?(type any credentials): ");
    char* put= read_input();
    char h[50];
    sscanf(put,"%s",h);
    while (temp != NULL) {
        if(strncmp(h, temp->name,strlen(temp->name))==0){
            insert_node(temp,addr);
            break;
        }else if(strncmp(h, temp->surname,strlen(temp->surname))==0){
            insert_node(temp,addr);
            break;
        }else if(strncmp(h, temp->phone,strlen(temp->phone))==0){
            insert_node(temp,addr);
            break;
        }else if(strncmp(h, temp->email,strlen(temp->email))==0){
            insert_node(temp,addr);
            break;
        }
        temp = temp->next;

    }
   
    free(put);
    free(input);
    return;
    
}

void delete_node(struct Address *list)
{
    struct Address *temp = list;

    temp->next = temp->next->next;

    
}

void delete_first_node(struct Address **list)
{
    struct Address *first = *list;
    *list = first->next;
    free(first);
    first = *list;
    return;
}

void delete_selected(struct Address *list)
{
    struct Address *temp = list;
    int input;
    int count =0;
    scanf("%d", &input);
    while (temp != NULL) {
        count++;
        if (input == 1){
            printf("\n to delete first line type 'rmfirst'\n");
            return;
        } else if (input-1 == count){
            delete_node(temp);
            return;
        }
        temp = temp->next;
    }
    return;
}

void help() 
{
    printf("\n Commands: \n");
    printf("exit program ------------------quit\n");
    printf("get information from file -----load\n");
    printf("add more contacts --------------add\n");
    printf("insert a contact ------------insert\n");
    printf("display list -----------------print\n");
    printf("search list -----------------search\n");
    printf("delete an entry -------------remove\n");
    printf("delete the list -------------delete\n");
    printf("to display this window again --help\n");
}