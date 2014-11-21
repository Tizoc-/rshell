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
void p(int nump,char **&argv,queue<string>&args,queue <string> &arg);
void pipin(queue <string> & arg,char **&argv,queue <string>pipearg);
void execute(queue<string>&args,queue<string>&arg,int count,bool outr,bool inR,bool pip,char **&argv );
int main()
{
    string usr;
    queue<string> arg;

    queue<string>args;
    char **argv=NULL;
    bool outr=false;
    bool inR=false;
    int nump=0;
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
            if(*tok_iter=="|")
            {
              nump++;
            }
            arg.push (*tok_iter);
        }
        if(arg.front()=="exit")
        {
            exit(1);
        }
        int count=0;
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
                arg.pop();
                outr=true;
                execute(args,arg,count,outr,inR,pip,argv);
            } 
            else if(arg.front()=="<")
            {
                arg.pop();
                inR=true;
                execute(args,arg,count,outr,inR,pip,argv);

            }
            else if(arg.front()=="2")
            {

            }
            else if(arg.front()=="|")
            {
                arg.pop();
                pip=true;
               p(nump,argv,args,arg);
               // int nump,char **&argv,queue<string>&argexecute(args,arg,count,outr,inR,pip,argv);
            }
            else
            {
                args.push(arg.front());
                arg.pop();
                count++;
            }
        }
        if(arg.empty())
        {
          execute(args,arg,count,outr,inR,pip,argv);
        }
    }
    return 0;
}
void argcom(queue<string> & arg,queue<string> & args,int count,char ** & argv)
{
    int num=0;
    argv=new char*[count];
    for(int i=0;i<count;i++)
    {

        argv[i]=new char[args.size()+1];
        strcpy(argv[i],args.front().c_str());
        args.pop();
        num=i;
    }
    num++;
    argv[num]=NULL;

}
void pipin(queue <string> & arg,char **&argv,queue <string>pipearg)
{
    int num=0;
    int count=0;
    if(pipearg.empty())
    {
        while(!arg.empty())
        {
            if(arg.front()!="|")
            {   arg.pop();
                break;
            }
            else
                pipearg.push(arg.front());    
            count++;
        }
        argv=new char*[count];
        for(int i=0;i<count;i++)
        {

            argv[i]=new char[pipearg.size()+1];
            strcpy(argv[i],pipearg.front().c_str());
            pipearg.pop();
            num=i;
        }
        num++;
        argv[num]=NULL;
        for(int i=0;i<count;i++)
        {
            cout<<"arg"<<endl;
            cout<<argv[i]<<endl;
        }

    }
    else
    {

        argv=new char*[count];
        for(int i=0;i<count;i++)
        {

            argv[i]=new char[pipearg.size()+1];
            strcpy(argv[i],pipearg.front().c_str());
            pipearg.pop();
            num=i;
        }
        num++;
        argv[num]=NULL;
        for(int i=0;i<count;i++)
        {
            cout<<"arg"<<endl;
            cout<<argv[i]<<endl;
        }
    }
}
void p(int nump,char **&argv,queue<string>&args,queue <string> &arg)
{  queue <string> pipearg;
    int cargs=0;
    int *fd=(int*)alloca(2*nump);
    for( int i = 0; i < nump; i++ ){
        if( pipe(fd + i*2) < 0 ){
            perror("pipe"); 
            exit(1);
        }
    }
    while(!args.empty())
    {
        pipearg.push(args.front());
        args.pop();
        cargs++;
    }
    int count=0;
    while(!arg.empty())
    {    if(count==0)
        {
            pipin(arg,argv,pipearg);
        }
        else if(count> 0)
        {
            pipin(arg,argv,pipearg);

        }
        int  pid = fork();
        if( pid == 0 ){
            if( count>0 ){
                if( dup2(fd[(count-1)*2], 0)==-1  ){
                    perror("dup2");
                    exit(1);
                }
            }
            if( count!=nump )
            {
                if( dup2(fd[count*2+1], 1)==-1){
                    perror("dup2");
                    exit(1);
                }
            }
            for(int i=0;i<2*nump;i++)
            {
                if(close(fd[i]))
                {
                    perror("close");
                    exit(1);
                }
            }
            if(execvp(argv[0],argv)==-1)
            {
                perror("execvp");
                exit(1);
            }
        } 
        else if( pid < 0 )
        {
            if (pid == -1) {
                perror("fork");
                exit(1);
            }
        }
        else
        {
            wait(0);
            count++;
        }
    }

}
void execute(queue<string>&args,queue<string>&arg,int count,bool outr,bool inR,bool pip,char **&argv)
{   int piip;
    int oor;
    int ii;
    int fd[2];
    pipe(fd);
    if(outr==true)
    {
        oor=1;
    }
    if(inR==true)
    {
        ii=0;
    }
    if(pip==true)
    {
        piip=3;
    }
    int pid= fork();
    if(pid == -1)
    {
        perror("fork");
    }
    else if(pid == 0)
    {     
        argcom(arg,args,count,argv);
        if(ii==0)
        {

            if(arg.front()!="<")
            {
                int fdi=open(arg.front().c_str(),O_RDONLY);
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
            }
            if(arg.front()=="<")
            {
                arg.pop();
                arg.pop();
                int fds = open(".oi2h3j1kj3", O_CREAT | O_RDWR | O_TRUNC, 0644);
                if (errno != 0) {
                    perror("open");
                    exit(1);
                }
                string quotes;
                quotes.append(arg.front());
                if(quotes[0]=='\"')
                {
                    quotes.erase(quotes.begin());
                }
                quotes.pop_back();
                write(fds,quotes.c_str(),quotes.size());
                if(errno !=0)
                {
                    perror("write");
                    exit(1);
                }
                if( close(fds)==-1)
                {
                    perror("exit");
                    exit(1);
                }
                fds=open(".oi2h3j1kj3", O_RDWR, 0644);
                if( dup2(fds,0)==-1)
                {
                    perror("dup2");
                }
            }
            arg.pop();
            if(arg.front()==">")
            {
                oor=1;
                arg.pop();
            }
            if(arg.front()=="|")
            {
                piip=3;  
                arg.pop();
            }
        }
        if(oor==1)
        {  
            if(arg.front()!=">")
            {
                int fdo=open(arg.front().c_str(),O_RDWR|O_CREAT,0666);
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
            if(arg.front()==">")
            {
                arg.pop();
                int fda=open(arg.front().c_str(),O_RDWR|O_CREAT|O_APPEND,0666);
                if(fda==-1)
                {
                    perror("open");
                    exit(1);
                }
                if (dup2(fda, 1) == -1)
                {
                    perror("dup2");
                    exit(1);

                }

            }
        }
        if(piip==3)
        {

            if( dup2(fd[1],1)==-1)
            {
                perror("dup2");
            }
            if(close(fd[0])==-1)
            {
                perror("close");
            }
        }

        if( execvp(argv[0] ,argv)==-1)
        {
            exit(1);
        }

    }
    else 
    {
	    if( wait(0)==-1)
	    {
		perror("wait");
	    }
	    if(errno!=0)
	    {
		    perror("wait");
	    }
	    while(!args.empty())
	    {
		    args.pop();
	    }
    }
}
