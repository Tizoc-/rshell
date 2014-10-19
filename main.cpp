#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
using namespace std;

int main()
{
 char *argv[100];
 char *pch;
 char *usrname= getlogin();
 int arg=0;
 char user[50];
 cout<<usrname<<"@"<<"$ ";
 cin.getline(user,50);
 pch=strtok(user," ");
 cout<<pch<<endl;
   if(strcmp(pch,"exit")==0)
   {
     exit(1);
   }
 int pid=fork();
 if(pid==0)
 {
   for(int i=0;pch !=NULL;i++)
   {
   argv[i]=new char[100];
   strcpy(argv[i],pch);
   pch=strtok(NULL," ");
   arg=i;
   }
   arg++;
   argv[arg]=NULL;
 execvp(argv[0],argv);
 }
 else 
 {
   wait(0);
   }
 }
