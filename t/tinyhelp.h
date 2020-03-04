/**
 * @file tinyhelp.h
 * @version 0.2.0
 * @see https://github.com/crowja/tinyhelp
 * @date Sun Feb 16, 2020 11:18:06 PM CST
 * @copyright 2020 John A. Crow <crowja@gmail.com>
 * @license Unlicense <http://unlicense.org/>
 * @brief Helpers supporting Joe Walnes' tinytest.h unit test framework.
 */

#ifndef TINY_HELP_H
#define TINY_HELP_H

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "tinytest.h"

#ifdef  TH_COLOR_RED
#undef  TH_COLOR_RED
#endif
#define TH_COLOR_RED        "\x1B[31;1m"

#ifdef  TH_COLOR_GREEN
#undef  TH_COLOR_GREEN
#endif
#define TH_COLOR_GREEN      "\x1B[32;1m"

#ifdef  TH_COLOR_YELLOW
#undef  TH_COLOR_YELLOW
#endif
#define TH_COLOR_YELLOW     "\x1B[33;1m"

#ifdef  TH_COLOR_BLUE
#undef  TH_COLOR_BLUE
#endif
#define TH_COLOR_BLUE       "\x1B[34;1m"

#ifdef  TH_COLOR_RESET
#undef  TH_COLOR_RESET
#endif
#define TH_COLOR_RESET      "\x1B[0m"

static int
doubles_are_close(double x, double y, double tol)
{
   return fabs(x - y) > fabs(tol) ? 0 : 1;
}

static int
doubles_are_equal(double x, double y)
{
   return doubles_are_close(x, y, 2 * DBL_EPSILON);
}

static int
files_are_equal(char *fn1, char *fn2)
{
   FILE     *in1 = fopen(fn1, "r");
   FILE     *in2 = fopen(fn2, "r");
   int       rc = 0;

   if (NULL == in1) {
      if (NULL != in2)
         fclose(in2);
   }

   else if (NULL == in2)
      fclose(in1);

   else {
      for (;;) {
         int       c1 = fgetc(in1);
         int       c2 = fgetc(in2);

         if (c1 != c2)
            goto DONE;

         if (EOF == c1)
            break;
      }

      rc = 1;

    DONE:

      fclose(in1);
      fclose(in2);
   }

   return rc;
}

static void
fprintf_test_info(FILE *out, char *name, const char *info)
{
   fprintf(out, TH_COLOR_YELLOW "%s" TH_COLOR_RESET, name);

   if (NULL != info)
      printf(" [%s]", info);

   printf("\n");
}

#define ASSERT_DOUBLE_EQUALS(expected, actual) ASSERT((#actual), 1 == doubles_are_equal((expected), (actual)))
#define ASSERT_DOUBLE_CLOSE(expected, actual, tol) ASSERT((#actual), 1 == doubles_are_close((expected), (actual), (tol)))
#define ASSERT_FILE_EQUALS(expected, actual) ASSERT((#actual " and " #expected), 1 == files_are_equal((expected), (actual)))

#endif
