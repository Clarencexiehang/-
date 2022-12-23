#include<iostream>
#include "cstdlib"
#include "cstring"
#include "vector"
#include "time.h"
using namespace std;

typedef struct user{
    string userName;
    string passWord;
}user;

typedef struct file{
    string fileName;
    char fileType;     //文件为F，目录为D
    int address;
    char protectCode[3];    //存取rwx三种值，分别对应读取，写入和执行权限,没有权限赋值为-
    string content;
    file *pre;              //同目录下前一个文件结点
    file *subfile;          //子目录
    file *next;             //同级目录下一个文件结点
    int openNum;            //文件打开个数
    int len;                //文件长度
}file;

vector<user> User;      //用户队列
vector<file*> dirs;     //目录队列

//全局变量
string currentUser; //现在登录的用户
file* currentDir;   //现在所在的子目录
string Path="";     //所在路径
string cm;          //用户输入命令command
int addr = 0;

//函数声明
void CreateFile(string filename,file *head);
void DeleteFile(string fileName);
void CreateDir();
bool login();
void showDirs();
void openFile(string fileName);
void closeFile(string fileName);
void readFile(string fileName);
void writeFile(string fileName);


void CreateUser(){
    //分配一个root的用户
    user root;
    root.userName = "root";
    root.passWord = "123";
    User.push_back(root);
}

void setPath(string dir){
    if(Path == "" || dir == ".."){
        Path = "[";
        Path += currentUser;
        Path += " /]$ ";
    }else{
        if(Path[Path.size()-1-4] == '/')
            Path.insert(Path.size()-1-3,dir);
        else{
            Path = "[";
            Path += currentUser;
            Path += " /]$ ";
            Path.insert(Path.size()-1-2,dir);
        }
    }
}

void CreateFile(string filename,file *head){
    file *newFile = new file;
    newFile->fileName = filename;
    newFile->fileType = 'F';
    newFile->address = addr++;                              //物理地址用全局变量以示区分
    strcpy(newFile->protectCode,"rwx");        //默认文件具有可读可写权限
    newFile->content = "";
    newFile->pre = head;
    newFile->next = NULL;
    newFile->subfile = NULL;
    newFile->openNum = 0;
    newFile->len = sizeof(*newFile);

    //处理上一个结点
    if(head !=NULL){
        if(head->fileName == currentDir->fileName)
            head->subfile = newFile;
        else
            head->next = newFile;
    }
    dirs.push_back(newFile);
}

void DeleteFile(string fileName){
    file *tempFile = currentDir->subfile;

    while(tempFile){
        //若找到要删除的文件
        if(tempFile->fileName == fileName){
            if(tempFile->openNum != 0){
                cout<<"请先关闭文件！\n";
                return;
            }

            //如果前面结点为目录文件,则处理前一个结点的subfile指针，否则处理next指针
            if(tempFile->pre->fileName == currentDir->fileName){
                tempFile->pre->subfile = tempFile->next;
                //如果后一个结点不是NULL，则处理后一个的pre指针
                if(tempFile->next)
                    tempFile->next->pre = tempFile->pre;
            }else{
                tempFile->pre->next = tempFile->next;
                //如果后一个结点不是NULL，则处理后一个的pre指针
                if(tempFile->next)
                    tempFile->next->pre = tempFile->pre;
            }

            delete tempFile;
        }
        tempFile = tempFile->next;
    }
}

//创建二级目录,并且生成两个文件，f1没有任何权限，f2没有写权限
void CreateDir(){
    CreateFile(currentUser,NULL);
    dirs[dirs.size()-1]->fileType = 'D';
    currentDir = dirs[0];

    CreateFile("f1",currentDir);
    strcpy(dirs[1]->protectCode,"---");
    CreateFile("f2",dirs[1]);
    strcpy(dirs[2]->protectCode,"r--");

    CreateFile("Dir1",dirs[dirs.size()-1]);
    dirs[dirs.size()-1]->fileType = 'D';


    CreateFile("Dir2",dirs[dirs.size()-1]);
    dirs[dirs.size()-1]->fileType = 'D';
}

bool login(){
    string userName,password;
    cout<<"UserName: "; cin>>userName;
    cout<<"PassWord: "; cin>>password;
    for(int i=0;i<User.size();i++){
        if(User[i].userName==userName && User[i].passWord==password){
            cout<<"登录成功！\n";
            currentUser = userName;
            setPath("");
            return true;
        }
    }
    cout<<"请检查用户名或密码是否正确";
    return false;
}

