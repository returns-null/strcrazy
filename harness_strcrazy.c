#include <assert.h>
#include <stdio.h>
#include "string.h"

// Try to confuse with multiple includes.
#include "strcrazy.h"
#include "strcrazy.h"

int main()
{
   char * stringLiteral = "S. Literal";

   printf("STRCRAZY Cheapo Test Harness\n");

   // The inclusion of this library shall not have caused the demise of arithmetic.
   assert(2+2==4);
   assert(0!=1);

   // The newly-blessed string will soon be (null)terminated.
   assert(strbless(4)[4]==0);

   // The address of a copy of a string shall not be
   // the address of the string itself.
   assert(strrogate(stringLiteral)!=stringLiteral);

   // The first character of a single-character string should be that character.
   assert(charstr('!')[0]=='!');

   // With regard to opportunities to be insensitively compared,
   // The alphabet shall not discriminate on the basis of case, case, or case.
   assert(strceql(strabc(STRABC_UPPERCASE), strabc(STRABC_LOWERCASE)));

   // The strings that begin together, begin together.
   assert(strstrts("Begin at the beginning, the king said gravely", "Begin"));

   // Unless of course you pay me...
   char * myDemands = strwich("$",strpad("1000000","0",12,1),".00");
   assert(streql(myDemands, "$100000000000.00"));

   // Some assembly required.
   printf("\nFor some reason the test suite has stopped!");
   printf("\nYou've got to ___ it, ___ it.\n");
   assert(strceql(strgetline(OVER_9000, stdin),"MOV"));

   // Harder than searching for a needle in a haystack:
   // searching for the number of needles in a haystack.
   char * hay = "HANEEDLESTANEEDLECK";
   assert(substrcnt(hay, "NEEDLE") == 2);

   // A feat not guaranteed: Two algorithms to accomplish the same thing do so.
   char * zonealarm = "The white zone is for loading and unloading only.";
   assert(strindex(zonealarm, "load") == strkmp(zonealarm, "load"));

   // The difference between ordinary and extraordinary is exactly 5.
   assert(strshtein("ordinary","extraordinary") == 5);

   // How can you tell an introvert from an extrovert in the US Senate?
   char * cipher = "Va gur onguebbz, gur rkgebireg gncf uvf sbbg va gur bgure thl'f fgnyy!";
   assert(strrot(13, strlow(cipher), strabc(STRABC_LOWERCASE))[0] == 'i');

   // Welcome to my ool!
   assert(strcany(strpclb("pool", "p"),"p") == 0);

   // The following sentence is a lie.
   assert(strworc("There are 6 words in this sentence.")==7);

   // "I'm sorry, Sheila, that you can't have that sheepshagger for breakfast!"
   assert(streql(struth(streql("brickie","brekkie"),"STREWTH!?", "STREWTH"),"STREWTH"));

   // Let's begin with some basic fundaments of the culinary arts.
   char * recipe = strwich("BREAD", "MEET", "BREAD");
   char * breadwich = strrep(recipe, "MEET", "");
   assert(strindex(breadwich, "MEET") == -1 && substrcnt(breadwich, "BREAD") == 2);

   char **shorterlines = strwrap("This line is longish, and shall be summarily wrapped", 20);
   int pdx = 0;
   while (shorterlines[pdx] != 0)
   {
         assert(strlen(shorterlines[pdx]) < 20);
         printf("%s\n", shorterlines[pdx++]);
   }

   // As huddling together is a necessity in these economic times.
   assert(streql(strmarry("carD","cdr"), "carDcdr"));

   assert(!streql(strcrazy("Wilder & Pryor", 1980), "Wilder & Pryor"));

   // Spoiler alert.
   assert(streql(verrts("REDRUM"), "MURDER"));

   // Courtesy of NARA:
   printf("%s",strsound("Ashcraft"));
   assert(strcmp(strsound("Ashcraft"), "A261") == 0);

   printf("%s",strsound("Gutierrez"));
   assert(strcmp(strsound("Gutierrez"), "G362") == 0);

   printf("%s",strsound("Jackson"));
   assert(strcmp(strsound("Jackson"), "J250") == 0);

   printf("%s",strsound("Tymczak"));
   assert(strcmp(strsound("Tymczak"), "T522") == 0);

   // Let's case dis-joint.
   assert(!streql("CASE","cAse") && strceql("CASE","cAse"));

   // Imagine four balls on the edge of a cliff.
   char * zybourne = strcons("Johnny ", strburst('A',5));

   // A, E, O, *U*, and *I* need to stick together on this one.
   assert(!isvowel('Y'));

   char * frag = strsplode("The second word is \"second\"!", " ")[1];
   assert(strcmp(frag, "second") == 0);

   // Say what you mean!
   char * swansong = "This is the end, beautiful friend.";
   swansong = strrogate(swansong);
   strterm(swansong, 15);
   assert(strlen(swansong) < 16);

   printf("\nAll tests passed.");

   getchar();
}
