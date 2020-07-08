#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;
#define ID 53
#define CHARS 52
#define NUM 10

/*******数据结构*******/
typedef struct node
{
    char op[3];
    char argu1[3];
    char argu2[3];
    char result[3];
} Node;
typedef struct temp_pool{
    char tp[3];
} Temp_pool;

static int index = 0;
int pos = 0;
string txt;
string keyword;
vector<Node> order;
vector<Temp_pool> pool;
vector<string> kkw;
vector<int> line_no;

/*************文件读入模块*************/
ifstream get_file(const string file_path);
void import_txt(ifstream & iread,string & txt);
/***********文件读入模块结束************/

/***************公共数据***************/
char id[ID] =  {'_','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char number[NUM] = {'0','1','2','3','4','5','6','7','8','9'};
/*************公共数据结束*************/

/***************公共模块**************/
bool It_is_letter(char c);
bool Is_id(int & tops);
bool Is_id(void);
bool Is_number(char c);
bool Is_non_zero(char c);
bool Is_number(void);
bool Is_number(int & n);
bool Is_type(int & n);
bool Is_type(void);
void clean_space();
bool Is_if();
bool Is_while();
void put_strings_into(void);
bool cmper(string & ifkk);
void fill_line_no(void);
int give_line_no(int n);
bool Is_judgement(Temp_pool & temp,int & n);
bool Is_judgement(void);
void result(char * resutl);
void filling_the_pool(void);
/*************公共模块结束************/

/**********算术表达式分析模块**********/
//此处为直接拷贝自bianyi4
char first_E[1] = {'('};
char first_Eprime[2] = {'+','-'};
char first_T[1] = {'('};
char first_Tprime[2] = {'*','/'};
char first_F[1] = {'('};
char first_M[2] = {'*','/'};
char first_A[2] = {'+','-'};
char follow_Eprime[2] = {')',';'};
char follow_Tprime[4] = {'+','-',')',';'};

bool Is_In_firstT(char c);
bool Is_In_firstE(char c);
bool Is_In_followE(void);
bool Is_In_firstF(char c);
bool Is_In_firstM(char c);
bool Is_In_firstA(char c);
bool Is_In_followEprime(char c);
bool Is_In_followTprime(char c);

Temp_pool E(void);
Temp_pool Eprime(Node & part);
Temp_pool T(void);
Temp_pool Tprime(Node & part);
Temp_pool F(void);
char A(void);
char M(void);
/**********算术表达式分析结尾**********/

/**********声明语句分析模块************/
bool Is_in_first_Dprime(void);
bool Is_in_follow_H(char c);
bool Is_in_first_Ty(void);
bool Is_in_first_G(char c);
bool Is_in_follow_D(void);

void D(void);
void H(void);
void Dprime(void);
void Ty(void);
void N(void);
void Nprime(void);
void G(void);
/**********声明语句分析结束************/

/***********语句们分析开始*************/
bool Is_in_first_R();
bool Is_in_first_Sprime();
bool Is_in_follow_R();
bool Is_in_follow_S();

void B(void);
void S(void);
void R(void);
void Sprime(void);
void Sprime(int & n);
void BOOL(Node & part);
/************语句们分析结束***********/

int main(void)
{
    ifstream readfile(get_file("./bp.cpp"));
    ifstream readfile2(get_file("./keyword.txt"));
    import_txt(readfile,txt);
    import_txt(readfile2,keyword);
    put_strings_into();
    fill_line_no();
    filling_the_pool();
    B();
    cout<<"size of order = "<<order.size()<<endl;
    for(int i=0;i<order.size();i++)
    {
        cout<<i<<" ";
        cout<<order[i].op[0];
        cout<<order[i].op[1];
        cout<<order[i].op[2];
        cout<<" ";
        cout<<order[i].argu1[0];
        cout<<order[i].argu1[1];
        cout<<order[i].argu1[2];
        cout<<order[i].argu2[0];
        cout<<order[i].argu2[1];
        cout<<order[i].argu2[2];
        cout<<" ";
        cout<<order[i].result[0];
        cout<<order[i].result[1];
        cout<<order[i].result[2];
        cout<<endl;
    }
    cout<<"#"<<pos<<'$'<<txt[pos]<<"#"<<endl;
    return 0;
}

/**********文件读入模块**********/
ifstream get_file(const string file_path)
{
    ifstream readfile(file_path,ios::in);
    if(readfile.is_open())
    {
        cout<<"open is OK!"<<endl;
        return readfile;
    }
    else
    {
        cout<<"file open failed!"<<endl;
        //打开失败就直接退出，简单粗暴
        exit(0);
    }
}
void import_txt(ifstream & iread,string & txt)
{
    string temp;
    while(getline(iread,temp))
    {
        temp.append("\n");
        txt.append(temp);
    }
    txt.erase(txt.size()-1);    //擦去字符末尾多加入的一个换行符
}
/************公共模块内容************/
//比较一个传入的字符串是否与列表中的关键字相同
bool cmper(string & ifkk)
{
    for(int i=0;i<kkw.size();i++)
    {
        if(kkw[i].compare(ifkk) == 0)
        {
            return true;
        }
    }
    return false;
}
//把从文件读入的关键字push进向量kkw中,而kkw是一个全局变量，这样做目的是避免频繁在函数间传递参数
void put_strings_into(void)
{
    vector<int> index;
    for(int i=0;i<keyword.size();i++)
    {
        if(keyword[i] == '\n')
        {
            index.push_back(i);
        }
    }
    for(int j=0;j<index.size();j++)
    {
        if(j == 0)
        {
            kkw.push_back(keyword.substr(0,index[j]));
        }
        else if(j == index.size()-1)
        {
            kkw.push_back(keyword.substr(index[j]+1,keyword.size()-index[j]-1));
        }
        else
        {
            kkw.push_back(keyword.substr(index[j]+1,index[j+1]-index[j]-1));
        }
    }
}
bool It_is_letter(char c)
{
    for(int i=0;i<ID;i++)
    {
        if(c==id[i])
        {
            return true;
        }
    }
    return false;
}
//判断一个字符是否为一个little C形式的id,实际也就是一个字母,但现在不是了，它是一个长度不过3的字符串
bool Is_id(int & tpos)
{
    tpos = pos;
    if(It_is_letter(txt[tpos]))
    {
        tpos++;
        while(It_is_letter(txt[tpos]) || Is_number(txt[tpos]))
        {
            tpos++;
        }
        if(tpos-pos > 3)
        {
            return false;
        }
        else
        {
            string temp(txt.substr(pos,tpos-pos));
            if(cmper(temp))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}
//重载的函数
bool Is_id(void)
{
    int tpos = pos;
    if(It_is_letter(txt[tpos]))
    {
        tpos++;
        while(It_is_letter(txt[tpos]) || Is_number(txt[tpos]))
        {
            tpos++;
        }
        if(tpos - pos > 15)
        {
            return false;
        }
        else
        {
            string temp(txt.substr(pos,tpos-pos));
            if(cmper(temp))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}
bool Is_number(char c)
{
    for(int i=0;i<NUM;i++)
    {
        if(c==number[i])
        {
            return true;
        }
    }
    return false;
}
bool Is_non_zero(char c)
{
    for(int i=1;i<NUM;i++)
    {
        if(c == number[i])
        {
            return true;
        }
    }
    return false;
}
//overload func
bool Is_number(void)
{
    int bpos = pos;
    if(Is_non_zero(txt[bpos]))
    {
        bpos++;
        while (Is_number(txt[bpos]))
        {
            bpos++;
        }
        if(txt[bpos]=='.')
        {
            bpos++;
            int tt = bpos;
            while (Is_number(txt[bpos]))
            {
                bpos++;
            }
            if(tt==bpos)
                return false;
            else
                return true;
        }
        else
        {
            return true;
        }
    }
    else if(txt[bpos]=='0' && !Is_number(txt[bpos+1]))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_number(int & n)
{
    n = pos;
    if(Is_number(txt[n]))
    {
        n++;
        while (Is_number(txt[n]))
        {
            /* code */
            n++;
        }
        if(txt[n]=='.')
        {
            n++;
            int tt = n;
            while (Is_number(txt[n]))
            {
                /* code */
                n++;
            }
            if(tt==n)
                return false;
            else
                return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}
bool Is_if()
{
    if(txt[pos] == 'i' && txt[pos+1] == 'f')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_while()
{
    if(txt.substr(pos,5).compare("while") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//判断从当前索引处起的三个连续字符是否为类型关键字int
bool Is_type(int & n)
{
    if(txt.substr(pos,3).compare("int") == 0)
    {
        n = 3;
        return true;
    }
    else if(txt.substr(pos,5).compare("float") == 0)
    {
        n = 5;
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_type(void)
{
    if(txt.substr(pos,3).compare("int") == 0)
    {
        return true;
    }
    else if(txt.substr(pos,5).compare("float") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void clean_space()
{
    while(txt[pos] == ' '||txt[pos]=='\n'||txt[pos]=='\t')
    {
        pos++;
    }
}
void fill_line_no(void)
{
    for(int i=0;i<txt.size();i++)
    {
        if(txt[i] == '\n')
        {
            line_no.push_back(i);
        }
    }
}
int give_line_no(int n)
{
    if(n <= line_no[0])
    {
        return 1;
    }
    else if(n>line_no[0] && n<txt.size())
    {
        for(int i=1;i<line_no.size();i++)
        {
            if(n>line_no[i-1]&&n<=line_no[i])
            {
                return i+1;
            }
        }
        return line_no.size()+1;
    }
    else
    {
        return -1;
    }
}
bool Is_judgement(Temp_pool & temp,int & n)
{
    if(txt[pos]=='='&&txt[pos+1]=='=')
    {
        temp.tp[0] = 'j';
        temp.tp[1] = 'e';
        temp.tp[2] = '\0';
        n = 2;
        return true;
    }
    else if(txt[pos] =='!'&&txt[pos+1]=='=')
    {
        temp.tp[0] = 'j';
        temp.tp[1] = 'n';
        temp.tp[2] = 'e';
        n = 2;
        return true;
    }
    else if(txt[pos] =='<'&&txt[pos+1]=='=')
    {
        temp.tp[0] = 'j';
        temp.tp[1] = 'b';
        temp.tp[2] = 'e';
        n = 2;
        return true;
    }
    else if(txt[pos]=='>'&&txt[pos+1]=='=')
    {
        temp.tp[0] = 'j';
        temp.tp[1] = 'a';
        temp.tp[2] = 'e';
        n = 2;
        return true;
    }
    else if(txt[pos] == '>')
    {
        temp.tp[0] = 'j';
        temp.tp[1] = 'a';
        temp.tp[2] = '\0';
        n = 1;
        return true;
    }
    else if(txt[pos] == '<')
    {
        temp.tp[0] = 'j';
        temp.tp[1] = 'b';
        temp.tp[2] = '\0';
        n = 1;
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_judgement(void)
{
    if(txt[pos]=='='&&txt[pos+1]=='=')
    {
        return true;
    }
    else if(txt[pos] =='!'&&txt[pos+1]=='=')
    {
        return true;
    }
    else if(txt[pos] =='<'&&txt[pos+1]=='=')
    {
        return true;
    }
    else if(txt[pos]=='>'&&txt[pos+1]=='=')
    {
        return true;
    }
    else if(txt[pos] == '>')
    {
        return true;
    }
    else if(txt[pos] == '<')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void filling_the_pool(void)
{
    Temp_pool t;
    for(char a='0';a<='9';a++)
    {
        for(char b='0';b<='9';b++)
        {
            t.tp[0] = 'T';
            t.tp[1] = a;
            t.tp[2] = b;
            pool.push_back(t);
        }
    }
}
void result(char * result)
{
    memcpy(result,pool[index].tp,3);
    index++;
}
/************公共模块内容************/
/************声明模块开始************/
//几个集成的first集和follow集判断函数
bool Is_in_first_Dprime(void)
{
    if(Is_type())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_in_follow_H(char c)
{
    if(Is_id())
    {
        return true;
    }
    else if (Is_if())
    {
        return true;
    }
    else if (Is_while())
    {
        return true;
    }
    if(txt[pos] == '{'||txt[pos] =='}')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_in_first_Ty(void)
{
    if(Is_type())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_in_first_G(char c)
{
    if(c == ',')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_in_follow_D(void)
{
    if(Is_in_first_R())
    {
        return true;
    }
    else if(txt[pos] == '{'||txt[pos]=='}')
    {
        return true;
    }
    else
    {
        return false;
    }
}
//产生式 D->H
void D(void)
{
    clean_space();
    if(Is_type())
    {
        H();
    }
    else if(Is_in_follow_D())
    {
        //doing nothing
    }
    else
    {
        clean_space();
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Statement error."<<endl;
        exit(0);
    }
}
void H(void)
{
    clean_space();
    if(Is_in_first_Dprime())
    {
        Dprime();
        H();
    }
    else if (Is_in_follow_H(txt[pos]))
    {
        /* nothing to do */
    }
    else
    {
        clean_space();
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Statement error."<<endl;
        exit(0);
    }
}
void Dprime(void)
{
    clean_space();
    if(Is_in_first_Ty())
    {
        Ty();
        int start = pos;
        while(txt[pos] == ' ')
        {
            pos++;
        }
        int end = pos;
        if(end-start<1)
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Variable declaration error. Space must be there between type and id."<<endl;
            exit(0);
        }
        else
        {
            N();
            clean_space();
            if(txt[pos] == ';')
            {
                pos++;
            }
            else
            {
                cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Variable declaration error. Missing a ';'."<<endl;
                exit(0);
            }
        }
    }
    else
    {
        clean_space();
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Variable declaration error."<<endl;
        exit(0);
    }
}
void Ty(void)
{
    int type_forward;
    if(Is_type(type_forward))
    {
        pos+=type_forward;
    }
    else
    {
        clean_space();
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Variable declaration error. Wrong type."<<endl;
        exit(0);
    }
}
void N(void)
{
    clean_space();
    if(Is_id())
    {
        Nprime();
        G();
    }
    else
    {
        clean_space();
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Statement error. Wrong id."<<endl;
        exit(0);
    }
}
void Nprime(void)
{
    clean_space();
    int fman;
    if(Is_id(fman))
    {
        pos = fman;
    }
    else
    {
        clean_space();
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Statement error. Wrong id."<<endl;
        exit(0);
    }
}
void G(void)
{
    clean_space();
    if(Is_in_first_G(txt[pos]))
    {
        pos++;
        Nprime();
        G();
    }
    else if (txt[pos] == ';')
    {
        /* nothing to do */
    }
    else
    {
        clean_space();
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Statement error or missing a ';'."<<endl;
        exit(0);
    }
}
/**********声明语句模块结束**********/

/***********算数表达式模块**********/
bool Is_In_firstE(char c)
{
    if(c=='(')
    {
        return true;
    }
    else if(Is_id())
    {
        return true;
    }
    else if(Is_number())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_In_firstT(char c)
{
    if(c==first_T[0])
    {
        return true;
    }
    if(Is_id())
    {
        return true;
    }
    if(Is_number())
    {
        return true;
    }
    return false;
}
bool Is_In_firstF(char c)
{
    if(c==first_F[0])
    {
        return true;
    }
    if(Is_id())
    {
        return true;
    }
    if(Is_number())
    {
        return true;
    }
    return false;
}
bool Is_In_firstM(char c)
{
    for(int i=0;i<2;i++)
    {
        if(c==first_M[i])
        {
            return true;
        }
    }
    return false;
}
bool Is_In_firstA(char c)
{
    for(int i=0;i<2;i++)
    {
        if(c==first_A[i])
        {
            return true;
        }
    }
    return false;
}
bool Is_In_followE(void)
{
    if(Is_judgement())
    {
        return true;
    }
    else if(txt[pos]==')')
    {
        return true;
    }
    else if(Is_in_first_R())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_In_followEprime(char c)
{
    for(int i=0;i<2;i++)
    {
        if(c==follow_Eprime[i])
        {
            return true;
        }
    }
    if(Is_id())
    {
        return true;
    }
    if(Is_if())
    {
        return true;
    }
    if(Is_while())
    {
        return true;
    }
    if(Is_In_followE())
    {
        return true;
    }
    return false;
}
bool Is_In_followTprime(char c)
{
    for(int i=0;i<4;i++)
    {
        if(c==follow_Tprime[i])
        {
            return true;
        }
    }
    if(Is_id())
    {
        return true;
    }
    if(Is_if())
    {
        return true;
    }
    if(Is_while())
    {
        return true;
    }
    if(Is_In_followE())
    {
        return true;
    }
    return false;
}
Temp_pool E(void)
{
    clean_space();
    Node part;
    Temp_pool temp;
    if(Is_In_firstT(txt[pos]))
    {
        temp = T();
        memcpy(part.argu1,temp.tp,3);
        temp = Eprime(part);
        if(temp.tp[0] == '\0')
        {
            memcpy(temp.tp,part.argu1,3);
        }
        else
        {
            memcpy(part.argu2,temp.tp,3);
            result(part.result);
            order.push_back(part);
            memcpy(temp.tp,part.result,3);
        }
        return temp;
    }
    else if(Is_In_followE())
    {
        memcpy(temp.tp,"\0\0",3);
        return temp;
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error."<<endl;
        exit(0);
    }
}
Temp_pool Eprime(Node & part)
{
    clean_space();
    Node part2;
    Temp_pool temp;
    if(Is_In_firstA(txt[pos]))
    {
        part.op[0] = A();
        part.op[1] = '\0';
        part.op[2] = '\0';
        temp = T();
        memcpy(part2.argu1,temp.tp,3);
        temp = Eprime(part2);
        if(temp.tp[0] == '\0')
        {
            memcpy(temp.tp,part2.argu1,3);
        }
        else
        {
            memcpy(part.argu2,temp.tp,3);
            result(part2.result);
            order.push_back(part2);
            memcpy(temp.tp,part2.result,3);
        }
        return temp;
    }
    else if (Is_In_followEprime(txt[pos]))
    {
        memcpy(temp.tp,"\0\0",3);
        return temp;
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error."<<endl;
        exit(0);
    }
}
Temp_pool T(void)
{
    clean_space();
    Node part;
    Temp_pool temp;
    if(Is_In_firstF(txt[pos]))
    {
        temp = F();
        memcpy(part.argu1,temp.tp,3);
        temp = Tprime(part);
        if(temp.tp[0] == '\0')
        {
            memcpy(temp.tp,part.argu1,3);
        }
        else
        {
            memcpy(part.argu2,temp.tp,3);
            result(part.result);
            order.push_back(part);
            memcpy(temp.tp,part.result,3);
        }
        return temp;
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error."<<endl;
        exit(0);
    }
}
Temp_pool Tprime(Node & part)
{
    clean_space();
    Node part2;
    Temp_pool temp;
    if(Is_In_firstM(txt[pos]))
    {
        part.op[0] = M();
        part.op[1] = '\0';
        part.op[2] = '\0';
        temp = F();
        memcpy(part2.argu1,temp.tp,3);
        temp = Tprime(part2);
        if(temp.tp[0] == '\0')
        {
            memcpy(temp.tp,part2.argu1,3);
        }
        else
        {
            memcpy(part2.argu2,temp.tp,3);
            result(part2.result);
            order.push_back(part2);
            memcpy(temp.tp,part2.result,3);
        }
        return temp;
    }
    else if (Is_In_followTprime(txt[pos]))
    {
        memcpy(temp.tp,"\0\0",3);
        return temp;
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error."<<endl;
        exit(0);
    }
}
Temp_pool F(void)
{
    Temp_pool temp;
    int n = 0;
    if(Is_id(n))
    {
        for(int i=pos;i<n;i++)
        {
            temp.tp[i-pos] = txt[i];
        }
        for(int j=n-pos;j<3;j++)
        {
            temp.tp[j] = '\0';
        }
        pos = n;
        return temp;
    }
    else if (Is_number(n))
    {
        for(int i=pos;i<n;i++)
        {
            temp.tp[i-pos] = txt[i];
        }
        pos = n;
        return temp;
    }
    else if (txt[pos]=='(')
    {
        pos++;
        temp = E();
        if(txt[pos] == ')')
        {
            pos++;
            return temp;
        }
        else
        {
            cout<<"F error"<<endl;
            exit(0);
        }
    }
    else
    {
        cout<<"F error"<<endl;
        exit(0);
    }
}
char A(void)
{
    clean_space();
    if(txt[pos] == '+')
    {
        pos++;
        return txt[pos-1];
    }
    else if (txt[pos] == '-')
    {
        pos++;
        return txt[pos-1];
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Operator error."<<endl;
        exit(0);
    }
}
char M(void)
{
    clean_space();
    if(txt[pos] == '*')
    {
        pos++;
        return txt[pos-1];
    }
    else if (txt[pos] == '/')
    {
        pos++;
        return txt[pos-1];
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Operator error."<<endl;
        exit(0);
    }
}
/***********算数表达式模块结束**********/

/*************语句们模块开始************/
bool Is_in_first_R()
{
    if(Is_in_first_Sprime())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_in_follow_S()
{
    if(txt[pos]=='}')
    {
        return true;
    }
    else if(Is_in_first_Sprime())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_in_first_Sprime()
{
    if(Is_id())
    {
        return true;
    }
    else if (Is_if())
    {
        return true;
    }
    else if (Is_while())
    {
        return true;
    }
    else if (txt[pos] == '{')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Is_in_follow_R()
{
    if(txt[pos]=='}')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void B(void)
{
    clean_space();
    if(txt[pos] == '{')
    {
        pos++;
        D();
        S();
        clean_space();
        if(txt[pos] == '}')
        {
            pos++;
        }
        else
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Program error. Missing a '}'."<<endl;
            exit(0);
        }
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Program error. Missing a '{'."<<endl;
        exit(0);
    }
}
void S(void)
{
    clean_space();
    if(Is_in_first_R())
    {
        R();
    }
    else if(Is_in_follow_S())
    {
        //non
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Statement error."<<endl;
        exit(0);
    }
}
void R(void)
{
    clean_space();  //这里的clean似乎没有必要
    if(Is_in_first_Sprime())
    {
        Sprime();
        R();
    }
    else if (Is_in_follow_R())
    {
        /* 属于R的follow集，不做动作 */
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Statement error."<<endl;
        exit(0);
    }
}
void Sprime(void)
{
    clean_space();
    Node part;
    Node part2;
    Temp_pool temp;
    int fman;
    int pre_index;
    if (Is_if())
    {
        pos+=2;
        part.op[0] = 'c';
        part.op[1] = 'm';
        part.op[2] = 'p';
        clean_space();
        if(txt[pos] == '(')
        {
            pos++;
            BOOL(part);
            clean_space();
            if(txt[pos] == ')')
            {
                part2.op[0] = 'j';
                part2.op[1] = 'm';
                part2.op[2] = 'p';
                memcpy(part2.argu1,"\0\0",3);
                strcpy(part2.argu1,"\0\0");
                strncpy(part2.argu1,"\0\0",3);
                memcpy(part2.argu2,"\0\0",3);
                strcpy(part2.argu2,"\0\0");
                strncpy(part2.argu2,"\0\0",3);
                order.push_back(part2);
                pre_index = order.size() - 1;
                pos++;
                //cout<<"is pushing fman"<<endl;
                Sprime(fman);
                order[pre_index].result[0] = fman/100+48;
                order[pre_index].result[1] = fman/10+48;
                order[pre_index].result[2] = fman%10+48;
            }
            else
            {
                cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Contional statement error. Missing a ')'."<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Conditional statement error. Missing a '('."<<endl;
            exit(0);
        }
    }
    else if (Is_while())
    {
        pos+=5;
        part.op[0] = 'c';
        part.op[1] = 'm';
        part.op[2] = 'p';
        clean_space();
        if(txt[pos] == '(')
        {
            pos++;
            BOOL(part);
            clean_space();
            if(txt[pos] == ')')
            { 
                part2.op[0] = 'j';
                part2.op[1] = 'm';
                part2.op[2] = 'p';
                memcpy(part2.argu1,"\0\0",3);
                memcpy(part2.argu2,"\0\0",3);
                order.push_back(part2);
                pre_index = order.size()-1;
                pos++;
                Sprime(fman);
                fman++;
                order[pre_index].result[0] = fman/100+48;
                order[pre_index].result[1] = fman/10+48;
                order[pre_index].result[2] = fman%10+48;
                fman = pre_index - 2;
                part2.result[0] = fman/100+48;
                part2.result[1] = fman/10+48;
                part2.result[2] = fman%10+48;
                order.push_back(part2);
            }
            else
            {
                cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Loop statement error. Missing a ')'."<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Loop statement error. Missing a '('."<<endl;
            exit(0);
        }
    }
    else if(Is_id(fman))    //这里一定要先判断是否为关键字if、while再判断是否为id，否则就会出现意想不到的错误
    {
        for(int i=pos;i<fman;i++)
        {
            part.argu1[i-pos] = txt[i];
        }
        for(int j=fman-pos;j<3;j++)
        {
            part.argu1[j] = '\0';
        }
        pos = fman;
        clean_space();
        if(txt[pos] == '=')
        {
            pos++;
            temp = E();
            part.op[0] = '=';
            part.op[1] = '\0';
            part.op[2] = '\0';
            memcpy(part.argu2,temp.tp,3);
            memcpy(part.result,"\0\0",3);
            clean_space();
            if(txt[pos] == ';')
            {
                order.push_back(part);
                pos++;
            }
            else
            {
                cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error. Missing a ';'."<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error. Missing a '='."<<endl;
            exit(0);
        }
    }
    else if (txt[pos] == '{')
    {
        B();
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Wrong statement."<<endl;
        exit(0);
    }
}
//布尔值定义为id、常数、表达式
void Sprime(int & n)
{
    clean_space();
    Node part;
    Node part2;
    Temp_pool temp;
    int fman;
    int pre_index;
    if (Is_if())
    {
        pos+=2;
        part.op[0] = 'c';
        part.op[1] = 'm';
        part.op[2] = 'p';
        clean_space();
        if(txt[pos] == '(')
        {
            pos++;
            BOOL(part);
            clean_space();
            if(txt[pos] == ')')
            {
                part2.op[0] = 'j';
                part2.op[1] = 'm';
                part2.op[2] = 'p';
                memcpy(part2.argu1,"\0\0",3);
                memcpy(part2.argu2,"\0\0",3);
                order.push_back(part2);
                pre_index = order.size() - 1;
                pos++;
                //cout<<"S2 is pushing man"<<endl;
                Sprime(fman);
                part2.result[0] = fman/100+48;
                part2.result[1] = (fman/10)%10+48;
                part2.result[2] = fman%10+48;
                n = order.size();
            }
            else
            {
                cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Contional statement error. Missing a ')'."<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Conditional statement error. Missing a '('."<<endl;
            exit(0);
        }
    }
    else if (Is_while())
    {
        pos+=5;
        part.op[0] = 'c';
        part.op[1] = 'm';
        part.op[2] = 'p';
        clean_space();
        if(txt[pos] == '(')
        {
            pos++;
            BOOL(part);
            clean_space();
            if(txt[pos] == ')')
            {
                part2.op[0] = 'j';
                part2.op[1] = 'm';
                part2.op[2] = 'p';
                memcpy(part2.argu1,"\0\0",3);
                memcpy(part2.argu2,"\0\0",3);
                order.push_back(part2);
                pre_index = order.size()-1;
                pos++;
                Sprime(fman);
                fman++;
                order[pre_index].result[0] = fman/100+48;
                order[pre_index].result[1] = fman/10+48;
                order[pre_index].result[2] = fman%10+48;
                fman = pre_index - 2;
                order[pre_index].result[0] = fman/100+48;
                order[pre_index].result[1] = fman/10+48;
                order[pre_index].result[2] = fman%10+48;
                order.push_back(part2);
                n = order.size();
            }
            else
            {
                cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Loop statement error. Missing a ')'."<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Loop statement error. Missing a '('."<<endl;
            exit(0);
        }
    }
    else if(Is_id(fman))    //这里一定要先判断是否为关键字if、while再判断是否为id，否则就会出现意想不到的错误
    {
        //cout<<"S' fuzhi2 doing"<<endl;
        for(int i=pos;i<fman;i++)
        {
            part.argu1[i-pos] = txt[i];
        }
        pos = fman;
        clean_space();
        if(txt[pos] == '=')
        {
            pos++;
            temp = E();
            memcpy(part.argu2,temp.tp,3);
            clean_space();
            if(txt[pos] == ';')
            {
                part.result[0] = '\0';
                part.result[1] = '\0';
                part.result[2] = '\0';
                order.push_back(part);
                n = order.size();
                pos++;
            }
            else
            {
                cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error. Missing a ';'."<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Expression error. Missing a '='."<<endl;
            exit(0);
        }
    }
    else if (txt[pos] == '{')
    {
        B();
        n = order.size();
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Wrong statement."<<endl;
        exit(0);
    }
}

//这里是布尔函数
void BOOL(Node & part)
{
    clean_space();
    Temp_pool temp;
    Node part2;
    if(Is_In_firstE(txt[pos]))
    {
        temp = E();
        memcpy(part.argu1,temp.tp,3);
        int n;
        clean_space();
        if(Is_judgement(temp,n))
        {
            pos+=n;
            memcpy(part2.op,temp.tp,3);
            memcpy(part2.argu1,"\0\0",3);
            memcpy(part2.argu2,"\0\0",3);
            temp = E();
            memcpy(part.argu2,temp.tp,3);
            memcpy(part.result,"\0\0",3);
            order.push_back(part);
            n = order.size()+2;
            part2.result[0] = (n/100)+48;
            part2.result[1] = (n/10)+48;
            part2.result[2] = (n%10)+48;
            order.push_back(part2);
        }
    }
    else if(txt[pos] == '!')
    {
        pos++;
        temp = E();
        memcpy(part.argu1,temp.tp,3);
        memcpy(part.argu2,"0\0",3);
        memcpy(part.result,"\0\0",3);
        order.push_back(part);
        memcpy(part2.op,"jne",3);
        memcpy(part2.argu1,"\0\0",3);
        memcpy(part2.argu2,"\0\0",3);
        int mm = order.size()+2;
        part2.result[0] = mm/100+48;
        part2.result[1] = mm/10+48;
        part2.result[2] = mm%10+48;
        order.push_back(part2);
    }
    else
    {
        cout<<"Error at "<<give_line_no(pos)<<".\n"<<txt.substr(pos-1,6)<<" Bool value definition error!"<<endl;
        exit(0);
    }
}
/*************语句们模块结束************/