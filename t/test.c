#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strutils.h"
#include "tinytest.h"
#include "tinyhelp.h"

#if 0
void      test_check(void);
void      test_chomp(void);
void      test_crush(void);
void      test_dup(void);
void      test_isspace(void);
void      test_lcat(void);
void      test_split_1(void);
void      test_splitpp(void);
void      test_tolower(void);
void      test_toupper(void);
void      test_trim(void);
void      test_trim_ip(void);
void      test_wssplit(void);
#endif

static void
test_check(void)
{
   char     *cp = malloc(10000);
   fprintf_test_info(stdout, "test_check", "stru_check");
   memset(cp, 'a', 10000);
   ASSERT_EQUALS(0, stru_check(cp, 100));
   free(cp);
}

static void
test_chomp(void)
{
   char      test_str0[] = "This is to be chomped";
   char      test_str1[] = "This is to be chomped\n\n\n";

   fprintf_test_info(stdout, "test_chomp", "stru_chomp");
   ASSERT_STRING_EQUALS(test_str0, stru_chomp(test_str1));
}

static void
test_crush(void)
{
   char      test_str0[] = "Thisistobecrushed";
   char      test_str1[] = "\r\n   \nThi\n s is to be\r  crushed\n\n\n";

   fprintf_test_info(stdout, "test_crush", "stru_crush");
   ASSERT_STRING_EQUALS(test_str0, stru_crush(test_str1));
}

static void
test_dup(void)
{
   char      test_str[] = "This is to be\r\nduplicated";
   char     *cp;

   fprintf_test_info(stdout, "test_dup", "stru_dup");
   cp = stru_dup(test_str);
   ASSERT_STRING_EQUALS(test_str, cp);
   free(cp);
   cp = stru_dup(NULL);
   ASSERT_EQUALS(NULL, cp);
}

static void
test_isspace(void)
{
   char      test_str1[] = "\r\n   \n \n \r  \n\n\n\r";
   char      test_str2[] = "\r\n   \ni\n \rab\n\n\n\r";

   fprintf_test_info(stdout, "test_isspace", "stru_isspace");
   ASSERT_EQUALS(1, stru_isspace(test_str1));
   ASSERT_EQUALS(0, stru_isspace(test_str2));
}


static void
test_lcat(void)
{
   char     *s1 = malloc(10);
   char     *s2 = malloc(10);

   fprintf_test_info(stdout, "test_lcat", "stru_lcat");
   *s1 = '\0';
   *s2 = '\0';
   strcat(s1, "string1");
   strcat(s2, "string2");
   ASSERT_STRING_EQUALS("string1string2", stru_lcat(&s1, &s2));
   free(s1);
   free(s2);
}

static void
test_leadswith(void)
{
   fprintf_test_info(stdout, "test_leadswith", "stru_leadswith");
   ASSERT_EQUALS(0, stru_leadswith(" \t\r  my dog has fleas", '#'));
   ASSERT_EQUALS(0, stru_leadswith("                       ", '#'));
   ASSERT_EQUALS(1, stru_leadswith(" \t\r #my dog has fleas", '#'));
   ASSERT_EQUALS(0, stru_leadswith("                  ", ' '));
}

static void
test_split_1(void)
{

   char    **list = stru_split('\t', "now\t'Is\tthe' time for\tall good dogs \t\ta");
   char    **cp;

   fprintf_test_info(stdout, "test_split_1", "stru_split");
   ASSERT_STRING_EQUALS("now", list[0]);
   ASSERT_STRING_EQUALS("Is\tthe time for", list[1]);   /* single quotes removed */
   ASSERT_STRING_EQUALS("all good dogs ", list[2]);

   cp = list;

   while (*cp != NULL) {
#if 0
      printf("-->%s<--\n", *cp);
#endif
      free(*cp);
      cp += 1;
   }

   free(list);
}

static void
test_splitpp(void)
{

   char    **list = NULL;
   char    **cp;
   unsigned  ret;

   fprintf_test_info(stdout, "test_splitpp", "stru_splitpp");
   /* stru_splitpp(char delim, char *str, char **list) */
   ret = stru_splitpp('\t', "now\t'Is\tthe' time for\tall good dogs \t\ta", list);

   /* FIXME at some point need to fix this */
#if 0
   ASSERT_STRING_EQUALS("now", list[0]);
   ASSERT_STRING_EQUALS("Is\tthe time for", list[1]);   /* single quotes removed */
   ASSERT_STRING_EQUALS("all good dogs ", list[2]);
#endif

   cp = list;

   while (*cp != NULL) {
#if 0
      printf("-->%s<--\n", *cp);
#endif
      free(*cp);
      cp += 1;
   }

   free(list);
}

static void
test_tolower(void)
{
   char      str[] = "My Dog Has Fleas!!!";

   fprintf_test_info(stdout, "test_tolower", "stru_tolower");
   ASSERT_STRING_EQUALS("my dog has fleas!!!", stru_tolower(str));
}

static void
test_toupper(void)
{
   char      str[] = "My Dog Has Fleas!!!";

   fprintf_test_info(stdout, "test_toupper", "stru_toupper");
   ASSERT_STRING_EQUALS("MY DOG HAS FLEAS!!!", stru_toupper(str));
}

static void
test_trim(void)
{
   char      str[] = "\t\t   no whitespace left or right! \r\n  ";

   fprintf_test_info(stdout, "test_trim", "stru_trim");
   ASSERT_STRING_EQUALS("no whitespace left or right!", stru_trim(str));
}

static void
test_wssplit(void)
{

   char    **list;
   char    **cp;

   fprintf_test_info(stdout, "test_wssplit", "stru_wssplit");
   list = stru_wssplit("now\tIs\tthe time for\tall good dogs \t\ta");
   ASSERT_STRING_EQUALS("now", list[0]);
   ASSERT_STRING_EQUALS("Is", list[1]);
   ASSERT_STRING_EQUALS("the", list[2]);
   ASSERT_STRING_EQUALS("time", list[3]);

   cp = list;

   while (*cp != NULL) {
#if 0
      printf("-->%s<--\n", *cp);
#endif
      free(*cp);
      cp += 1;
   }

   free(list);
}

int
main(void)
{
   printf("%s\n", stru_version());

   RUN(test_check);
   RUN(test_chomp);
   RUN(test_crush);
   RUN(test_dup);
   RUN(test_isspace);
   RUN(test_lcat);
   RUN(test_leadswith);
   RUN(test_split_1);

   /** FIXME. Not sure how to invoke this function correctly, and
    *  it could be the code never actually worked.
    */

#if 0
   RUN(test_splitpp);
#endif

   RUN(test_tolower);
   RUN(test_toupper);
   RUN(test_trim);
   RUN(test_wssplit);

   return TEST_REPORT();
}
