#include <iostream>
#include <pwd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <boost/tokenizer.hpp>
#include <queue>
#include <vector>
using namespace std;
int main()
{
    string usr;
    queue<string> arg;
    vector<string>arg2;
    bool redir=false;
    unsigned count=0;
    int pid;
    struct passwd *pass;
    pass = getpwuid(getuid());
    if(pass == NULL){
        perror("getpwuid()");
    }
    string login(pass->pw_name);
    char *host = new char[100];
    if( gethostname(host,30)==-1)
    {
        perror("gethostname");
    }
    string hostname(host);
    delete[] host;
    while(1){
    cout<<login<<"@"<<hostname<<" ";
    getline(cin,usr); 
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
    boost::char_separator<char> sep(" ", ";&|<>");
    tokenizer tokens(usr, sep);
    for (tokenizer::iterator tok_iter = tokens.begin();
            tok_iter != tokens.end(); ++tok_iter)
    {
        std::cout << "<" << *tok_iter << "> ";
        arg.push (*tok_iter);
        arg2.push_back(*tok_iter);
    }
    if(arg2[0]=="exit")
    {
        exit(1);
    }


    char **argv=(char**)alloca(arg.size()+1);

    std::cout << "myqueue contains: "<<endl;
    for(unsigned i= 0;i<arg2.size();i++)
    {
        cout<<arg2[i]<<endl;
        cout<<arg.front()<<endl;
        cout<<i<<endl;
        if(arg2[i]==";")
        {  arg.pop();
            argv[count]=NULL;
            pid=fork();
            if(pid==0)
            {
                for(int i =0;i<count;i++)
                {
                    cout<<argv[i]<<endl;
                } 
                if(execvp(argv[0],argv)==-1)
                {
                    perror("execvp");
                    exit(1);
                }
                else
                {
                    exit(1);
                }
            }
            else if (pid <0)
            {
                perror("fork function failed");
                exit(1);
            }
            else
            {
                wait(0);
                for(int i=0;i<count;i++)
                {
                    argv[i]==NULL;
                }
                for(int i =0;i<count;i++)
                {
                    cout<<argv[i]<<endl;
                }
                count=0;
            }
        }
        else if(arg2[i]=="exit")
        {
            exit(1);
        }
        else if(arg2[i]==">"&&arg2[i+1]==">")
        {
            arg.pop();
            arg.pop();
            cout<<arg.front()<<endl;
            count++;
            argv[count]=NULL;
            cout<<"append"<<endl;
            pid = fork();
            if(pid == -1)
            {
                perror("fork");
            }
            else if(pid == 0)
            {
                int fda=open(arg.front().c_str(),O_RDWR|O_CREAT|O_APPEND,0666);
                if(fda==-1)
                {
                    perror("open");
                    exit(1);
                }
                //    int oldstdout=dup(1);
               if( close(1)==-1)
               {
                 perror("close");
                 exit(1);
               }
               if( dup(fda)==-1)
               {
                 perror("dup");
                 exit(1);
               }
                //    cout << "fd=" << fd << endl;
                if(execvp(argv[0], argv) == -1)
                {
                    perror("execvp");
                    exit(1);
                } 

            }
            else
            {
                wait(NULL);
                for(int i=0;i<count;i++)
                {
                    argv[i]==NULL;
                }
                redir==true;
            }

        }
        else if(arg2[i]==">"&&arg2[i-1]!=">")
        { cout<<"\nredirect"<<endl;
            arg.pop();
            cout<<arg.front()<<endl;
            count++;
            argv[count]=NULL;
            pid = fork();
            if(pid == -1)
            {
                perror("fork");
            }
            else if(pid == 0)
            {
                cout<<"kshdj"<<endl;

                int fd=open(arg.front().c_str(),O_RDWR|O_CREAT,0666);
                if(fd==-1)
                {
                    perror("open");
                    exit(1);
                }
                //    int oldstdout=dup(1);
                cout<<"dshjb"<<endl;
               if( close(1)==-1)
                {
                   perror("close");
                }
               if( dup(fd)==-1)
               {
                perror("dup");
               }
               cout<<"hehehe"<<endl;
                   cout << "fd=" << fd << endl;
               if(execvp(argv[0], argv) == -1)
                {
                    perror("execvp");
                    exit(1);
                } 

            }
            else
            {
                wait(NULL);
                for(int j=0;j<count;j++)
                {
                    cout<<"work";
                    strcpy(argv[j],"");
                }
                for(int j=0;j<count;j++)
                {
                    cout<<argv[j];
                }
                redir=true;
                
            }
        }
        else if(arg2[i]=="<")
        {
            cout<<"stdin"<<endl;
            arg.pop();
            cout<<arg.front();
            count=i;
            cout<<count<<endl;
            argv[count] = (char*)alloca(arg.front().size()+1);
            strcpy(argv[count],arg.front().c_str());
            count ++;
            argv[count]=NULL;
            int fdi=open(arg.front().c_str(),O_RDONLY);
            if(fdi==-1)
            {
                perror("open");
            }
            if(close(0)==-1);
            {
                perror("close");
            }
            dup(fdi);
            pid = fork();
            if(pid == -1)
            {
                perror("fork");
            }
            else if(pid == 0)
            {

                if(execvp(argv[0], argv) == -1)
                {
                    perror("execvp");
                    exit(1);
                } 
                else
                {
                    exit(1);

                }

            }
            else
            {
                wait(NULL);
             /*   for(int i=0;i<count;i++)
                {
                   strcpy( argv[i],NULL);
                }*/
                redir==true;

            }
        }
        else if(arg2[i]=="|")
        {
            int fd[2];
            if(pipe(fd)==-1)
            {
                perror("pipe");
            }
            int pip=fork();
            if(pip==-1)
            {
                perror("fork");
            }
            else if(pip==0)
            { 
                dup2(fd[0],0);
                close(fd[1]);


            }
        }
        else
        {
            std::cout << ' ' << arg.front()<<' ';
            count=i;
            argv[count] = (char*)alloca(arg.front().size()+1);
            strcpy(argv[count],arg.front().c_str());
            arg.pop();
            cout<<count<<endl;
        }
    }
    count++;
    cout<<count<<endl;
    argv[count]=NULL;
    for(int i =0;i<count;i++)
    {
        cout<<argv[i];
    }
    cout<<argv[0];
    if(redir==false)
    {
        cout<<"why"<<endl;
        pid=fork();
        if(pid==0)
        {
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
        }

        std::cout << '\n';
    }
    }
    return 0;

}
