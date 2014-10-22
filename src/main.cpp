#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
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
	char user[50];
	if(usrname !=NULL)
	{
		perror("username noame error");
	}
	while(1){
		host= new char[30];
		if( gethostname(host,30)==-1)
		{
			perror("gethostname");
		}
		cout<<usrname<<"@"<<host<<" $ ";
		delete []host;
		int  arg;
		cin.getline(user,50);
		pch=strtok(user," ");
		if(strcmp(pch,"exit")==0)
		{
			exit(1);
		}
		for(unsigned i=0;i<100;i++)
	                {
  	       		argv[i]=new char[100];
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
					cout<<"inside"<<endl;
					if(execvp(argv[0],argv)==-1)
					{
					}
					else
					{
					}
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
							exit(1);
						}
					}
				}
				else
				{
					strcpy(argv[i],pch);
					pch=strtok(NULL," ");
					arg=i;
				}
			}
			arg++;
			cout<<arg<<endl;
			argv[arg]=NULL;
			if( execvp(argv[0],argv)==-1)
			{
				perror("invalid command");
			}
		}
		else if (pid <0)
		{
			perror("fork function failed");
		}
		else
		{
			wait(0);
		}
		cout<<"end"<<endl;
		for(int i=0;i<100;i++)
		{
			delete argv[i];
		}
	}
}
