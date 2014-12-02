#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <queue>
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <vector> 
using namespace std;
void sighand(int sig);
string prep(string usr);
queue<string> parse(string a);
queue<string> path();
void run(int count,queue<string>&arg,queue<string>&dir);
void myexec(int count,queue<string>&arg,queue<string>&dir);
int main()
{    
	string usr;
	queue<string> cmd;
	queue<string> arg;	
	queue<string> dir;
	struct stat buff;
	int count=0;
	signal(SIGINT,sighand);
	while(1)
	{
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
		char buf[1024];
		if(!getcwd(buf,1024))
		{
			perror("problem with getcwd.");
		}

		cout<<login<<"@"<<hostname<<":~"<<buf<<"$ ";
		getline(cin,usr);
		string a=prep(usr);	
		cout<<a<<endl;
		cmd=parse(a);
		if(cmd.front()=="exit")
		{
			exit(1);
		}
		while(!cmd.empty())
		{
			if(cmd.front()=="exit")
			{
				exit(1);
			}	
			else if(cmd.front()=="#")
			{
				while(!cmd.empty())
				{
					cmd.pop();
				}
			}
			else if(cmd.front()==";")
			{
			  cmd.pop();
			}
			else if(cmd.front()=="cd")
			{
				cmd.pop();
			 	chdir(cmd.front().c_str());
				while(!cmd.empty())
				{
					cmd.pop();
				}
			}
			else
			{
				cout<<cmd.front()<<endl;
				arg.push(cmd.front());
				cmd.pop();
				count++;
			}
		}	

		dir= path();
		run(count,arg,dir);
		while(!arg.empty())
		{
		  arg.pop();
		}	
		while(!dir.empty())
		{
		 dir.pop();
		}
		count=0;
	}

}
queue<string>  path()
{	queue<string> arg;
	string get= getenv("PATH");
	if(errno==!0)
	{
		perror("getenv");
	}
	typedef boost::tokenizer<boost::char_separator<char> > 
		tokenizer;
	boost::char_separator<char> sep(":", "");
	tokenizer tokens(get, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter)
	{	std::cout << "<" << *tok_iter << "> ";
		arg.push(*tok_iter);
		std::cout << "\n";
	}
	return arg;

}
string prep(string usr)
{
	typedef boost::tokenizer<boost::char_separator<char> > 
		tokenizer;
	boost::char_separator<char> sep("",";|<>&");
	tokenizer tokens(usr, sep);
	int a=0;
	int i=0;
	string f;
	for (tokenizer::iterator tok_iter = tokens.begin();tok_iter != tokens.end(); ++tok_iter)
	{	std::cout << "<" << *tok_iter << "> ";
		if(*tok_iter==";")
		{
			f.append(" ");
			f.append(*tok_iter);
		}
		else if(*tok_iter=="|")
		{
			if(i==0)
			{
				f.append(" ");
				f.append(*tok_iter);
				i++;
			}	
			else if(i==1)
			{
				f.append(*tok_iter);
				i=0;
			}

		}
		else if(*tok_iter=="&")
		{
			if(a==0)
			{
				f.append(" ");
				f.append(*tok_iter);
				a++;
			}	
			else if(a==1)
			{
				f.append(*tok_iter);
				a=0;
			}

		}
		else
		{
			f.append(*tok_iter);	
		}	
		std::cout << "\n";
	}
	cout<<f<<endl;
	return f;
}
void run(int count,queue<string>&arg,queue<string>&dir)
{

	int pid = fork();
	if(pid == -1)
	{
		perror("fork()");
		exit(1);
	}else if(pid == 0)
	{
		cout<<"child"<<endl;
		myexec(count,arg,dir);
		exit(1);
	}else if(pid > 0)
	{
		if(wait(0) == -1)
		{
			perror("wait()");
		}
	}

}
void myexec(int count,queue<string>&arg,queue<string>&dir)
{
	int num=0;
	int e;
	char **argv=NULL;
	string path;
	string cmd;
	cmd.append(arg.front());
	argv=new char*[count];
	for(int i=0;i<count;i++)
	{
		argv[i]=new char[arg.size()+1];
		strcpy(argv[i],arg.front().c_str());
		arg.pop();
		num=i;
	}
	num++;
	argv[num]=NULL;
	if(cmd[0]=='/')
	{
	if(execv(cmd.c_str(),argv))
	{
	perror("execv");
	}
	}
	while(!dir.empty())
	{
		path.append(dir.front());
		path.append("/");
		path.append(cmd);
		e=(execv(path.c_str(),argv));
		dir.pop();
		path.erase(path.begin(),path.end());
	}
	if(e==-1);
	{
		perror("execvp");
	}

}
queue<string> parse(string a)
{
	queue<string>cmd;
	cout<<a<<endl;
	typedef boost::tokenizer<boost::char_separator<char> > 
		tokenizer;
	boost::char_separator<char> sep(" ","");
	tokenizer tokens(a, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();tok_iter != tokens.end(); ++tok_iter)
	{	std::cout << "<" << *tok_iter << "> ";
		cmd.push(*tok_iter);
	}
	return cmd;
}
void sighand(int sig)
{
	if(sig==SIGINT)
	{
		int pid=getpid();
		if(pid==-1)
		{
			perror("getpid");
			exit(0);
		}
		if(pid==0)
		{
			kill(0,SIGINT);

		}
	}  
}
