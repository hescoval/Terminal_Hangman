
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define clear() printf("\033[H\033[J")

void printhang(char *s, char *used, int errors)
{
	printf("________\n");
	printf("|       |\n");
	printf("|       ");
	if(errors > 0)
	{
		printf("O");
	}
	printf("\n");
	printf("|      ");
	if(errors<4)
	{
		switch (errors)
		{
			case 2:
			{
				printf(" |");
				break;
			}
			case 3:
			{
				printf("/|");
				break;
			}
		}
	}
	else
		printf("/|\\");
	printf("\n");
	printf("|      ");
	if(errors == 5)
		printf("/");
	else if(errors == 6)
		printf("/\\");
	printf("\n");
	printf("|\n");
	printf("|__________\n\n");

	for(int i = 0; s[i]; i++)
	{
		int found = 0;
		for(int j = 0; used[j]; j++)
		{
			if(s[i] == used[j])
			{
				printf("%c",s[i]);
				found = 1;
				break;
			}
		}
		if(!found)
			printf("_");
		printf(" ");
	}
	printf("\n\n");

	if(errors < 6)
	{
		printf("You have used these letters so far\n");
		for(int i = 0; used[i]; i++)
		{
			if(used[i] == '!')
				break;
			printf(" |%c| ", used[i]);
		}
	}
	else
		printf("You died :(\n\n The word was %s", s);
}

int checknew(char *s, char x)
{
	for(int i = 0; s[i]; i++)
	{
		if(s[i] == '!')
			return 1;
		if(s[i] == x)
			return 0;
	}
	return 1;
}

int check(char *s)
{
	for(int i = 0; s[i]; i++)
	{
		if(!isalpha(s[i]))
		{
			return 0;
		}
	}
	return 1;
}

void playhangman(char *s)
{
	int len = strlen(s);
	char letused[26];
	int errors = 0;
	char test[999];
	char input = '0';
	int guessed = 0;
	int attempts = 0;

	if(!check(s))
	{
		printf("Letters only in your word please!\n");
		return;
	}

	for(int i = 0; i<26; i++)
		letused[i] = '!';

	while(errors != 6 && guessed != strlen(s))
	{
		printf("Pick a new letter to check!\n");
		scanf(" %s", test);
		int correct = 0;
		input = test[0];

		if(checknew(letused, input))
		{
			letused[attempts] = input;
			attempts++;
		}
		else 
		{
			printf("Youve already picked this letter!\n");
			continue;
		}

		for(int i = 0; s[i]; i++)
		{
			if(input == s[i])
			{
				guessed ++;
				correct = 1;
			}
		}

		if(!correct)
		{
			errors++;	
		}

		printhang(s, letused, errors);
		if(guessed == strlen(s))
			printf("\nGood job, you got it!");
	}
}

int main(int ac, char **av)
{
	clear();
	if(ac == 2)
	{
		printf("You are playing Hangman!\n\nThe word youre guessing is %ld letters long \n\n",strlen(av[1]));
		for(int i = 0; i < strlen(av[1]); i++)
			av[1][i] = tolower(av[1][i]);
		playhangman(av[1]);
	}
	else
		printf("Please enter a single word");
	return 0;
}
