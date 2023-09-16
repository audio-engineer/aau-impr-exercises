#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Book NewBook(char* title, char* author, char* publisher, int publishing_year,
             bool is_university_text_book) {
  Book book;

  strcpy(book.title, title);
  strcpy(book.author, author);
  strcpy(book.publisher, publisher);
  book.publishing_year = publishing_year;
  book.is_university_text_book = is_university_text_book;

  return book;
}

void PrintShelf(Book* shelf, size_t shelf_size) {
  short book_id = 1;

  for (int i = 0; i < shelf_size; i++) {
    Book book = shelf[i];

    if ('\0' == book.title[0] || 0 == strlen(book.title) ||
        0 == book.publishing_year) {
      continue;
    }

    printf("Book %d:\n", book_id);
    printf("\t- Title: %s\n", shelf[i].title);
    printf("\t- Author: %s\n", shelf[i].author);
    printf("\t- Publisher: %s\n", shelf[i].publisher);
    printf("\t- Publishing year: %d\n", shelf[i].publishing_year);
    printf("\t- University text book: %s\n",
           (int)shelf[i].is_university_text_book ? "yes" : "no");
    printf("------------------------------------------------------------\n");

    book_id++;
  }
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
int SortByTitleComparator(const void* argument_one, const void* argument_two) {
  Book* book_one = (Book*)argument_one;
  Book* book_two = (Book*)argument_two;

  return strcmp(book_one->title, book_two->title);
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
int SortByYearComparator(const void* argument_one, const void* argument_two) {
  Book* book_one = (Book*)argument_one;
  Book* book_two = (Book*)argument_two;

  if (book_one->publishing_year < book_two->publishing_year) {
    return -1;
  }

  if (book_one->publishing_year > book_two->publishing_year) {
    return 1;
  }

  return 0;
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
int SortByKindComparator(const void* argument_one, const void* argument_two) {
  Book* book_one = (Book*)argument_one;
  Book* book_two = (Book*)argument_two;

  if (!book_one->is_university_text_book &&
      (int)book_two->is_university_text_book) {
    return -1;
  }

  if ((int)book_one->is_university_text_book &&
      !book_two->is_university_text_book) {
    return 1;
  }

  return 0;
}

void SortBooksByTitle(Book* shelf, size_t shelf_size) {
  qsort(shelf, shelf_size, sizeof(shelf[0]), SortByTitleComparator);
}

void SortBooksByKindAndYear(Book* shelf, size_t shelf_size) {
  qsort(shelf, shelf_size, sizeof(shelf[0]), SortByKindComparator);
  qsort(shelf, shelf_size, sizeof(shelf[0]), SortByYearComparator);
}

int main() {
  Book shelf[kShelfSize] = {"", "", "", 0, false};

  // NOLINTBEGIN(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)
  shelf[0] = NewBook("Problem Solving and Program Design in C",
                     "Hanly and Koffman", "Pearson", 2010, true);
  shelf[1] = NewBook("C by Dissection", "Kelley and Pohl", "Addison Wesley",
                     2001, true);
  shelf[2] = NewBook("The C Programming Language", "Kernighan og Ritchie",
                     "Prentice Hall", 1988, true);
  shelf[3] = NewBook("Pelle Erobreren", "Martin Andersen Nexoe", "Gyldendal",
                     1910, false);
  shelf[4] = NewBook("Ditte Menneskebarn", "Martin Andersen Nexoe", "Gyldendal",
                     1917, false);
  // NOLINTEND(readability-magic-numbers,cppcoreguidelines-avoid-magic-numbers)

  size_t shelf_size = sizeof(shelf) / sizeof(shelf[0]);

  //  SortBooksByTitle(shelf, shelf_size);
  //  SortBooksByKindAndYear(shelf, shelf_size);
  PrintShelf(shelf, shelf_size);

  return EXIT_SUCCESS;
}
