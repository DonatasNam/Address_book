#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

int main(void)
{   
    printf("\n ----Start of Program----\n");
    printf("Enter a function, for help with functions type 'help'\n\n");
    struct Address *list = NULL;
    char command[16];
	char input[16];	
    char address_file_path[30] = "book.txt";
    FILE *address_file = NULL;

    address_file = fopen(address_file_path, "r");

    if( address_file == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }
    load_addresses(address_file,&list);
    print_list(list);
    while( fgets( input, 15, stdin) ) {
		
		sscanf(input,"%s",command);	
		
		if ( strncmp(command, "quit", 5) == 0) {
			printf("\n\n----Program finnished----\n");
			break;
        }else if (strncmp(command, "load", 5) == 0){
            load_addresses(address_file,&list);
            print_list(list);
        }else if (strncmp(command, "help", 5) == 0){
            help();
        }else if (strncmp(command, "print", 6) == 0){
            print_list(list);
        }else if (strncmp(command, "add", 3) == 0){
            printf("\n Input contact information\n");
            addr_from_input(&list);
        }else if (strncmp(command, "search", 7) == 0){
            printf("\n To search by number type 'number', to search by data type 'data'\n");
            search(list);
        }else if (strncmp(command, "delete", 7) == 0){
            delete_list(&list);
        }else if (strncmp(command, "insert", 7) == 0){
            printf("\n Enter data you wish to insert: ");
            insert(&list);
            print_list(list);
        }else if (strncmp(command, "remove", 7) == 0){
            printf("Input a number: ");
            delete_selected(list);
        }else if (strncmp(command, "rmfirst", 8) == 0){
            delete_first_node(&list);
        }
        
        		
    }
    return 0;
}