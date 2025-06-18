#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

struct Book {
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int quantity;
    int is_available; // 1 for available, 0 for not available
};

struct Book library[MAX_BOOKS];
int book_count = 0;

// Function prototypes
void display_menu();
void add_book();
void display_all_books();
void search_book();
void update_book();
void delete_book();
void save_to_file();
void load_from_file();
int get_valid_integer_input(const char *prompt);

int main() {
    load_from_file();
    
    int choice;
    do {
        display_menu();
        printf("Enter your choice: ");
        choice = get_valid_integer_input("");
        
        switch(choice) {
            case 1:
                add_book();
                break;
            case 2:
                display_all_books();
                break;
            case 3:
                search_book();
                break;
            case 4:
                update_book();
                break;
            case 5:
                delete_book();
                break;
            case 6:
                save_to_file();
                printf("Data saved successfully. Exiting...\n");
                break;
            default:
                if (choice != 6) {
                    printf("Invalid choice. Please try again.\n");
                }
        }
    } while (choice != 6);
    
    return 0;
}

void display_menu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. Display All Books\n");
    printf("3. Search Book\n");
    printf("4. Update Book\n");
    printf("5. Delete Book\n");
    printf("6. Exit\n");
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }
    
    struct Book new_book;
    
    printf("\nEnter Book Details:\n");
    
    // Get a unique ID
    new_book.id = book_count + 1;
    
    printf("Title: ");
    fgets(new_book.title, MAX_TITLE_LENGTH, stdin);
    new_book.title[strcspn(new_book.title, "\n")] = '\0'; // Remove newline
    
    printf("Author: ");
    fgets(new_book.author, MAX_AUTHOR_LENGTH, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = '\0'; // Remove newline
    
    new_book.quantity = get_valid_integer_input("Quantity: ");
    
    new_book.is_available = 1;
    
    library[book_count++] = new_book;
    printf("Book added successfully with ID: %d\n", new_book.id);
}

void display_all_books() {
    if (book_count == 0) {
        printf("No books in the library.\n");
        return;
    }
    
    printf("\n%-5s %-30s %-20s %-10s %s\n", "ID", "Title", "Author", "Quantity", "Available");
    printf("-----------------------------------------------------------------\n");
    
    for (int i = 0; i < book_count; i++) {
        printf("%-5d %-30s %-20s %-10d %s\n", 
               library[i].id, 
               library[i].title, 
               library[i].author, 
               library[i].quantity,
               library[i].is_available ? "Yes" : "No");
    }
}