void showDirs(){
   file* temp = currentDir->subfile;
   while(temp){
       if(temp->fileType == 'D'){
           cout<<"d"<<temp->protectCode<<" "<<temp->fileName<<"  物理地址:"<<temp->address;
           //计算文件夹的大小
           file *subFiles = temp->subfile;
           temp->len = sizeof(*temp);
           while(subFiles){
               temp->len += subFiles->len;
               subFiles = subFiles->next;
           }
           cout<<"  长度:"<<temp->len<<"B\n";
       }
       else if(temp->fileType == 'F')
           cout<<"-"<<temp->protectCode<<" "<<temp->fileName<<"  物理地址:"<<temp->address<<"  长度:"<<temp->len<<"B\n";

       temp = temp->next;
   }
}

void openFile(string fileName){
    file *tempFile = currentDir->subfile;
    while(tempFile){
        //若找到文件
        if(tempFile->fileName == fileName){
            if(tempFile->openNum!=5){
                tempFile->openNum++;
                cout<<"文件打开成功\n";
            }else{
                cout<<"打开数量超过上限！\n";
            }
            break;
        }
        tempFile = tempFile->next;
    }
}

void closeFile(string fileName){
    file *tempFile = currentDir->subfile;
    while(tempFile){
        //若找到文件
        if(tempFile->fileName == fileName){
            if(tempFile->openNum!=0){
                tempFile->openNum--;
                cout<<"文件关闭成功\n";
            }else{
                cout<<"文件已处于关闭状态\n";
            }
            break;
        }
        tempFile = tempFile->next;
    }
}

void readFile(string fileName){
    file *tempFile = currentDir->subfile;
    while(tempFile){
        //若找到文件
        if(tempFile->fileName == fileName){
            if(tempFile->openNum==0){
                cout<<"未打开文件\n";
                return;
            }

            if(tempFile->protectCode[0] != 'r'){
                cout<<"没有权限读取此文件\n";
                return;
            }
            cout<<tempFile->content<<"\n";
        }
        tempFile = tempFile->next;
    }
}

void writeFile(string fileName){
    file *tempFile = currentDir->subfile;
    while(tempFile){
        //若找到文件
        if(tempFile->fileName == fileName){
            if(tempFile->openNum==0){
                cout<<"未打开文件\n";
                return;
            }

            if(tempFile->protectCode[1] != 'w'){
                cout<<"没有权限写入此文件\n";
                return;
            }
            cout<<"写入内容:";
            string newContent;
            getline(cin,newContent);
            tempFile->content += newContent;
            tempFile->len = sizeof(*tempFile);
        }
        tempFile = tempFile->next;
    }
}


int main(){
    CreateUser();
    //登录
    while (1){
        bool login_status = login();
        if(login_status)
            break;
    }
    CreateDir();
    cin.ignore();

    while(1){
        cout<<Path;
        getline(cin,cm);

        if(cm == "exit")
            return 0;

        else if(cm[0] == 'c' && cm[1]=='d'){
            //取到cd 的目录
            string tempPath="";
            for(int i=3;i<cm.size();i++){tempPath +=cm[i];}

            setPath(tempPath);

            if(tempPath=="..")
                currentDir = dirs[0];
            else{
                for(vector<file*>::iterator it=dirs.begin();it != dirs.end();it++) {
                    if ((*it)->fileName == tempPath)
                        currentDir = *it;
                }
            }
        }

        else if(cm == "dir"){
            showDirs();
        }

        else if(cm.find("create") != cm.npos){
            //取到新文件名
            string temp;
            for(int i=7;i<cm.size();i++)
                temp +=cm[i];

            //找到上一个文件endfile
            file *endfile;
            if(currentDir->subfile){
                file *endfile = currentDir->subfile;
                while(endfile){
                    if(endfile->fileName == temp){
                        cout<<"文件名重复!";
                        break;
                    }
                    if(!endfile->next){
                        CreateFile(temp,endfile);
                        break;
                    }
                    else
                        endfile = endfile->next;
                }
            }else{
                endfile = currentDir;
                CreateFile(temp,endfile);
            }

        }

        else if(cm.find("delete") != cm.npos){
            //取到删除文件名
            string temp;
            for(int i=7;i<cm.size();i++)
                temp +=cm[i];

            DeleteFile(temp);
        }

        else if(cm.find("open") != cm.npos){
            //取到打开文件名
            string temp;
            for(int i=5;i<cm.size();i++)
                temp +=cm[i];

            openFile(temp);
        }

        else if(cm.find("close") != cm.npos){
            //取到打开文件名
            string temp;
            for(int i=6;i<cm.size();i++)
                temp +=cm[i];

            closeFile(temp);
        }

        else if(cm.find("read") != cm.npos){
            //取到读取文件名
            string temp;
            for(int i=5;i<cm.size();i++)
                temp +=cm[i];

            readFile(temp);
        }

        else if(cm.find("write") != cm.npos){
            //取到打开文件名
            string temp;
            for(int i=6;i<cm.size();i++)
                temp +=cm[i];

            writeFile(temp);
        }

        else{
            cout<<"未识别到该命令!\n";
        }
    }
}
