#include <stdio.h>
#include <stdbool.h>
#define MAX 100
#include "project2023a.h"
int main()
{
  int n=0,i,temp;
  struct hand A[MAX];

  char k,c;
  do
  {
    scanf(" %c",&k);
    switch (k)
    {
      case 'i': n = readFromInput(A);
                break;
      
      case 's': scanf ("%d",&i);
                if (i>=0 && i<n)
                  printHand(A[i]);
                printf ("\n");
                break;
      
      case 'r': scanf ("%d",&i);
                if (i>=0 && i<n)
                  response(A[i]);
                printf ("\n");
                break;
      case 'p': scanf ("%d",&i);
                if (i>=0 && i<n)
                {
                  temp = hcp(A[i]);
                  printf ("%d HCP (%d total)\n",temp,temp+declarer(A[i]));
                }
                printf ("\n");
                break;
      case 'd': scanf ("%d",&i);
                if (i>=0 && i<n)
                {
                  if (balanced(A[i]))
                    printf ("Balanced distribution\n");
                else
                    printf ("Unbalanced distribution\n");
                }
                printf ("\n");
                break;
      case 'f': n = readFromFile(A);
                break;
      case 'o': saveData(A,n);
                break; 
    }
  }
  while (k!='q');

  return 0;
}