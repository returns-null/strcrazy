#include "strcrazy.h"

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

// Creates and initializes a new string big enough to hold len intended
// characters, plus the null-terminator, which it drops into memory.
char * strbless(int len)
{
    char* strp = (char *) malloc(len+1);
    *strp = '\0';
    *(strp+len) = '\0';
    return strp;
}

// Creates a clone copy of the supplied string, which is mandatory
// when working with string literals on some compilers and platforms
// which cause awfully inconsistent behavior or faults when attempting
// to modify them, as some strtok's seem to do.
char * strrogate(char * s)
{
    char * news = strbless(strlen(s));
    strcpy(news, s);
    return news;
}

// Creates a singleton string out of a lone character,
// since a cast won't do.
char * charstr(char c)
{
    char * ns = strbless(1);
    ns[0] = c;
    return ns;
}

// Attempts to free a pointer which hopefully still points
// to one allocated by malloc. If we know the pointer has
// travelled so many bytes beyond the original block beginning
// we can supply that number as the distwok'd.
char * strfri(char * sesame, int distwok)
{
    free(sesame+(-distwok));
    return sesame;
}

// Because working with the alphabet is a fairly common task
// often accomplished with explicit array literals at the head,
// of the source file, strabc takes a request for one
// of several meaningful ASCII spans and shoots back a 
// string containing it that can be thoroughly munged or
// used for trivial encoding and decoding.
char * strabc(int mode)
{
    char * news;
    int start, end, span, iter;

   
   switch (mode)
   {
      case STRABC_UPPERCASE: start = 65; end = 90; span = 26; break;
      case STRABC_LOWERCASE: start = 97; end = 122; span = 26; break;
      case STRABC_DIGITS: start = 48; end = 57; span = 10; break;
      case STRABC_PANASCII: start = 1; end = 255; span = 255; break;
      case STRABC_PRINTASCII: start = 32; end = 126; span = 95; break;
   }

    news = strbless(span);

    int pos = 0;
    for (iter = start; iter <= end; iter++,pos++)
    {
        news[pos] = iter;
    }

    return news;

}

// Returns whether a string starts with a certain subsequence or not.
int strstrts(char * s, char * b)
{
    int i;
    for(i=0; i<strlen(b)&&i<strlen(s); i++)
        if (s[i]!=b[i]) return 0;
    return 1;
}

// Since getline() is used in so many projects and is merely POSIX
// and not always in standard libraries, this version can grab BUFSIZE
// characters or up to a newline from the stdout if that's the file
// handle chosen.
char * strgetline(int BUFSIZE, FILE * f)
{
    char c;
    int i;

    if (!f) f = stdin;

    i = 0;
    char * buffa = (char*) malloc(BUFSIZE + 1);
    while (((c = fgetc(f)) != '\n') && c != EOF && i < BUFSIZE)
    {
        buffa[i++] = c;
    }

    buffa[i] = '\0';

    return buffa;

}

// Counts how many instances of the substring exist within the string.
int substrcnt(char * s, char * bad)
{
    char * spumoni = s;
    int cnt = 0;

    do
    {
        spumoni = strstr(spumoni, bad);
        if (spumoni != NULL)
        {
            spumoni += strlen(bad);
            cnt++;
        }
    }
    while (spumoni != NULL);

    return cnt;
}

// Returns whether the whole string is alphanumeric.
// Since spaces are so common it also counts them as alphanumeric.
// Future versions may either not include them or include all whitespace.
int isstralnum(char * s)
{
    for (; *s!=0; s++)
    {
        if (!isalnum(*s) && *s != ' ')
        {
            return 0;
        }
    }

    return 1;
}

// Returns an all uppercase copy of a string.
char * strupp(char * s)
{
    char * news = strrogate(s);
    int i;
    for (i=0; i<strlen(s); i++)
        news[i] = toupper(news[i]);
    return news;
}

// Returns an all lowercase copy of a string.
char * strlow(char * s)
{
    char * news = strrogate(s);
    int i;
    for (i=0; i<strlen(s); i++)
        news[i] = tolower(news[i]);
    return news;
}

// Counts the number of instances of a specific character in a string.
int strccnt(char * s, char ch)
{
    int c,i;
    c = 0;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == ch)
            c++;
    }

    return c;
}

// Counts the number of instances of a number of characters in a string.
int strcany(char * s, char * filter)
{
    int i, c;
    c = 0;
    for (i=0; i<strlen(filter); i++)
    {
        c += strccnt(s, filter[i]);
    }

    return c;
}

