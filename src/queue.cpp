#include <iostream>
#include <errno.h>
#include <fstream>
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
void argcom(queue<string> & arg,queue<string> & args,int count,char ** & argv);
void execute(queue<string>&args,queue<string>&arg,int count,bool outr,bool inR,bool pip );
int main()
{
    string usr;
    queue<string> arg;

    queue<string>args;
    char **argv=NULL;
    bool outr=false;
    bool inR=false;
    bool pip=false;
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
        cout<<login<<"@"<<hostname<<":~$ ";
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
        if(arg.front()=="exit")
        {
            exit(1);
        }
        int count=0;
        cout << "myqueue contains: "<<endl;
        while(!arg.empty())
        {
            if(arg.front()==";")
            {  


            }
            else if(arg.front()=="exit")
            {
                exit(1);
            }
            else if(arg.front()==">")
            {
                cout<<"dwwee"<<endl;
                arg.pop();
                outr=true;
                if(outr==true)
                {
                    cout<<"sasawqw";
                }
                execute(args,arg,count,outr,inR,pip);
            } 
            else if(arg.front()=="<")
            {
                cout<<"dsrrh"<<endl;
                arg.pop();
                cout<<arg.front();
                inR=true;
                execute(args,arg,count,outr,inR,pip);

            }
            else if(arg.front()=="2")
            {

            }
            else if(arg.front()=="|")
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
                args.push(arg.front());
                arg.pop();
                count++;
            }
        }
    }
    return 0;
}
void argcom(queue<string> & arg,queue<string> & args,int count,char ** & argv)
{
    int num=0;
    argv=new char*[count];
    cout<<"l";
    for(int i=0;i<count;i++)
    {
        argv[i]=new char[args.size()+1];
        strcpy(argv[i],args.front().c_str());
        num=i;
    }
    num++;
    argv[num]=NULL;

}
void execute(queue<string>&args,queue<string>&arg,int count,bool outr,bool inR,bool pip)
{  
    int oor;
    int ii;
    int fd[2];
    pipe(fd);
    if(outr==true)
    {
        oor=1;
    }
    if(inR=true)
    {
       ii=0;
    }
    cout<<count<<endl;
    int pid= fork();
    if(pid == -1)
    {
        perror("fork");
    }
    else if(pid == 0)
    {     
        cout<<oor<<endl;
        cout<<count<<endl;
        if(ii==0)
        {
            cout<<count;
            int fdi=open("ls",O_RDONLY);
            if(fdi==-1)
            {
                perror("open");
                exit(1);
            } 
            if (dup2(fdi, 0) == -1)
            {
                perror("dup2");
                exit(1);
            }
            arg.pop();
            cout<<arg.front();
            if(arg.front()==">")
            {
              oor=1;
              arg.pop();
            }
        }
        cout<<oor<<endl;
        if(oor==1)
        {
            int fdo=open("s",O_RDWR|O_CREAT,0666);
            if(fdo==-1)
            {
                perror("open");
                exit(1);
            }
            if (dup2(fdo, 1) == -1)
            {
                perror("dup2");
                exit(1);

            }
        }
        execlp("cat" ,"cat" ,NULL);
        exit(1);


    }
    else 
    {
        wait(0);
        if(errno!=0)
        {
            perror("wait");
        }
    }
}
