#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))
#define MAXWORD 100
#define BUFSIZE 100

struct key 
{
	char *word;
	int count;
} keytab[] = {
		"auto", 0, "break", 0, "case", 0, "char", 0,
              	"const", 0, "continue", 0, "default", 0, "do", 0,
           	"double", 0, "else", 0, "enum", 0, "extern", 0,
              	"float", 0, "for", 0, "goto", 0, "if", 0,
              	"int", 0, "long", 0, "register", 0, "return", 0,
              	"short", 0, "signed", 0, "sizeof", 0, "static", 0,
              	"struct", 0, "switch", 0, "typedef", 0, "union", 0,
              	"unsigned", 0, "void", 0, "volatite", 0, "while", 0
             };
      
int getword(char *, int);
int binary_search(char *, struct key *, int);
void ungetch(int);
int getch(void);

char buf[BUFSIZE];
int buffer_pointer = 0;

void main(int argc, char *argv[])
{
	int n;
	char word[MAXWORD];
	
	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			if((n = binary_search(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for(n = 0; n < NKEYS; n++)
		if(keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
}

int binary_search(char *word, struct key keytab[], int n)
{
	int cond;
	int low, high, mid;
	
	low = 0;
	high = n- 1;
	
	while(low <= high)
	{
		mid  = (low + high) / 2;
		if((cond = strcmp(word, keytab[mid].word)) < 0)
			high = mid - 1;
		else if(cond > 0)
			low = mid + 1;
		else
			return mid;
			
	}
	
	return -1;
}

int getword(char *word, int lim)
{
	int c, t;
	char *w = word;
	
	while (isspace(c = getch()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) 
    {
        if (c == '\"') 
        { 
            for (c = getch(); c != '\"'; c = getch());//string constant
        } 
        else if (c == '#') //preprocessor
        { 
            for (c = getch(); c != '\n'; c = getch());
        } 
        else if (c == '/')            
            if ((c = getch()) == '/') //single line comment
            { 
                for (c = getch(); c != '\n'; c = getch());
            } 
            else if (c == '*')    //multi line comment
            {    
                for (c = getch(), t = getch(); c != '*' && t != '/'; c = getch(), t = getch())
                    ungetch(t);
            } 
            else
                ungetch(c);
        else 
            for (; !isspace(c) && c != EOF; c = getch());
        if (c != '\"' && c != '\n' && c != '/')
            ungetch(c);
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            if (!isspace(*w)) {
                ungetch(*w);
                return (*w);
            } else {
                ungetch(*w);
                break;
            }
        }
    *w = '\0';
    return word[0];
}
	
	
				

              	     
int getch(void) 
{
	return (buffer_pointer > 0) ? buf[--buffer_pointer] : getchar(); 
}

void ungetch(int c) 
{
    if (buffer_pointer >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[buffer_pointer++] = c;
}
