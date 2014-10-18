#include <iostream>
#include <unistd.h>
#include <string.h>
using namespace std;

int main()
{
 char *argv[100];
 char *pch;
 char *usrname= getlogin();
 char user[50];
 cout<<usrname<<"@"<<"$ ";
 cin.getline(user,50);
 pch=strtok(user," ");
 cout<<pch<<endl;
 for(int i=0;pch != NULL;i++)
 {
   if(strcmp(pch,"exit")==0)
   {
     exit(0);
   }
   argv[i]=new char[100];
   strcpy(argv[i],pch);
    cout<<i<<endl; 
   pch=strtok(NULL," ");
 }
  execvp(argv[0],argv);
 
  for(int i=0;i<100;i++)
  {
    delete argv[i];
  }
}
