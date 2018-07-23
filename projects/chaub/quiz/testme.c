#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>

// This function random return a character with
// ascii code value from 32 (space character) to 125 ('}' character)
char inputChar()
{
	int low_char = 32;		// the space character in the ascii table
	int high_char = 125;	// the '}' character in the ascii table
	int range;	

	range = (high_char - low_char) + 1;
	return (int)floor(rand() % range) + low_char;
}

// This function returns a string of 5 characters with the 
// characters randomly selected from a set of 10 different characters.
char *inputString()
{

	char source[] = "abcderstuv";
	char *str = malloc(6 * sizeof(char));
	int i, index;

	for (i = 0; i < 5; i++) {
		index = (int)floor(rand() % 10);
		str[i] = source[index];
	}

	str[5] = '\0';
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
      printf("error \n");
      exit(200);
    }
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    
    return 0;
}
