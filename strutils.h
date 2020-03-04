/**
 *  @file strutils.h
 *  @version 0.1.0-dev0
 *  @date Sun Feb 16, 2020 05:15:23 PM CST
 *  @copyright 2018-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 *  @brief Provides a number of string handling helpers.
 *  @details FIXME
 */

#ifndef STRUTILS_H
#define STRUTILS_H

/**
 *  @brief Check for null termination of a character array.
 *  @details Check the first n characters of the memory following cp for
 *  the presence of a null-terminator.
 *  @param[in] cp Pointer to character array.
 *  @param[in] n Number of characters to check.
 *  @returns 0 if no terminator is found, 1 otherwise.
 */
int       stru_check(const char *cp, size_t n);

/**
 *  @brief Remove trailing newlines from a string.
 *  @details In-place removal of trailing newlines from a string, mimicking
 *  Perl's chomp(). cp will be modified.
 *  @param[in,out] cp Pointer to string.
 *  @returns
 */
char     *stru_chomp(char *cp);

/**
 *  @brief Remove all whitespace from a string.
 *  @details In-place removal of all whitespace from a string.
 */
char     *stru_crush(char *cp);

/**
 *  @brief Duplicate a string.
 *  @details Same as POSIX strdup(). Duplicates a string with malloc().
 *  Returns NULL if str is NULL or the malloc() fails.
 */
char     *stru_dup(const char *str);

/**
 *  @brief Test if a string is completely whitespace.
 *  @details Return 1 or 0, respectively, depending on whether or not a string
    is completely whitespace.
 */
unsigned  stru_isspace(char *str);

/**
 *  @brief Concatenate two strings.
 *  @details Replace str1 with the concatenation of two strings, str1 and str2.
 */
char     *stru_lcat(char **str1, char **str2);

/**
 *  @brief Split a string.
 *  @details Return a NULL-terminated list of strings obtained by splitting string
 *  str on the delimiter delim. Single- and double-quoted protection of delimiters
 *  is supported.
 */
char    **stru_split(char delim, char *str);

char    **stru_split_csv(char delim, char *str);
unsigned  stru_splitpp(char delim, char *str, char **list);

/**
 *  @brief Convert a string to lower-case.
 *  @details In-place conversion of a string to lower-case.
 */
char     *stru_tolower(char *cp);

/**
 *  @brief Convert a string to upper-case.
 *  @details In-place conversion of a string to upper-case.
 */
char     *stru_toupper(char *cp);

/**
 *  @brief Remove leading and trailing whitespace.
 *  @details In-place removal of leading and trailing whitespace
 *  from a string.
 */
char     *stru_trim(char *cp);

/**
 *  @brief Return the version string.
 *  @details Return the version of the strutils package.
 */
const char *stru_version(void);

/**
 *  TODO
 */

void      stru_wordize(FILE *fh);

/**
 *  @brief Split a string on whitespace.
 *  @details Return a list of strings obtained by splitting
 *  a string on whitespace; leading whitespace, if present,
 *  is ignored.
 */
char    **stru_wssplit(char *s);

#endif
