#include <iostream>
#include <string.h>
using namespace std;

int main()
{
 char *argv[100];
 char *pch;
 char user[50];
 cout<<"$ ";
 cin.getline(user,50);
 pch=strtok(user," ");
 for(int i=0;pch != NULL;i++)
 {
   argv[i]=new char[100];
   strcpy(argv[i],pch);
   pch=strtok(NULL," ");
 }
 execvp(argv[0],argv);

}
