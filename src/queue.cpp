#include <iostream>
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
using namespace std;
int main()
{
    string usr;
    queue<string> arg;
 int count=0;
int pid;
    std::cout << "Please enter some integers (enter 0 to end):\n";

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
    }


    char **argv=(char**)alloca(arg.size()+1);

    std::cout << "myqueue contains: "<<endl;
    while (!(arg.empty()))
    {
        if(arg.front()==";")
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
        else if(arg.front()==">")
        { cout<<"\nredirect"<<endl;
            arg.pop();
            argv[count]=NULL;
            pid = fork();
            if(pid == -1){
                perror("fork");
            }
            else if(pid == 0)
            {

                int fd=open(arg.front().c_str(),O_RDWR|O_CREAT,0666);
                if(fd==-1)
                {
                    perror("open");
                    exit(1);
                }
            //    int oldstdout=dup(1);
                close(1);
                dup(fd);
            //    cout << "fd=" << fd << endl;
                if(execvp(argv[0], argv) == -1)
                {
                    perror("execvp");
                    exit(1);
                } 
                else
                {
                    exit(1);
                }
              //  close(1);
              //  dup(oldstdout);
              //  cout << "to the screen" << endl;
                /* cout<<"pid"<<endl;
                   cout<<arg.front()<<endl;
                   cout<<"l"<<endl;
                   int fdo = open("testfile", O_RDWR|O_CREAT,0666);

                   cout << "fdo: " << fdo << endl;
                   if(fdo == -1)

                   int oldstout=dup(1);
                   if(oldstout==-1)
                   {
                   perror("dup");
                   }
                   if(close(1) == -1 )
                   {
                   perror("close");
                   }
                   if(dup(fdo) == -1)
                   {
                   perror("dup");
                   }
                   cout<<fdo<<endl;*/

            }
            else{
                wait(NULL);
                for(int i=0;i<count;i++)
                {
                    argv[i]==NULL;
                }

            }

        }
        else
        {
            std::cout << ' ' << arg.front();
            argv[count] = (char*)alloca(arg.front().size()+1);
            strcpy(argv[count],arg.front().c_str());
            arg.pop();
            count++;
        }
    }
    argv[count]=NULL;
    for(int i =0;i<count;i++)
    {
        cout<<argv[i];
    }
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

    return 0;

}
