#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define LOWER_CHAR		' '
#define UPPER_CHAR		'~'
#define LOWER_STR_CHAR	'a'
#define UPPER_STR_CHAR	'z'

#define MAX_TEST_TIME	5

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

  time_t startTime;
  time_t currentTime;
  time_t elapsedTime;
  time_t endTime;

  struct tm* timeinfo;

  time(&startTime);
  time(&currentTime);
  endTime = startTime + MAX_TEST_TIME * 60;

  while (currentTime < endTime)
  {
  	time(&currentTime);
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
      // printf("\nIteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

      elapsedTime = currentTime - startTime;
      timeinfo = localtime(&elapsedTime);
      printf("Execution took %d minutes and %d seconds to complete.\n", timeinfo->tm_min, timeinfo->tm_sec);

      printf("error ");
      exit(200);
    }
  }
  printf("Test exceeded the max time of %d minute. Aborting test.\n", MAX_TEST_TIME);
  exit(100);
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
