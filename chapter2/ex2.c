#include<stdio.h>
#define maximum_limit 10
/*for(i=0; i < lim -1 && (c=getchar()) != '\n' && c != EOF; ++i)
  s[i] = c;
  
  Equivalent of this without using && or ||
*/
void main()
{
	int character, i = 0;
	char s[1000];
	while((character = getchar())!= EOF)
	{
	   if(i >= maximum_limit - 1)
	      break;
	      
	   if(character == '\n')
	      break;
	   
	   s[i] = character;
	   i++;
	}

printf("%s", s);
}