// Attempts to count the "words" in a string, as separated by whitespace.
int strworc(char * s)
{
    int b, wc;
    wc = 0;
    while (*s != 0)
    {
        if (isspace(*s))
            b = 0;
        else
        {
            if (!b||wc<1)
            {
                b=1;
                wc++;
            }
        }
        s++;
    }
    return wc;
}


// Takes a group of of characters to strip out
// of a new copy of a supplied string.
char * strpclb(char * str, char * charclub)
{
    int ls, lcc;
    ls = strlen(str);
    lcc = strcany(str,charclub);
    char * news = strbless(ls-lcc);

    int i,prog,r,am;

    i=prog=r=am = 0;

    for (i = 0; i < ls; i++)
    {
        am = 1;
        for (r = 0; r < strlen(charclub); r++)
        {
            if (str[i] == charclub[r])
            {
                am = 0;
            }
        }
        if (am == 1)
        {
            news[prog] = str[i];
            prog++;
        }
        news[prog] = '\0';

    }
    return news;
}

// Computes the popular Levenshtein Edit Distance metric between two strings,
// defined as the number of additions, deletions, or transcriptions required
// to mutate one of the strings into the other, provided for RYO fuzzy matching.
int strshtein(char * sa, char * sb)
{
    int la,b,i,j,cst;
    int dl,dr,mdldr,cstplus;

    la = strlen(sa);
    b = strlen(sb);

    if (!la) return b;
    if(!b) return la;

    int mat[la+1][b+1];

    for (i = 0; i <= la; mat[i][0] = i++);
    for (j = 0; j <= b;  mat[0][j] = j++);

    for (i = 1; i <= la; i++)
        for (j = 1; j <= b; j++)
        {
            cst = (sb[j - 1] == sa[i - 1]) ? 0 : 1;

            dl=      mat[i-1][j]+1;
            dr=      mat[i][j-1]+1;
            mdldr=   ((dl<dr)?dl:dr);
            cstplus= cst+mat[i-1][j-1];

            mat[i][j] = ((mdldr < cstplus) ? mdldr : cstplus);
        }

    return mat[la][b];

}

// Implements the famous classical Caesar rotation
// cipher on an arbitrary alphabet and shift.
// Of course, the only shift parameter you need is 13.
char * strcaesar(char * s, char * alpha, int shift)
{
    char * news = strbless(strlen(s));

    int i, j, k, b;
    k = strlen(alpha);

    for (i = 0; i < strlen(s); i++)
    {
        b=0;
        for (j = 0; j < k; j++)
        {
            if (s[i] == alpha[j])
            {

                int mod = (j+shift) % k;
                if (mod < 0)
                    mod = k - abs(mod);
                news[i] = alpha[mod];
                b = 1;
            }

        }
        if (!b)
            news[i] = s[i];

    }
    return news;
}

// Null terminates an existing string (lacking one, it isn't yet a string)
// at a desired number of characters from the pointer, ideally the known length.
int strterm(char * s, int endpos)
{
    s[endpos] = '\0';
}

// Takes a boolean (0 or nonzero) and what to print if true or false,
// and passes a pointer to the corresponding string for display
// ex: Yes/No True/False
char * struth(int truth, char * onTrue, char * onFalse)
{
    return (truth) ? onTrue:onFalse;
}

// Joins two strings, a and b together in that order.
// No lists are yet involved.
char * strcons(char*a, char*b)
{
    char * ab = strbless(strlen(a) + strlen(b));

    strcat(ab, a);
    strcat(ab, b);
    strterm(ab, strlen(a)+strlen(b));

    return ab;
}

// Same as strcons, but after the strings are married,
// their individual "lives" are destroyed.
char * strmarry(char* hus, char* wif)
{
    char * huswifery = strbless(strlen(hus) + strlen(wif));

    strcat(huswifery, hus);
    strcat(huswifery, wif);
    strterm(huswifery, strlen(hus)+strlen(wif));

    strfri(hus,0);
    strfri(wif,0);

    return huswifery;
}

// Equivalent of indexOf() in many slightly more civilized languages,
// attempts to deliver the index of the search string in the first string.
// Delivers -1 upon failure. Compare with strstr() which gives a *pointer*
// to the same.
int strindex(char * str, char * srch)
{
    int i,l,m;
    int lenstr, lensrch;

    lenstr = strlen(str);
    lensrch = strlen(srch);
    l = -1; m = 0;

    for (i = 0; i < strlen(str); i++)
    {
        if (l >= 0 && m == strlen(srch)) return l;
        if (str[i] == srch[m])
        {
            if (l < 0) l = i;
            m++;
        }
        else
        {
            l = -1;
            m = 0;
        }
    }

    return -1;
}

