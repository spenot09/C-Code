#include "database_main.h"

/* read file containing database of books */

/*"match" will hold the string until whitespace of a newline and will be used to see if it matches "Title","Author" or"Year". "Count" will be used to increment to the next structure in the array. If the file is successfully opened matches are looked for. If matches are found then the line is read, newline character is removed and the resulting string is added to strucure element. */

void read_book_database(char * file_name) {
    /* fill in the code here in part 3, and add any extra functions you need */
    char match[101], temp[101];
    char * Title = "Title:";
    char * Author = "Author:";
    char * Year = "Year:";

    int count = 0, year;

    no_books = 0;

    FILE * fp = fopen(file_name, "r");

    if (fp == NULL) {
        fprintf(stderr, "File is empty\n");
        exit(-1);
    }
    /* Searches for matching strings in file and populates structure */
    while (!feof(fp)) { /* loops util EOF is reached */
        fscanf(fp, "%s", match);
        if (strcmp(match, Title) == 0) {
            fgetc(fp); /* Absorbs the extra space that isn't needed */
            fgets(temp, 101, fp);
            strtok(temp, "\n");
            if (temp[0] != '\n') { /* ensures an empty string is not entered */
                strcpy(book_array[no_books].title, temp);
            } else { /* exits if invalid title is inputted */
                fprintf(stderr, "File is corrupted\n");
                exit(-1);
            }
            count++;
        }

        if (strcmp(match, Author) == 0) {
            fgetc(fp); /* Absorbs the extra space that isn't needed */
            fgets(temp, 101, fp);
            strtok(temp, "\n");
            if (temp[0] != '\n') { /* ensures an empty string is not entered */
                strcpy(book_array[no_books].author, temp);
            } else {/* exits if empty string for author is entered */
                fprintf(stderr, "File is corrupted\n");
                exit(-1);
            }
            count++;
        }
        if (strcmp(match, Year) == 0) {
            fgetc(fp); /* Absorbs the extra space that isn't needed */
            fgets(match, 101, fp);
            year = atoi(match); /* converts string to an int */
            book_array[no_books].year = year;
            count++;
        }
        if (count == 3) { /* test to see if all elements of stucture are filled */
            count = 0; /*resets counter */
            no_books++; /* moves on to next structure to populate */
        }

    }
    fclose(fp);
}
