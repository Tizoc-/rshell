#include <iostream>
#include <vector>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <string.h>
using namespace std;
int main()
{
    string usr;
    vector<string> arg;
    char *pch;
    char *host;
    char *pos;
    struct	passwd  *usrname= getpwuid(getuid());
    if(errno !=0)
    {
        perror("username name error");
        exit(1);
    }
    while(usr!= "exit")
    {
        host= new char[30];
        if( gethostname(host,30)==-1)
        {
            perror("gethostname");
        }
        cout<<usrname<<"@"<<host<<" $ ";
        delete []host;
        /*           if( execvp(argv[0],argv)==-1)
                     {
                     perror("invalid command");
                     }*/

        getline(cin,usr);
        char *ch=(char*)alloca(usr.length()+1);
        strcpy(ch,usr.c_str());
        string uc=usr;
        for(unsigned i=0;i<usr.length();i++)
        {
            if(usr[i]==';')
            {
                pos=strchr(uc,';'); 
                pch=strtok(ch,";");
                cout<<pch<<endl;
                cout<<ch<<endl;
                arg.push_back(pch);
                cout<<arg[0]<<endl;
                int pid=fork();
                    if(pid==0)
                    { char **argv=(char**)alloca(arg.size()+1);
                      int count=0;
                      cout<<count;
                      for(unsigned i=0;i<arg.size();i++)
                      {
                        argv[i] = (char*)alloca(arg[i].size()+1);
                        strcpy(argv[i],arg[i].c_str());
                        count=i;
                      }
                      cout<<"y"<<endl;
                      cout<<arg.size()<<endl;
                      for(unsigned i=0;i<arg.size();i++)
                      {
                          cout<<argv[i]<<endl;
                          cout<<"hello";
                      }
                      count++;
                      argv[count]=NULL; 
                      if(execvp(argv[0],argv)==-1)
                      {
                        perror("execvp");
                      }
                      else
                      {    
                          exit(1);
                      }
                    }
                    else if (pid <0)
                    {
                        perror("fork function failed");
                    }
                    else
                    {
                        wait(0);
                        arg.clear();
                    }
            }
            else if(usr[i]=='&'&&usr[i+1]=='&')
            {
                cout<<"hoal";
            }
            else if(usr[i]=='|'&&usr[i+1]=='|')
            {
                cout<<"bihao";
            }
        }
        pch=strtok(ch," ");
       while(pch!=NULL)
           {
        arg.push_back(pch);     
        pch=strtok(NULL," ");
           }
       

        cout<<arg[0]<<endl;
        int pid=fork();
        if(pid==0)
        { char **argv=(char**)alloca(arg.size()+1);
            int count=0;
            cout<<count;
            cout<<"hello";
            for(unsigned i=0;i<arg.size();i++)
            {
                argv[i] = (char*)alloca(arg[i].size()+1);
                strcpy(argv[i],arg[i].c_str());
                count=i;
            }
            cout<<"y"<<endl;
            cout<<arg.size()<<endl;
            for(unsigned i=0;i<arg.size();i++)
            {
                cout<<argv[i]<<endl;
                cout<<"hello";
            }
            count++;
            argv[count]=NULL; 
            if(execvp(argv[0],argv)==-1)
            {
                perror("execvp");
            }
            else
            {    
                exit(1);
            }
        }
        else if (pid <0)
        {
            perror("fork function failed");
        }
        else
        {
            wait(0);
            arg.clear();
        }


    }
}

