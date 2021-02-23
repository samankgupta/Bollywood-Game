#include<iostream>
#include<string>
#include<stdio.h>
#include<iomanip>
#include<Windows.h>
#include<map>
#include<vector>
#include <time.h>
#include<fstream>

using namespace std;

void SetColor(int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void animation()
{
    for(int m=1;m<18;m++)
	{	if(m%2==0)
            cout<<"* * * * * * * * * * * * * *";
		else
			cout<<" * * * * * * * * * * * * * ";
		Sleep(160);
        cout<<string(27,'\b');
	}
}
void start()
{
    system("cls");
    SetColor(14);
    cout<<string(40,'*')<<" WELCOME TO "<<string(40,'*')<<"\n\n";
    cout<<string(37,' ')<<"THE BOLLYWOOD GAME"<<"\n";
    cout<<string(33,' ');
    animation();
}
void common(string movie,string ans,char bollywood[],string type)
{
    int bollyindex=0;
    for(int i=0;i<movie.size();i++)
    {
        movie[i]=toupper(movie[i]);
        ans[i]=movie[i];
        if(isalpha(movie[i]) && movie[i]!='A' && movie[i]!='E' && movie[i]!='I' && movie[i]!='O' && movie[i]!='U')
            movie[i]='_';
        else if(movie[i]==' ')
        {
            movie[i]='/';
            ans[i]=movie[i];
        }
    }
    while(1)
    {
        system("cls");
        cout<<string(40,'*')<<type<<"PLAYER MODE "<<string(40,'*')<<"\n\n";
        cout<<"\n\n"<<string(45,' ');
        SetColor(14);
        for (int i=0;i<9;i++)
            cout<<bollywood[i];
        SetColor(11);
        cout<<"\n\n"<<string(40,' ');
        for (int i=0;i<movie.size();i++)
            cout<<movie[i]<<' ';
        if(bollywood[8]=='/')
        {
            SetColor(12);
            cout<<"\n\n\n"<<string(43,' ')<<" YOU LOST :("<<"\n"<<string(36,' ');
            animation();
            SetColor(11);
            cout<<"\n\n\n"<<string(38,' ')<<"The Movie is ";
            SetColor(14);
            for(int i=0;i<ans.size();i++)
            {
                if(ans[i]=='/')
                    cout<<' ';
                else
                    cout<<ans[i];
            }
            SetColor(11);
            break;
        }
        if(ans == movie)
        {
            SetColor(10);
            cout<<"\n\n\n"<<string(43,' ')<<" YOU WON :)"<<"\n"<<string(36,' ');
            animation();
            SetColor(11);
            break;
        }
        cout<<"\n\n\n\n"<<string(40,' ')<<"Enter a letter : ";
        char ch;
        cin>>ch;
        int flag=0;
        for(int i=0;i<ans.size();i++)
        {
            if(ans[i]==toupper(ch))
            {
                flag=1;
                movie[i]=ans[i];
            }
        }
        if(flag==0)
        {
            bollywood[bollyindex++]='/';
        }
    }
    Sleep(500);
    cout<<"\n\n\n\n\n\n\n\n"<<string(36,' ')<<" Enter 1 to Continue : ";
    char temp;
    cin>>temp;

}
void singlePlayer()
{
    system("cls");
    SetColor(11);
    cout<<string(40,'*')<<" SINGLE PLAYER MODE "<<string(40,'*')<<"\n\n";
    Sleep(200);
    char bollywood[]={'B','O','L','L','Y','W','O','O','D'};
    string movie,ans;
    map< string, vector<string> > films;
	films["easy"];
	films["medium"];
	films["hard"];

    ifstream fin;
    string line;
    fin.open("easy.txt");
    while (fin) {

        getline(fin, line);
        films["easy"].push_back(line);
    }
    fin.close();

    fin.open("medium.txt");
    while (fin) {

        getline(fin, line);
        films["medium"].push_back(line);
    }
    fin.close();

    fin.open("hard.txt");
    while (fin) {

        getline(fin, line);
        films["hard"].push_back(line);
    }
    fin.close();

    cout<<"\n\n"<<string(15,' ')<<"1) Easy"<<"\n"<<string(15,' ')<<"2) Medium"<<"\n"<<string(15,' ')<<"3) Hard"<<"\n\n"<<string(15,' ')<<"Enter Your Choice : ";
    int choice;
    cin>>choice;
    srand(time(NULL));
    if (choice==1)
    {
        int len=films["easy"].size();
        movie=films.at("easy")[(rand()%len)];
    }
    else if (choice==2)
    {
        int len=films["medium"].size();
        movie=films.at("medium")[(rand()%len)];
    }
    else if (choice==3)
    {
        int len=films["hard"].size();
        movie=films.at("hard")[(rand()%len)];
    }
    ans=movie;
    common(movie,ans,bollywood," SINGLE ");
}
void multiPlayer()
{
    system("cls");
    SetColor(11);
    cout<<string(40,'*')<<" MULTI PLAYER MODE "<<string(40,'*')<<"\n\n";
    Sleep(200);
    char bollywood[]={'B','O','L','L','Y','W','O','O','D'};
    string movie,ans;
    cout<<"\n\n"<<string(15,' ')<<"1) Enter A Movie Name : ";
    cin.ignore();
    getline(cin,movie);
    ans=movie;
    common(movie,ans,bollywood," MULTI ");
}
void addMovies()
{
    system("cls");
    cout<<string(40,'*')<<" ADMIN AREA "<<string(40,'*')<<"\n\n";
    Sleep(200);
    int choice;
    cout<<"\n\n"<<string(15,' ')<<"1) Add Easy Movies"<<"\n"<<string(15,' ')<<"2) Add Medium Movies"<<"\n"<<string(15,' ')<<"3) Add Hard Movies"<<"\n\n"<<string(15,' ')<<"Enter Your Choice : ";
    cin>>choice;
    string movie;
    cin.ignore();
    if(choice==1)
    {
        cout<<"\n\n"<<string(15,' ')<<"Enter an Easy Movie : ";
        getline(cin,movie);
        ofstream file;
        file.open ("easy.txt", std::ios_base::app);
        file<<'\n' << movie;
        file.close();
    }
    else if(choice==2)
    {
        cout<<"\n\n"<<string(15,' ')<<"Enter a Medium Movie : ";
        getline(cin,movie);
        ofstream file;
        file.open ("medium.txt", std::ios_base::app);
        file<<'\n' << movie;
        file.close();
    }
    else if(choice==3)
    {
        cout<<"\n\n"<<string(15,' ')<<"Enter a Hard Movie : ";
        getline(cin,movie);
        ofstream file;
        file.open ("hard.txt", std::ios_base::app);
        file<<'\n' << movie;
        file.close();
    }
    Sleep(200);
    cout<<"\n\n\n"<<string(36,' ')<<"Movie Added!"<<"\n\n"<<string(32,' ')<<" Enter 1 to Exit : ";
    char temp;
    cin>>temp;
}
void viewMovies()
{
    system("cls");
    cout<<string(40,'*')<<" ADMIN AREA "<<string(40,'*')<<"\n\n";
    Sleep(200);
    int choice;
    string line;
    cout<<"\n\n"<<string(15,' ')<<"1) View Easy Movies"<<"\n"<<string(15,' ')<<"2) View Medium Movies"<<"\n"<<string(15,' ')<<"3) View Hard Movies"<<"\n\n"<<string(15,' ')<<"Enter Your Choice : ";
    cin>>choice;
    cin.ignore();
    if(choice==1)
    {
        cout<<"\n\n"<<string(15,' ')<<"Easy Movies"<<"\n";
        ifstream fin;
        fin.open("easy.txt");
        while (fin)
        {
            if( fin.eof() ) break;
            getline(fin, line);
            cout <<string(15,' ')<<line << endl;
        }
        fin.close();
    }
    else if(choice==2)
    {
        cout<<"\n\n"<<string(15,' ')<<"Medium Movies"<<"\n";
        ifstream fin;
        fin.open("medium.txt");
        while (fin)
        {
            if( fin.eof() ) break;
            getline(fin, line);
            cout <<string(15,' ')<<line << endl;
        }
        fin.close();
    }
    else if(choice==3)
    {
        cout<<"\n\n"<<string(15,' ')<<"Hard Movies"<<"\n";
        ifstream fin;
        fin.open("hard.txt");
        while (fin)
        {
            if( fin.eof() ) break;
            getline(fin, line);
            cout <<string(15,' ')<<line << endl;
        }
        fin.close();
    }
    Sleep(1000);
    cout<<"\n\n\n"<<string(36,' ')<<" Enter 1 to Exit : ";
    char temp;
    cin>>temp;
}
void adminArea()
{
    system("cls");
    SetColor(11);
    cout<<string(40,'*')<<" ADMIN AREA "<<string(40,'*')<<"\n\n";
    Sleep(200);
    string pass="temp";
    while(pass!="password")
    {
        system("cls");
        cout<<string(40,'*')<<" ADMIN AREA "<<string(40,'*')<<"\n\n";
        cout<<"\n\n"<<string(20,' ')<<"Enter Password / Enter 0 to Exit : ";
        cin>>pass;
        if(pass=="0")
            return;
        if(pass=="password")
        {
            cout<<"\n\n\n\n"<<string(40,' ')<<" WELCOME !";
            Sleep(1000);
            system("cls");
            cout<<string(40,'*')<<" ADMIN AREA "<<string(40,'*')<<"\n\n";
        }
    }
    int choice;
    cout<<"\n\n"<<string(15,' ')<<"1) View Movies"<<"\n"<<string(15,' ')<<"2) Add Movies"<<"\n"<<string(15,' ')<<"3) Exit"<<"\n\n"<<string(15,' ')<<"Enter Your Choice : ";
    cin>>choice;
    if (choice==1)
    {
        viewMovies();
    }
    else if (choice==2)
    {
        addMovies();
    }
    else
    {
        return;
    }
}

int main()
{
    while(1)
    {
        start();
        int ch, choice;
        Sleep(150);
        cout<<"\n\n"<<string(15,' ')<<"1) Play Bollywood Game"<<"\n"<<string(15,' ')<<"2) Admin Area"<<"\n"<<string(15,' ')<<"3) Exit"<<"\n\n"<<string(15,' ')<<"Enter Your Choice : ";
        cin>>ch;
        if(ch==1)
        {
            system("cls");
            cout<<string(40,'*')<<" WELCOME TO "<<string(40,'*')<<"\n\n"<<string(37,' ')<<"THE BOLLYWOOD GAME"<<"\n"<<string(33,' ');
            cout<<"\n\n"<<string(15,' ')<<"1) Play Single Player"<<"\n"<<string(15,' ')<<"2) Play Multi Player"<<"\n"<<string(15,' ')<<"3) Exit"<<"\n\n"<<string(15,' ')<<"Enter Your Choice : ";
            cin>>choice;
            if (choice==1)
            {
                singlePlayer();
            }
            else if (choice==2)
            {
                multiPlayer();
            }
            else
            {
                break;
            }
        }
        else if(ch==2)
        {
            system("cls");
            adminArea();
        }
        else
        {
            break;
        }
    }
}