// Splits a string using strtok, but places the results in an
// array of strings so that they can be used more easily and
// not at once.
char ** strsplode(char * str, char * filter)
{
    str = strclone(str);
    int thmsdbrks = strcany(str,filter);

    char ** strdex = (char**) malloc(thmsdbrks+2);

    int index;
    char * pch = strtok(str,filter);

    index = 0;
    while (pch != NULL)
    {
        strdex[index] = pch;
        pch = strtok (NULL,filter);
        index++;
    }

    strdex[index] = 0;

    return strdex;
}

// Equivalent of substring in many languages, makes a string copy
// of a sequence of length characters from an index, start.
char * substr(char * s, int start, int length)
{
    char* news = strbless(length+1);

    int i;
    for (i = 0; i < length; i++)
    {
        news[i] = s[start+i];
    }

    news[i] = '\0';

    return news;
}

// Provides a copy of the string in which whitespace is trimmed
// from the left side (mode -1), right (1), or both sides (0).
char * strtrim(char * s, int mode)
{
   int i,b,m;

   int l;
   l = strlen(s);

   for (i = 0; i < l && isspace(s[i]); i++);         b = i;
   for (i = l-1; i >= 0 && isspace(s[i]); i--);      m = i-1;

   if (mode > 0)
     { b = 0; m = i+1; }
   else if (mode < 0)
      m = l - 1;

   char * news = strbless((m-b));
   news = substr(s,b,m);

   return news;

}

// Makes a string copy of joining three strings at once,
// wherein the middle string is sandwiched between
// the first and third argument, useful primarily for
// very simple HTML tags.
char * strwich(char* bread, char* meat, char* bread2)
{
    char * news = (char *) malloc( strlen(bread)+
                                   strlen(meat)
                                   + strlen(bread2) );
    *news = 0;

    news = strcons(news, bread);
    news = strcons(news, meat);
    news = strcons(news, bread2);

    return news;
}

// Attempts to wrap a long string to the desired number of
// characters returning each line in an array to aid formatting and decoration.
char ** strwrap(char * sp, int chars)
{
    char * s = strclone(sp);

    int sl = strlen(s);
    int approxlines = sl / chars;
    char** strdex = (char**) malloc(approxlines*5);

    int lastgappos;  int lineprog; int lastbeg;
    lastgappos = lineprog = lastbeg = 0;

    int i,p;
    p = 0;
    for (i=0; i<sl; i++)
    {
        if (isspace(s[i]) || (i - lastgappos) >= chars)
           lastgappos = i;

       if (lineprog >= chars)
       {
           strdex[p++] = substr(s, lastbeg, lastgappos - lastbeg);
           lineprog = 0;
           i = lastgappos;
           lastbeg = i;
       }

       lineprog++;
    }
    strdex[p] = substr(s, lastbeg, sl-lastbeg);
       strdex[p+1] = 0;
    return strdex;

}

// Provides a string made of the desired number of a character.
char * strburst(char c, int n)
{
    char * news = strbless(n);
    int i;
    for (i = 0; i < n; i++)
        news[i] = c;
    news[i] = '\0';
    return news;
}

// Creates a string that is padded either left or right
// to a specified length with characters from another
// string. 0 specifies left padding, 1 right.
char * strpad(char * s, char * p, int tolen, int dir)
{
   char * pads = strbless(tolen);
   int dif = tolen - strlen(s);

   int i,lp;
   lp = strlen(p);
   if (dif > 0)
   {
      for (i = 0; i < dif; i++)
          pads[i] = p[i%lp];
   }

   pads[i] = '\0';

   char * news;

   news = dir ? strcons(s, pads) : strcons(pads,s);

   return news;
}

// Supplies a reversed copy of the string.
char * strrev(char * s)
{
    int i;
    int l = strlen(s);
    char * news = (char *) malloc(l);

    for (i = 0; i < l; i++)
    {
        news[i] = s[l-(i+1)];
    }

    strterm(news,l);

    return news;
}

// Provides a jumbled copy of a string by
// "randomly" switching its letters a certain
// number of times. If that number is negative,
// it performs an exchange for every character.
// It is very wise to call srand first.
char * strcrazy(char * s, int erupts)
{
    erupts= (erupts < 0)
            ? strlen(s)
            : erupts;

    int a,b;
    int l_ess = strlen(s);

    char * news = strbless(l_ess);
    strcpy(news, s);

    int i;
    for (i = 0; i < erupts; i++)
    {

        a = rand()%l_ess;
        b = rand()%l_ess;

        char tmp;

        tmp = news[a];
        news[a] = news[b];
        news[b] = tmp;

    }

    return news;

}

