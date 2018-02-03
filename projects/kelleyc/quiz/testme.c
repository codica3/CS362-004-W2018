/**********************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** testme.c
**
** Random Testing Quiz
**
** Obtain the required code coverage to get error message to print
** within 5 minutes or less.
**********************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//change NOISY_TEST to 1 to see all printfs
#define NOISY_TEST 0

char inputChar()
{
    // TODO: rewrite this function
    char array[9] = { ' ', '(', ')', '{', '}', '[', ']', 'a', 'x' };

    int r;

    r = rand() % 9;

#if (NOISY_TEST == 1)
printf("Random char selected: %c\n", array[r]);
#endif

    return array[r];
}

char *inputString()
{
    // TODO: rewrite this function
    char array[5] = { 'r', 'e', 's', 't', '\0' };

    int i, r;

    char s[6];

    for (i = 0; i < 6; ++i) {

	r = rand() % 5;

#if (NOISY_TEST == 1)
printf("Random char selected: %c\n", array[r]);
#endif

	s[i] = array[r];
    }

#if (NOISY_TEST == 1)
printf("Random string generated: %s\n", *s);
#endif

    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();

#if (NOISY_TEST == 1)
printf("inputChar functioning\n");
#endif

    s = inputString();

#if (NOISY_TEST == 1)
printf("inputString functioning\n");
#endif

    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
