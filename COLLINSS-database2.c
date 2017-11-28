#include "database_main.h"

int Search(struct Book * book_array, char * Title);
/* menu_get_book_details():
 *
 * Get details of book from database.
 */

/* "Title" will hold the title entered by the user. "location" will hold the index 
    of the location of the serached for book. Details are printed of match is found 
    otherwise an error is printed */

void menu_get_book_details(void) {
    /* fill in the code here in part 2, and add any extra functions you need */
    char Title[MAX_TITLE_LENGTH];
    int location;

    fprintf(stderr, "Enter book title to be found\n");
    fgets(Title, MAX_TITLE_LENGTH, stdin);
    strtok(Title, "\n");
    location = Search(book_array, Title);
    if (location == -1)
        fprintf(stderr, "Book not found\n");
    else {
        fprintf(stdout, "Title: %s\n", strtok(book_array[location].title, "\n"));
        fprintf(stdout, "Author: %s\n", book_array[location].author);
        fprintf(stdout, "Year: %d\n", book_array[location].year);
        fprintf(stdout, "\n");
    }
}

/* menu_delete_book():
 *
 * Delete new book from database.
 */

/* Variables are similar to previous function. If book is found in the database,
   then all subsequent books after the sought after book are shifted down by one. 
   This will result in the unwanted book being overwritten and deleted */

void menu_delete_book(void) {
    /* fill in the code here in part 2, and add any extra functions you need */
    char Title[MAX_TITLE_LENGTH];
    int location, i;

    fprintf(stderr, "Enter book title to be deleted\n");
    fgets(Title, MAX_TITLE_LENGTH, stdin);
    strtok(Title, "\n");

    location = Search(book_array, Title);
    if (location == -1)
        fprintf(stderr, "Book not found\n");
    else {
        for (i = location; i < no_books; i++)
            book_array[i] = book_array[i + 1];
    }

    no_books--;
}

/* This function searches through the array looking for a match for "Title". If a match is found the index is returned, if not "-1"  is returned*/
int Search(struct Book * book_array, char * Title) {
    int i;

    for (i = 0; i < no_books; i++) {
        if (strcmp(book_array[i].title, Title) == 0)
            return i;
    }
    return -1;
}
