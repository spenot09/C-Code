#include "database_main.h"
#include <string.h>

    /* menu_add_book():
     *
     * Add new book to database
     */
    void SortABC(struct Book * book_array, int n);

/* "error" ensures input is prompted until valid input. 
   "check" is used to ensure an int is entered for year.
   "ch" is a temporary variable used to empty the input buffer.*/

void menu_add_book(void) {
    /* fill in the code here  in part 1, and add any extra functions you need */
    int error = 1, check, ch, len;
    char temp[200];

    while (error == 1) {
        fprintf(stderr, "Enter title:\n");
        fgets(temp, MAX_TITLE_LENGTH + 1, stdin); /*the input is read and automatically truncated */
        strtok(temp, "\n");
        len = strlen(temp);
        if (temp[0] != '\n') { /* ensures user didn't enter an empty string */
            strcpy(book_array[no_books].title, temp);
            error = 0;
        }
    }

    error = 1;
    if (len > 99) { /* empties out the buffer to prevent overflow */
        while ((ch = getchar()) != '\n');
    }
    while (error == 1) {

        fprintf(stderr, "Enter author:\n");
        fgets(temp, MAX_AUTHOR_LENGTH + 1, stdin);
        strtok(temp, "\n"); /* removes the new line character as it will be easier to print later on */
        len = strlen(temp); /* will be used to see if buffer needs emptying */
        if (temp[0] != '\n') {
            strcpy(book_array[no_books].author, temp);
            error = 0;
        }
    }
    if (len > 99) {
        while ((ch = getchar()) != '\n');
    }

    error = 1;
    while (error == 1) {
        fprintf(stderr, "Enter year:\n");
        check = fscanf(stdin, "%d", & book_array[no_books].year);
        scanf("%*[^\n]%*1[\n]");
        if (check == 1) {
            error = 0;
        }
    }
    while ((ch = getchar()) != '\n' && ch != EOF);
    no_books++; /* increments array index so next book structure can be populated */
    SortABC(book_array, no_books);
}

/* menu_print_database():
 *
 * Print database of books to standard output in alphabetical order of title.
 */

/* The database is sorted in alphabetical order and is printed element by element by element 
   by a series of fprintf() statements */

void menu_print_database(void) {
    /* fill in the code here in part 1, and add any extra functions you need */
    int i;

    SortABC(book_array, no_books);
    for (i = 0; i < no_books; i++) {
        fprintf(stdout, "Title: %s\n", strtok(book_array[i].title, "\n"));
        fprintf(stdout, "Author: %s\n", book_array[i].author);
        fprintf(stdout, "Year: %d\n", book_array[i].year);
        fprintf(stdout, "\n");
    }

}

/* This function goes through the array of structs and compares the alphabetic order of the titles of neighbouring elements         (essentially a bubble sort algorithm) and performs swaps when necessary*/

void SortABC(struct Book * book_array, int n) {
    int j, i;

    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            if (strcmp(book_array[j].title, book_array[j + 1].title) > 0) {
                struct Book temp = book_array[j];
                book_array[j] = book_array[j + 1];
                book_array[j + 1] = temp;
            }
        }
    }
}
