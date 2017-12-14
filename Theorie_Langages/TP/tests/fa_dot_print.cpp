#include "gtest/gtest.h"
#include <cstring>
#include <string.h>

extern "C"
{
    #include "fa.h"
}


TEST(fa_dot_print, file_input)
{
  struct fa *selfFa = (struct fa *) malloc(sizeof(struct fa));
  fa_create(selfFa, 2, 3);

  std::string str = "txt/wrong_dot_file.dot";
  char * writable = new char[str.size() + 1];
  std::copy(str.begin(), str.end(), writable);
  writable[str.size()] = '\0'; // don't forget the terminating 0

  std::string str0 = "test_dot.dot";
  char * writable0 = new char[str.size() + 1];
  std::copy(str0.begin(), str0.end(), writable0);
  writable0[str0.size()] = '\0'; // don't forget the terminating 0


  FILE *file = NULL;

  EXPECT_EQ(-1, fa_dot_print(selfFa, file, writable));

  EXPECT_EQ(0, fa_dot_print(selfFa, file, writable0));


  delete[] writable;
  delete[] writable0;

  fa_destroy(selfFa);
}
