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
void info(string file);
void ls(int flags,string file);
void rls(int flags,string file);
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
    cout<<files.size()<<endl;
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
void info(string file )
{
    struct stat inf;
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
    char b[50];
    t=localtime(&(inf.st_mtime));
    strftime(b,50, "%b %e %H:%M",t);
    cout<<b<<" ";
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
    struct stat ls;
    int totes=0;
    string path;
    path.append(file);
    path.append("/");
    vector<string>files;
    vector<string>dir;
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
        if(flags==0||flags==2||flags==4)//flags with hidden 
        {
            if(direntp->d_name[0]!='.')
            {

                stat(direntp->d_name,&ls);
                files.push_back(direntp->d_name);
                totes+=ls.st_blocks;
            }
        }
        else if(flags==1||flags==3||flags==5||flags==7)// flags with hidden
        {
            stat(direntp->d_name,&ls);
            files.push_back(direntp->d_name);
            totes+=ls.st_blocks;

        }
    }
    closedir(dirp);
    sort(files.begin(), files.end(), locale("en_US.UTF-8"));
    for(vector<int>::size_type i = 0; i != files.size(); ++i)
    {
        int bl,fl;
        bl=path.length();
        path.append(files.at(i));
        fl=path.length();
        stat(files[i].c_str(),&ls);
        if(S_ISDIR(ls.st_mode))
        {
            dir.push_back(path);
        }
        path.erase(bl,fl);
    }
    for(vector<int>::size_type i = 0; i != dir.size(); ++i)
    {
        cout<<dir[i]<<endl;
    }
    if(flags==0||flags==1)
    {
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {  // int length=80;
            cout << files[i] <<"  ";

        }

    }
    if(flags==2||flags==3)
    {   cout<<"total: "<<totes/2<<endl;
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {   
            info(files[i]);
        }

    }
    if(flags==4)
    {
        cout<<"hello";
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {            cout << files[i] <<"  ";

        }
        cout<<endl;
        for (vector<int>::size_type i = 0; i != dir.size(); ++i)
        {
            cout<<dir[i]<<":"<<endl;
            rls(4,dir[i]);
        }
    }
    if(flags==5)//flags Rl
    {
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {   
            cout<<files[i]<<endl;
        }
        for (vector<int>::size_type i = 0; i != dir.size(); ++i)
        {
            cout<<dir[i]<<":"<<endl;
    //        rls(5,dir[i]);
        }
    }
}
void rls(int flags,string dire)
{
    ls(flags,dire);
}






