#ifndef AAU_IMPR_EXERCISES_12_2_SRC_MAIN_H_
#define AAU_IMPR_EXERCISES_12_2_SRC_MAIN_H_

#include <stdlib.h>

enum Constants {
  kShelfSize = 100,
  kTitleLength = 100,
  kAuthorLength = 100,
  kPublisherLength = 100
};

typedef struct Book {
  char title[kTitleLength];
  char author[kAuthorLength];
  char publisher[kPublisherLength];
  unsigned short publishing_year;
  bool is_university_text_book;
} Book;

Book NewBook(char* title, char* author, char* publisher, int publishing_year,
             bool is_university_text_book);

void PrintShelf(Book* shelf, size_t shelf_size);

int SortByTitleComparator(const void* argument_one, const void* argument_two);

int SortByYearComparator(const void* argument_one, const void* argument_two);

int SortByKindComparator(const void* argument_one, const void* argument_two);

void SortBooksByTitle(Book* shelf, size_t shelf_size);

void SortBooksByKindAndYear(Book* shelf, size_t shelf_size);

#endif  // AAU_IMPR_EXERCISES_12_2_SRC_MAIN_H_
