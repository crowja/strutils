#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strutils.h"
#include "tinytest.h"


#ifdef _COLOR_CODE
#undef _COLOR_CODE
#endif
#define _COLOR_CODE      0x1B
#ifdef _COLOR_RED
#undef _COLOR_RED
#endif
#define _COLOR_RED       "[1;31m"
#ifdef _COLOR_GREEN
#undef _COLOR_GREEN
#endif
#define _COLOR_GREEN     "[1;32m"
#ifdef _COLOR_YELLOW
#undef _COLOR_YELLOW
#endif
#define _COLOR_YELLOW    "[1;33m"
#ifdef _COLOR_RESET
#undef _COLOR_RESET
#endif
#define _COLOR_RESET     "[0m"

static void
_printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", _COLOR_CODE, _COLOR_YELLOW, name, _COLOR_CODE, _COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}

void        test_check(void);
void        test_chomp(void);
void        test_crush(void);
void        test_dup(void);
void        test_is_ws(void);
void        test_lcat(void);
void        test_split_1(void);
void        test_splitpp(void);
void        test_tolower(void);
void        test_toupper(void);
void        test_trim(void);
void        test_trim_ip(void);
void        test_wssplit(void);

void
test_check(void)
{
   char       *cp = malloc(10000);

   _printf_test_name("test_check", NULL);
   memset(cp, 'a', 10000);
   ASSERT_EQUALS(0, stru_check(cp, 100));
   free(cp);
}

void
test_chomp(void)
{
   char        test_str0[] = "This is to be chomped";
   char        test_str1[] = "This is to be chomped\n\n\n";

   _printf_test_name("test_chomp", NULL);

   ASSERT_STRING_EQUALS(test_str0, stru_chomp(test_str1));
}

void
test_crush(void)
{
   char        test_str0[] = "Thisistobecrushed";
   char        test_str1[] = "\r\n   \nThi\n s is to be\r  crushed\n\n\n";

   _printf_test_name("test_crush", NULL);

   ASSERT_STRING_EQUALS(test_str0, stru_crush(test_str1));
}

void
test_dup(void)
{
   char        test_str[] = "This is to be\r\nduplicated";
   char       *cp;

   _printf_test_name("test_dup", "stru_dup");

   cp = stru_dup(test_str);
   ASSERT_STRING_EQUALS(test_str, cp);
   free(cp);

   cp = stru_dup(NULL);
   ASSERT_EQUALS(NULL, cp);
}

void
test_is_ws(void)
{
   char        test_str1[] = "\r\n   \n \n \r  \n\n\n\r";
   char        test_str2[] = "\r\n   \ni\n \rab\n\n\n\r";

   _printf_test_name("test_is_ws", NULL);

   ASSERT_EQUALS(1, stru_is_ws(test_str1));
   ASSERT_EQUALS(0, stru_is_ws(test_str2));
}


void
test_lcat(void)
{
   char       *s1 = malloc(10);
   char       *s2 = malloc(10);

   _printf_test_name("test_lcat", NULL);

   *s1 = '\0';
   *s2 = '\0';

   strcat(s1, "string1");
   strcat(s2, "string2");

   ASSERT_STRING_EQUALS("string1string2", stru_lcat(&s1, &s2));

   free(s1);
   free(s2);
}


void
test_split_1(void)
{

   char      **list = stru_split('\t', "now\t'Is\tthe' time for\tall good dogs \t\ta");
   char      **cp;

   _printf_test_name("test_split_1", NULL);

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

void
test_splitpp(void)
{

   char      **list = NULL;
   char      **cp;
   unsigned    ret;

   _printf_test_name("test_splitpp", NULL);

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

void
test_tolower(void)
{
   char        str[] = "My Dog Has Fleas!!!";

   _printf_test_name("test_tolower", NULL);

   ASSERT_STRING_EQUALS("my dog has fleas!!!", stru_tolower(str));
}

void
test_toupper(void)
{
   char        str[] = "My Dog Has Fleas!!!";

   _printf_test_name("test_toupper", NULL);

   ASSERT_STRING_EQUALS("MY DOG HAS FLEAS!!!", stru_toupper(str));
}

void
test_trim(void)
{
   char        str[] = "\t\t   no whitespace left or right! \r\n  ";

   _printf_test_name("test_trim", NULL);

   ASSERT_STRING_EQUALS("no whitespace left or right!", stru_trim(str));

}

void
test_wssplit(void)
{

   char      **list;
   char      **cp;

   _printf_test_name("test_wssplit", NULL);

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
   RUN(test_is_ws);
   RUN(test_lcat);
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
