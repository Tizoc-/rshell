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
  //  bool d=false;
//    bool e=false;
  //  bool h=false;
    if(lstat(file.c_str(),&inf)==-1)
    {
        perror("lstat");
        exit(1);
     }
    if (S_ISDIR(inf.st_mode))
    {
        modes.push_back('d');
   //      d=true;
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
   if(usrname==NULL)
{
 perror("getpwuid");
}
    cout<<usrname->pw_name<<" ";
    struct group *grp=getgrgid(inf.st_gid);
   if(grp==NULL)
{
  perror("getgrgid");
}
    cout<<grp->gr_name<<" ";
    cout<<inf.st_size<<" ";
    struct tm* t;
    char b[50];
    t=localtime(&(inf.st_mtime));
  if(t==NULL)
 {
 perror("localtime");
}
    strftime(b,50, "%b %e %H:%M",t);
    cout<<b<<" ";
    char buff[1024];
    char path[1024];
    cout << file<<" ";
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
    cout<<endl;
}


void ls(int flags, string file)
{
    string path;
    string reg;
    path.append(file);
    reg.append(file);
    path.append("/");
    char copy[500];
    char *regName=(char*)alloca(reg.length()+1);
    strcpy(regName,reg.c_str());
    //cout<<file<<endl;
    strcpy(copy,regName);
    DIR *dirp;
    dirent *direntp;
    struct stat ls;
    struct stat r;
    struct stat b;
    int totes=0;
    vector<string>files;
    vector<string>dir;
    if(lstat(regName,&r)==-1)
    {
        perror("stat");
        exit(1);
        }
    if(S_ISREG(r.st_mode))
    {  if(flags==0||flags==1||flags==5||flags==4)
       {
        cout<<regName;
       }
       else  if(flags==2||flags==3||flags==6||flags==7)
      {
        info(reg);
      }
    }
    else if(S_ISLNK(r.st_mode))
    {
      if(flags==2||flags==3)
      {
          info(reg); 
      }
    }
    else
    {
     char *dirName=(char*)alloca(path.length()+1);
    strcpy(dirName,path.c_str());
    if(stat(dirName,&r)==-1)
        {
          perror("stat");
          exit(1);
        }
     if(!(dirp =opendir(dirName)))
    {
        perror("opendir");
        exit(1);
    }
    while((direntp=readdir(dirp))!=NULL)
    {  strcat(copy,"/");
         strcat(copy,direntp->d_name);
       if( lstat(copy,&ls)==-1)
           {
             perror("lstat");
             exit(1);
           }
        if(S_ISREG(ls.st_mode))
        {
            if(flags==2)
            {
            }
        }
        else if(S_ISLNK(ls.st_mode))
        {
        
        }
        else if(errno !=0)
        {
            perror("readdir");
            exit(1);
        }
        if(flags==0||flags==2||flags==4||flags==6)//flags with hidden 
        {
            if(direntp->d_name[0]!='.')
            {

                files.push_back(direntp->d_name);
                totes+=ls.st_blocks;
            }
        }
        else if(flags==1||flags==3||flags==5||flags==7)// flags with hidden
        {
            files.push_back(direntp->d_name);
            totes+=ls.st_blocks;

        }
        copy[500]={0};
        strcpy(copy,dirName);
    }
    closedir(dirp);
    sort(files.begin(), files.end(), locale("en_US.UTF-8"));
    for(vector<int>::size_type i = 0; i != files.size(); ++i)
    {
        int bl,fl;
        bl=path.length();
        path.append(files.at(i));
        fl=path.length();
       if( stat(files[i].c_str(),&b)==-1)
           {
              perror("stat2");
              exit(1);
           }
        if((S_ISDIR(ls.st_mode)&&(files.at(i)!=".")&&(files.at(i)!="..")&&(!(S_ISLNK(ls.st_mode)))))
        {
            dir.push_back(path);
        }
        path.erase(bl,fl);
    }
/*   for(vector<int>::size_type i = 0; i != dir.size(); ++i)
    {
        cout<<dir[i]<<" ";
    }
    cout<<endl;
    cout<<"hello"<<endl;*/
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
    if(flags==4) //flag R
    {    
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {  if(i==0)
            {
                cout<<endl;
            }
            cout << files[i] <<"  ";

        }
        cout<<endl;
        for (vector<int>::size_type i = 0; i != dir.size(); ++i)
        {
            cout<<dir[i]<<":"<<endl;
            rls(4,dir[i]);
        }
    }
    if(flags==5)//flags Ra
    {
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {   
            cout<<files[i]<<" ";
        }
        for (vector<int>::size_type i = 0; i != dir.size(); ++i)
        {
            cout<<dir[i]<<" :"<<endl;
            rls(5,dir[i]);
        }
    }
    if(flags==6) // flagsRl
    {
        cout<<"total: "<<totes/2<<endl;
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {   
            info(files[i]);
        }
        for (vector<int>::size_type i = 0; i != dir.size(); ++i)
        {
            cout<<dir[i]<<":"<<endl;
            rls(6,dir[i]);
        }

    }
    if(flags==7) //flags Rla
    {
        cout<<"total: "<<totes/2<<endl;
        for (vector<int>::size_type i = 0; i != files.size(); ++i)
        {   
            info(files[i]);
        }
        for (vector<int>::size_type i = 0; i != dir.size(); ++i)
        {
            cout<<dir[i]<<":"<<endl;
            rls(7,dir[i]);
        }


    }
    }
}
void rls(int flags,string dire)
{
    ls(flags,dire);
}