void search_book() {
    if (book_count == 0) {
        printf("No books in the library to search.\n");
        return;
    }
    
    int choice;
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Title\n");
    printf("3. Author\n");
    printf("Enter your choice: ");
    choice = get_valid_integer_input("");
    
    if (choice < 1 || choice > 3) {
        printf("Invalid choice.\n");
        return;
    }
    
    int found = 0;
    
    if (choice == 1) {
        int id;
        printf("Enter book ID: ");
        id = get_valid_integer_input("");
        
        for (int i = 0; i < book_count; i++) {
            if (library[i].id == id) {
                printf("\nBook Found:\n");
                printf("ID: %d\n", library[i].id);
                printf("Title: %s\n", library[i].title);
                printf("Author: %s\n", library[i].author);
                printf("Quantity: %d\n", library[i].quantity);
                printf("Available: %s\n", library[i].is_available ? "Yes" : "No");
                found = 1;
                break;
            }
        }
    } 
    else if (choice == 2) {
        char title[MAX_TITLE_LENGTH];
        printf("Enter book title: ");
        fgets(title, MAX_TITLE_LENGTH, stdin);
        title[strcspn(title, "\n")] = '\0';
        
        printf("\nSearch Results:\n");
        printf("%-5s %-30s %-20s %-10s %s\n", "ID", "Title", "Author", "Quantity", "Available");
        printf("-----------------------------------------------------------------\n");
        
        for (int i = 0; i < book_count; i++) {
            if (strstr(library[i].title, title) != NULL) {
                printf("%-5d %-30s %-20s %-10d %s\n", 
                       library[i].id, 
                       library[i].title, 
                       library[i].author, 
                       library[i].quantity,
                       library[i].is_available ? "Yes" : "No");
                found = 1;
            }
        }
    } 
    else if (choice == 3) {
        char author[MAX_AUTHOR_LENGTH];
        printf("Enter author name: ");
        fgets(author, MAX_AUTHOR_LENGTH, stdin);
        author[strcspn(author, "\n")] = '\0';
        
        printf("\nSearch Results:\n");
        printf("%-5s %-30s %-20s %-10s %s\n", "ID", "Title", "Author", "Quantity", "Available");
        printf("-----------------------------------------------------------------\n");
        
        for (int i = 0; i < book_count; i++) {
            if (strstr(library[i].author, author) != NULL) {
                printf("%-5d %-30s %-20s %-10d %s\n", 
                       library[i].id, 
                       library[i].title, 
                       library[i].author, 
                       library[i].quantity,
                       library[i].is_available ? "Yes" : "No");
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("No books found matching your criteria.\n");
    }
}

void update_book() {
    if (book_count == 0) {
        printf("No books in the library to update.\n");
        return;
    }
    
    int id;
    printf("Enter the ID of the book to update: ");
    id = get_valid_integer_input("");
    
    int found = -1;
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Book with ID %d not found.\n", id);
        return;
    }
    
    printf("\nCurrent Book Details:\n");
    printf("1. Title: %s\n", library[found].title);
    printf("2. Author: %s\n", library[found].author);
    printf("3. Quantity: %d\n", library[found].quantity);
    printf("4. Available: %s\n", library[found].is_available ? "Yes" : "No");
    
    printf("\nEnter the field number to update (1-4): ");
    int field = get_valid_integer_input("");
    
    switch(field) {
        case 1:
            printf("Enter new title: ");
            fgets(library[found].title, MAX_TITLE_LENGTH, stdin);
            library[found].title[strcspn(library[found].title, "\n")] = '\0';
            break;
        case 2:
            printf("Enter new author: ");
            fgets(library[found].author, MAX_AUTHOR_LENGTH, stdin);
            library[found].author[strcspn(library[found].author, "\n")] = '\0';
            break;
        case 3:
            library[found].quantity = get_valid_integer_input("Enter new quantity: ");
            break;
        case 4:
            {
                int avail;
                printf("Is the book available? (1 for Yes, 0 for No): ");
                avail = get_valid_integer_input("");
                library[found].is_available = (avail == 1) ? 1 : 0;
            }
            break;
        default:
            printf("Invalid field number.\n");
            return;
    }
    
    printf("Book details updated successfully.\n");
}

void delete_book() {
    if (book_count == 0) {
        printf("No books in the library to delete.\n");
        return;
    }
    
    int id;
    printf("Enter the ID of the book to delete: ");
    id = get_valid_integer_input("");
    
    int found = -1;
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Book with ID %d not found.\n", id);
        return;
    }
    
    // Shift all books after the found index one position left
    for (int i = found; i < book_count - 1; i++) {
        library[i] = library[i + 1];
    }
    
    book_count--;
    printf("Book with ID %d deleted successfully.\n", id);
}

void save_to_file() {
    FILE *file = fopen("library_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    for (int i = 0; i < book_count; i++) {
        fprintf(file, "%d|%s|%s|%d|%d\n", 
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].quantity,
                library[i].is_available);
    }
    
    fclose(file);
}

void load_from_file() {
    FILE *file = fopen("library_data.txt", "r");
    if (file == NULL) {
        // File doesn't exist yet, that's okay
        return;
    }
    
    book_count = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), file) && book_count < MAX_BOOKS) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';
        
        char *token;
        token = strtok(line, "|");
        if (token == NULL) continue;
        library[book_count].id = atoi(token);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strncpy(library[book_count].title, token, MAX_TITLE_LENGTH);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strncpy(library[book_count].author, token, MAX_AUTHOR_LENGTH);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        library[book_count].quantity = atoi(token);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        library[book_count].is_available = atoi(token);
        
        book_count++;
    }
    
    fclose(file);
}

int get_valid_integer_input(const char *prompt) {
    char input[20];
    int number;
    int valid = 0;
    
    do {
        if (prompt[0] != '\0') {
            printf("%s", prompt);
        }
        
        fgets(input, sizeof(input), stdin);
        
        // Check if input is a valid integer
        valid = 1;
        for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }
        
        if (!valid) {
            printf("Invalid input. Please enter a number: ");
        } else {
            number = atoi(input);
        }
    } while (!valid);
    
    
    return number;
}