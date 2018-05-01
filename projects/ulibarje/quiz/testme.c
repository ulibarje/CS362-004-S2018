#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define UPPER_CHAR		'~'
#define LOWER_CHAR		' '
#define UPPER_STR_CHAR	't'
#define LOWER_STR_CHAR	'e'

char inputChar()
{
    return (rand() % (UPPER_CHAR - LOWER_CHAR + 1)) + LOWER_CHAR;
}

char *inputString()
{
	char* str;
	str = calloc(6, sizeof(char));

	int i;
	for(i = 0; i < 5; i++) {
		str[i] = (rand() % (UPPER_STR_CHAR - LOWER_STR_CHAR + 1)) + LOWER_STR_CHAR;
	}

    return str;
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
    s = inputString();
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
