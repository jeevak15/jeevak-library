/*
========================================================
        LIBRARY MANAGEMENT SYSTEM - main.c
========================================================

Features:
1. Add Book
2. View Books
3. Search Book
4. Delete Book
5. Save Data in books.txt

Concepts Used:
- Structures
- Functions
- Arrays
- File Handling
- Modular Programming Style

Author: Your Name
========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure for Book
struct Book
{
    int id;
    char title[100];
    char author[100];
    int quantity;
};

// Global array
struct Book books[MAX_BOOKS];

int count = 0;

// Function Declarations
void loadBooks();
void saveBooks();
void addBook();
void viewBooks();
void searchBook();
void deleteBook();

int main()
{
    int choice;

    // Load books from file at start
    loadBooks();

    while (1)
    {
        printf("\n=====================================\n");
        printf("   LIBRARY MANAGEMENT SYSTEM\n");
        printf("=====================================\n");

        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                viewBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                deleteBook();
                break;

            case 5:
                saveBooks();
                printf("\nData saved successfully.\n");
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

// Function to Load Books from File
void loadBooks()
{
    FILE *file;

    file = fopen("books.txt", "r");

    if (file == NULL)
    {
        return;
    }

    while (fscanf(file, "%d,%99[^,],%99[^,],%d\n",
                  &books[count].id,
                  books[count].title,
                  books[count].author,
                  &books[count].quantity) != EOF)
    {
        count++;
    }

    fclose(file);
}

// Function to Save Books to File
void saveBooks()
{
    FILE *file;

    file = fopen("books.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%s,%d\n",
                books[i].id,
                books[i].title,
                books[i].author,
                books[i].quantity);
    }

    fclose(file);
}

// Function to Add Book
void addBook()
{
    if (count >= MAX_BOOKS)
    {
        printf("\nLibrary is full!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &books[count].id);

    getchar();

    printf("Enter Book Title: ");
    fgets(books[count].title, sizeof(books[count].title), stdin);

    books[count].title[strcspn(books[count].title, "\n")] = '\0';

    printf("Enter Author Name: ");
    fgets(books[count].author, sizeof(books[count].author), stdin);

    books[count].author[strcspn(books[count].author, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &books[count].quantity);

    count++;

    saveBooks();

    printf("\nBook added successfully!\n");
}

// Function to View All Books
void viewBooks()
{
    if (count == 0)
    {
        printf("\nNo books available.\n");
        return;
    }

    printf("\n========== BOOK LIST ==========\n");

    for (int i = 0; i < count; i++)
    {
        printf("\nBook %d\n", i + 1);
        printf("ID       : %d\n", books[i].id);
        printf("Title    : %s\n", books[i].title);
        printf("Author   : %s\n", books[i].author);
        printf("Quantity : %d\n", books[i].quantity);
    }
}

// Function to Search Book
void searchBook()
{
    int id;
    int found = 0;

    printf("\nEnter Book ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (books[i].id == id)
        {
            printf("\nBook Found!\n");

            printf("ID       : %d\n", books[i].id);
            printf("Title    : %s\n", books[i].title);
            printf("Author   : %s\n", books[i].author);
            printf("Quantity : %d\n", books[i].quantity);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nBook not found.\n");
    }
}

// Function to Delete Book
void deleteBook()
{
    int id;
    int found = 0;

    printf("\nEnter Book ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (books[i].id == id)
        {
            for (int j = i; j < count - 1; j++)
            {
                books[j] = books[j + 1];
            }

            count--;

            saveBooks();

            printf("\nBook deleted successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nBook not found.\n");
    }
}