// Returns true only if every character in the string is printable.
int isstrprint(char * s)
{
    for (; *s!=0; s++)
        if (!isprint(*s))
            return 0;

    return 1;
}

// String equality shortcut.
int streql(char * a, char * b)
{
    return (strcmp(a,b) == 0) ? 1 : 0;
}

// The c-quel to isstrwql, it is "case-insensitive".
int strceql(char * a, char * b)
{
    char * la, *lb;

    la = strlow(a);
    lb = strlow(b);

    int truth = (strcmp(la,lb) == 0) ? 1 : 0;

    strfri(la,0);
    strfri(lb,0);

    return truth;
}

// Returns a copy of the supplied string with
// the "bad" substring replaced with the "good".
char * strrep(char * s, char * bad, char * good)
{
    char * spumoni = s;

    int occ = substrcnt(s, bad);
    int needful = strlen(s) + ((strlen(good) - strlen(bad)) * occ);

    char * dest = (char *) malloc(needful);
    *dest = '\0';

    if (occ < 1)
        return s;
    else
    {
        while (occ--> 0)
        {
            char * spoilmoni = spumoni;

            spumoni = strstr(spumoni, bad);

            if (spumoni != NULL)
            {
                spumoni += strlen(bad);

                strncat(dest, spoilmoni , spumoni - spoilmoni - strlen(bad));
                strcat(dest, good);
            }

        }

        if (spumoni != s + strlen(s))
        {
            strcat(dest, spumoni);
        }
    }
    return dest;
}


int isvowel(char c)
{
   char * vowels = "AEIOU";
   char lc = toupper(c);
   int i;
   for (i=0;i<5;i++)
       if (vowels[i] == c)
          return true;
   return false;
}

// A faster (in the long run) version of strindex(),
// implementing the Knuth-Morris-Pratt algorithm,
// which retains information after compares so it can just skip
// some clearly impossible matches.
int strkmp(char * s, char * ss)
{
   int m,fj,fi;

   m = strlen(ss);

   int failmat[m];

   failmat[0] = 0;
   fj = 0;
   fi = 1;

   while (fi < m)
         if (ss[fj] == ss[fi])
         {
            failmat[fi] = fj + 1;
            fi++; fj++;
         }
         else if (fj > 0)
              fj = failmat[fj - 1];
         else {
             failmat[fi] = 0;
             fi++; }

   int i,j,n;

   i = j = 0;
   n = strlen(s);

   while (i < n)
         if (s[i] == ss[j])
         {
            if (j == m-1)
               return i-m+1;
            i++;
            j++;
         }
         else if (j >= 1)
              j = failmat[j - 1];
         else
             i++;

    return -1;
}

// Computes the SOUNDEX value of a string, a phonetic encoding
// historically used by the US Census to detect soundalike names.
char * strsound(char * c)
{
    char * code = "BFPVCGJKQSXZDTLMNR";
    char * code2= "111122222222334556";
    char * SOUNDEX = strbless(4);

    int i,l,s,p;
    int z,cl;

    cl = strlen(code);
    s = 0;
    p = 1;

    SOUNDEX[0]= c[0]; SOUNDEX[1] = '0'; SOUNDEX[2] = '0'; SOUNDEX[3] = '0';

    l = strlen(c);
    c = strupp(c);

    int b; int lcode; int theban;
    for (i = 1; i<l; lcode=0,b=0,i++)
    { if (theban) {b = 1; theban = 0;}
       for (z = 0; z < cl; z++)
       {
           if (code[z] == c[i])
           {
               lcode = code2[z];
               if ((i+1)<l)
               {
                   if (c[i] == c[i+1])
                   {b = 1;}
                   else
                   {
                   int lki;   int s2;
                   for (lki=0;lki<cl;lki++)
                       if (code[lki] == c[i+1])
                           s2 = code2[lki];

                   if (code2[z] == s2)
                    {
                         theban = 1;
                    }
                   }
               }

               if ((i+2)<l)
               {
                     int lki;   int s2;
                   for (lki=0;lki<cl;lki++)
                       if (code[lki] == c[i+2])
                           s2 = code2[lki];

                   if (code2[z] == s2 && isvowel(c[i+1]))
                      b = 1;

                   if (code2[z] == s2 && (c[i+1]=='H'||c[i+1]=='W'))
                     { b = 1;    }

               }

             break;
           }

       }
       if (!b && lcode)
       {

       SOUNDEX[p] = lcode;
       p++;
       if (p > 3) break;
       }

    }
    SOUNDEX[4] = '\0';
    return SOUNDEX;
}

