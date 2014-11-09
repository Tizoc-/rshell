#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <iostream>
#include <pwd.h>
#include <sys/stat.h>
#include <grp.h>
#include <iostream>
using namespace std;
string  getmodes();
void dir(string &file,int flags);
void noflags();
int getflags(int argc,char **argv,string &file);
int main(int argc,char ** argv)
{

	string file="";
	int  flags= getflags( argc, argv, file);
	cout<<file<<endl;
	dir(file,flags);

}
int  getflags(int argc,char **argv,string &file)
{
	int flags=0;
	for(int j=1;j<argc;j++)
	{
		if(argv[j][0]=='-')
		{
			for(int k=0; argv[j][k]!='\0'; k++)
			{
				if(argv[j][k]=='l')
					flags+=1;
				else if(argv[j][k]=='a')
					flags+=2;
				else if(argv[j][k]=='R')
					flags+=4;
			}
		}
		else
		{
			file=argv[j];
		}

	}
	if(file=="")
	{
		file=".";
	}
	return flags;

}
void dirinfo()
{
}
void dir(string &file,int flags)
{
	char *dirName=(char*)alloca(file.length()+1);
	strcpy(dirName,file.c_str());
	DIR *dirp;
	dirent *direntp;
	struct stat inf;
	vector<string>files;
	string modes="";
	if(!(dirp =opendir(dirName)))
	{
		if(S_ISREG(inf.st_mode))
		{
			perror("opendir");
		}
		else
		{
		}
	}
	while((direntp=readdir(dirp)))
	{
		if(errno !=0)
		{
			perror("readdir");
		}
		//        stat(direntp->d_name,&inf);
		if(flags==0||flags==1||flags==4||flags==5)//no a flag 
		{
			if(direntp->d_name[0]!='.')
			{
				files.push_back(direntp->d_name);
			}
		}
		else if(flags==2||flags==3||flags==7)// a flag
		{
			files.push_back(direntp->d_name);
		}
	}
	closedir(dirp);
	if(flags==0||flags==2)
	{
		sort(files.begin(),files.end(),locale("en_US.UTF-8"));
		stat(direntp->d_name,&inf);
		for (vector<int>::size_type i = 0; i != files.size(); ++i)
		{            cout << files[i] <<"  ";

		}
	}
	else if(flags==1)
	{
		sort(files.begin(),files.end(),locale("en_US.UTF-8"));
		for (vector<int>::size_type i = 0; i != files.size(); ++i)
		{
			stat(files.at(i).c_str(),&inf);
			if (S_ISDIR(inf.st_mode))
			{
				modes.push_back('d');
			}
			else
				modes.push_back('-');
			if (inf.st_mode & S_IRUSR)
			{
				modes.push_back('r');
			}
			else
				modes.push_back('-');
			if (inf.st_mode & S_IWUSR)
			{
				modes.push_back('w');
			}
			else
				modes.push_back('-');
			if (inf.st_mode & S_IXUSR)
			{
				modes.push_back('x');
			}
			if(inf.st_mode &S_IRGRP)
			{
				modes.push_back('r');
			}
			else
				modes.push_back('-');
			if(inf.st_mode &S_IWGRP)
			{
				modes.push_back('r');
			}
			else
				modes.push_back('-');
			if(inf.st_mode &S_IXGRP)
			{
				modes.push_back('r');
			}
			else
				modes.push_back('-');
			if(inf.st_mode & S_IROTH)
			{
				modes.push_back('r');
			}
			else
				modes.push_back('-');
			if(inf.st_mode & S_IWOTH)
			{
				modes.push_back('w');
			}
			else
				modes.push_back('-');
			if(inf.st_mode & S_IXOTH)
			{
				modes.push_back('x');
			}
			else
				modes.push_back('-');
			cout<<modes<<" ";
			cout<<" "<<inf.st_nlink<<" ";
			struct passwd *usrname= getpwuid(inf.st_uid);
			cout<<usrname->pw_name<<" ";
			struct group *grp=getgrgid(inf.st_gid);
			cout<<grp->gr_name<<" ";
			cout<<inf.st_size<<" ";
			cout<<ctime(&inf.st_mtime);
			cout << files[i]<<endl;
			modes="";
		}
	}
}
