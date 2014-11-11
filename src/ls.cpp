#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <stdio.h>
#include <string.h>
using namespace std;
void inf(string filr,struct stat inf);
void ls(int flags,string file);
int main(int argc,char **argv)
{
    bool lflag=false;
    bool Rflag=false;
    bool aflag=false;
    int flags=0;
    vector<string> files;
    for(int i=1;i<argc;i++)
    {
        if(argv[i][0]=='-')
        {
            for(int j=1;argv[i][j]!=0;j++)
            {
                if(argv[i][j]=='a'&& aflag==false)
                {
                    aflag=true;
                    flags+=1;
                }
                else if(argv[i][j]=='l'&& lflag==false)
                {
                    lflag=true;
                    flags+=2;
                }
                else if(argv[i][j]=='R'&& Rflag==false)
                {
                    Rflag=true;
                    flags+=4;
                }
            }
        }
        else
        {
            files.push_back(argv[i]);

        }
    }
    cout<<files.size();
    cout<<flags<<endl;
    sort(files.begin(), files.end(), locale("en_US.UTF-8"));    
    if(files.size()==0)
    {
        ls(flags,".");
    }
    else if(files.size()>0)
    {
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {           ls(flags,files[i]);

        }
    }


    return 0;
}
void info(string file, struct stat inf)
{
    string modes="";
    lstat(file.c_str(),&inf);
    if (S_ISDIR(inf.st_mode))
    {
        modes.push_back('d');
    }
    else if(S_ISLNK(inf.st_mode))
    {
        modes.push_back('l');
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
        modes.push_back('w');
    }
    else
        modes.push_back('-');
    if(inf.st_mode &S_IXGRP)
    {
        modes.push_back('x');
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
    struct tm* t;
    t=localtime(&(inf.st_mtime));
    cout<<t<<" ";
    char buff[1024];
    char path[1024];
    cout << file<<endl;
    if( S_ISLNK(inf.st_mode)){
        ssize_t  rl;
        strcpy(path, file.c_str());
        rl = readlink(path,buff , inf.st_size+1);
        if(rl == -1)
        {
            perror("readlink: ");
        }
        buff[rl]='\0';
        cout<<"->"<<buff<<" ";
    }
    modes="";
}


void ls(int flags, string file)
{
    char *dirName=(char*)alloca(file.length()+1);
    strcpy(dirName,file.c_str());
    DIR *dirp;
    dirent *direntp;
    struct stat inf;
    int totes=0;
    vector<string>files;
    cout<<file<<endl;
    if(!(dirp =opendir(dirName)))
    {
        perror("opendir");
    }
    while((direntp=readdir(dirp)))
    {
        if(errno !=0)
        {
            perror("readdir");
        }
        if(flags==0||flags==2)//flags with hidden 
        {
            if(direntp->d_name[0]!='.')
            {
                files.push_back(direntp->d_name);
                totes+=inf.st_blocks;
            }
        }
        else if(flags==1||flags==3||flags==6||flags==7)// flags with hidden
        {
            files.push_back(direntp->d_name);
            totes+=inf.st_blocks;
        }
    }
    sort(files.begin(), files.end(), locale("en_US.UTF-8"));
    if(flags==0||flags==1)
    {
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {            cout << files[i] <<"  ";

        }

    }
    if(flags==2||flags==3||flags==6||flags==7)
    {
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {           info(files[i],inf);

        }

    }
}






