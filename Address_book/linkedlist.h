
struct Address {
    char name[50];
    char surname[50];
    char phone[50];
    char email[50];
    struct Address *next;
};

struct Address *create_node(char *name, char *surname, char *phone, char *email);
void add_to_list(struct Address **list, struct Address *person);
void print_list(struct Address *list);
void print_node(struct Address *node);
char* read_input();
void addr_from_input(struct Address **list);
void load_addresses(FILE *file, struct Address **list);

void search_by_data(struct Address *list);
void search_by_number(struct Address *list);
void search(struct Address *list);

void insert_to_list(struct Address **list, struct Address *person);
void insert (struct Address **list);

void delete_list(struct Address **list);
void delete_selected(struct Address *list);
void delete_node(struct Address *list);
void delete_first_node(struct Address **list);
void help();