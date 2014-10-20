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
 char *host;
 int arg=0;
 int f2;
 char user[50];
 while(1){
 host= new char[30];     
 gethostname(host,30);
 cout<<usrname<<"@"<<host<<" $ ";
 delete []host;
 cin.getline(user,50);
 pch=strtok(user," ");
   if(strcmp(pch,"exit")==0)
   {
     exit(1);
   }
   int pid=fork();
   if(pid==0)
   {
      for(int i=0;pch !=NULL;i++)
      {
       if(strcmp(pch,"#")==0)
        {
         break; 
        }
      else if(strcmp(pch,"&&")==0)
       {
       }
      else if(strcmp(pch,"||")==0)
       {
           if(execvp(argv[0],argv)==-1)
            {
                for(int j=0;pch != NULL;j++)
                {
                  pch=strtok(NULL," ");
                  cout<<j<<endl;
                  strcpy(argv[j],pch);
                  cout<<argv[j]<<endl;
                  arg=j;
                  cout<<arg<<endl;
                }
            }
           }
       else
       {
       argv[i]=new char[100];
       strcpy(argv[i],pch);
       pch=strtok(NULL," ");
       arg=i;
       }
     }
    arg++;
    cout<<arg<<endl;
    argv[arg]=NULL;
    execvp(argv[0],argv);
   }
   else 
   {
    wait(0);
   }
   cout<<"end"<<endl;
 }}
