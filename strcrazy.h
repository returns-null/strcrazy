#ifndef _STRCRAZY_H_
#define	_STRCRAZY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

//***********************************************************************
///////////////////////////////////////////////////////////////   *
//   <strcrazy.h>                                            //     *
//   THE BOSTON STRINGgler C-String Slicin N' Dicin Library  //    *
//   Copyright 2012 Andrew Burton                            //   *
//   ------------------------                                //     *
//   Use with caution!                                       //    *
//   (licensed under the RPL3v1)                             //   *
//                                                           //     *                                               //     *
//   -------------------------                               //    *
//   v. 0.01                                                 //   *
//                                                           //     *
///////////////////////////////////////////////////////////////    *
//***********************************************************************

#define returns_null(x)        x==NULL

#define verrts(s)              strrev(s)
#define strsalad(x,y,z)        strcaesar(x,y,z)
#define strfilip(x,y)          strburst(y,strlen(x))
#define strrot(s,c,a)          strcaesar(c,a,s)
#define bool2str(c,t,f)        struth(c,t,f)
#define strclone(s)            strrogate(s)

#define OVER_9000              9001
#define INSENSIBLE_BUFFER_SIZE OVER_9000

#define STRABC_LOWERCASE       26
#define STRABC_UPPERCASE       52
#define STRABC_DIGITS          10
#define STRABC_PANASCII        255
#define STRABC_PRINTASCII      95

// Creates and initializes a new string big enough to hold len intended
// characters, plus the null-terminator, which it drops into memory.
char * strbless(int len);

// Creates a clone copy of the supplied string, which is mandatory
// when working with string literals on some compilers and platforms
// which cause awfully inconsistent behavior or faults when attempting
// to modify them, as some strtok's seem to do.
char * strrogate(char * s);

// Creates a singleton string out of a lone character,
// since a cast won't do.
char * charstr(char c);

// Attempts to free a pointer which hopefully still points
// to one allocated by malloc. If we know the pointer has
// travelled so many bytes beyond the original block beginning
// we can supply that number as the distwok'd.
char * strfri(char * sesame, int distwok);

// Because working with the alphabet is a fairly common task
// often accomplished with explicit array literals at the head,
// of the source file, strabc takes a request for one
// of several meaningful ASCII spans and shoots back a 
// string containing it that can be thoroughly munged or
// used for trivial encoding and decoding.
char * strabc(int mode);


// Returns whether a string starts with a certain subsequence or not.
int strstrts(char * s, char * b);

// Since getline() is used in so many projects and is merely POSIX
// and not always in standard libraries, this version can grab BUFSIZE
// characters or up to a newline from the stdout if that's the file
// handle chosen.
char * strgetline(int BUFSIZE, FILE * f);

// Counts how many instances of the substring exist within the string.
int substrcnt(char * s, char * bad);


// Returns whether the whole string is alphanumeric.
// Since spaces are so common it also counts them as alphanumeric.
// Future versions may either not include them or include all whitespace.
int isstralnum(char * s);

// Returns an all uppercase copy of a string.
char * strupp(char * s);

// Returns an all lowercase copy of a string.
char * strlow(char * s);

// Counts the number of instances of a specific character in a string.
int strccnt(char * s, char ch);

// Counts the number of instances of a number of characters in a string.
int strcany(char * s, char * filter);


// Attempts to count the "words" in a string, as separated by whitespace.
int strworc(char * s);

// Takes a group of of characters to strip out
// of a new copy of a supplied string.
char * strpclb(char * str, char * charclub);

// Computes the popular Levenshtein Edit Distance metric between two strings,
// defined as the number of additions, deletions, or transcriptions required
// to mutate one of the strings into the other, provided for RYO fuzzy matching.
int strshtein(char * sa, char * sb);

// Implements the famous classical Caesar rotation
// cipher on an arbitrary alphabet and shift.
// Of course, the only shift parameter you need is 13.
char * strcaesar(char * s, char * alpha, int shift);

// Null terminates an existing string (lacking one, it isn't yet a string)
// at a desired number of characters from the pointer, ideally the known length.
int strterm(char * s, int endpos);


// Takes a boolean (0 or nonzero) and what to print if true or false,
// and passes a pointer to the corresponding string for display
// ex: Yes/No True/False
char * struth(int truth, char * onTrue, char * onFalse);

// Joins two strings, a and b together in that order.
// Worry not, no lists are yet involved.
char * strcons(char*a, char*b);

// Same as strcons, but after the strings are married,
// their individual "lives" are destroyed.
char * strmarry(char* hus, char* wif);

// Equivalent of indexOf() in many slightly more civilized languages,
// attempts to deliver the index of the search string in the first string.
// Delivers -1 upon failure. Compare with strstr() which gives a *pointer*
// to the same.
int strindex(char * str, char * srch);

// Splits a string using strtok, but places the results in an
// array of strings so that they can be used more easily and
// not at once.
char ** strsplode(char * str, char * filter);

// Equivalent of substring in many languages, makes a string copy
// of a sequence of length characters from an index, start.
char * substr(char * s, int start, int length);

// Provides a copy of the string in which whitespace is trimmed
// from the left side (mode -1), right (1), or both sides (0).
char * strtrim(char * s, int mode);

// Makes a string copy of joining three strings at once,
// wherein the middle string is sandwiched between
// the first and third argument, useful primarily for
// very simple HTML tags.
char * strwich(char* bread, char* meat, char* bread2);

// Attempts to wrap a long string to the desired number of
// characters returning each line in an array to aid formatting and decoration.
char ** strwrap(char * sp, int chars);

// Provides a string made of the desired number of a character.
char * strburst(char c, int n);

// Creates a string that is padded either left or right
// to a specified length with characters from another
// string. 0 specifies left padding, 1 right.
char * strpad(char * s, char * p, int tolen, int dir);

// Supplies a reversed copy of the string.
char * strrev(char * s);

// Provides a jumbled copy of a string by
// "randomly" switching its letters a certain
// number of times. If that number is negative,
// it performs an exchange for every character.
// It is very wise to call srand first.
char * strcrazy(char * s, int erupts);

// Returns true only if every character in the string is printable.
int isstrprint(char * s);

// String equality shortcut.
int streql(char * a, char * b);

// The c-quel to isstrwql, it is "case-insensitive".
int strceql(char * a, char * b);

// Returns a copy of the supplied string with
// the "bad" substring replaced with the "good".
char * strrep(char * s, char * bad, char * good);

// Returns non-zero if a vowel (AEIOU, no Y's allowed!)
int isvowel(char c);

// A faster (in the long run) version of strindex(),
// implementing the Knuth-Morris-Pratt algorithm,
// which retains information after compares so it can just skip
// some clearly impossible matches.
int strkmp(char * s, char * ss);

// Computes the SOUNDEX value of a string, a phonetic encoding
// historically used by the US Census to detect soundalike names.
// Planned: strroundsound(), a function to compute SOUNDEX for each word in a string.
char * strsound(char * c);

#endif
