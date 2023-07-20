#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <wingdi.h>
//#include <poco/NET/HTTPRequest.h> http://parsamabani.pythonanywhere.com/reminder/check/?student_id=401521327
//#include <SFML/Network.hpp>
//#include <curl>
//#include <curl/curl.h>

#include <bits/stdc++.h>
//#include "C:\Users\Kiarash\Desktop\Graphics Header File Setup for CodeBlocks\winbgim.h"
#include <windows.h>
//#include "C:\Users\Kiarash\Desktop\Graphics Header File Setup for CodeBlocks\graphics.h"
using namespace std;
#define MAX_INPUT 365
//global shit
char monthname[12][12]={"January", "February" , "March", "April", "May", "June", "July", "August", "September", "October", "November" , "December"};
char dayname[7][4]={ "Sun" , "Mon","Tue", "Wen", "Thu", "Fri", "Sat"};

struct datastoring{
	int notecounter=0;
	int notedate [MAX_INPUT];//left to digit: month
	int Repetive [7];
	char RN[7][1000];
	char note[MAX_INPUT][1000];
	//bool flag[12][31]={{0}};
	int Repetivecounter=0;
	int flagcounter=0;
	int flagdate[MAX_INPUT];
	int reminder[MAX_INPUT];
	int remindercounter=0;
	char friendname[MAX_INPUT][100];
	int friendbirthday[MAX_INPUT];
	char phonenumber[MAX_INPUT][14];
	int friendcounter=0;
} data;
//struct datastoring data;

struct datastoringtemp{
	int notecounter=0;
	int notedate [MAX_INPUT];//left to digit: month
	char note[MAX_INPUT][1000];
	int Repetive [7];
	char RN[7][1000];
	int Repetivecounter=0;
	//bool flag[12][31]={{0}};
	int flagcounter=0;
	int flagdate[MAX_INPUT];
} tempdata;
//struct datastoringtemp tempdata;
int order[MAX_INPUT];
//int orderfriend[MAX_INPUT];
int temporder[MAX_INPUT];
//functions:
void swipe (int *a, int *b)
{
	int c=*a;
	*a = *b;
	*b = c;
}
void sortnote ()
{
	void swipe (int *a, int *b);
	for(int i=0; i< data.notecounter; i++)
	{
		for(int j=i; j< data.notecounter; j++)
		{
			if(data.notedate[order[i]]/100 > data.notedate[order[j]]/100 )
			{
				//nasty switch
				swipe(&order[i], &order[j]);
			}
			else if( data.notedate[order[i]]/100 == data.notedate[order[j]]/100 && data.notedate[order[i]]%100 > data.notedate[order[j]]%100)
			{
				swipe(&order[i], &order[j]);
			}
		}
	}
}
void sortflag(int date[], int lim)
{
	void swipe (int *a, int *b);
	for(int i=0; i<lim; i++)
	{
		for(int j=i; j< lim; j++)
		{
			if(date[i]/100 > date[j]/100)
				swipe(&date[i], &date[j]);
			else if(date[i]%100 > date[j]%100)
				swipe(&date[i], &date[j]);
		}
	}
}
void sorttempnote()
{
	void swipe (int *a, int *b);
	for(int i=0; i< tempdata.notecounter; i++)
	{
		for(int j=i; j< tempdata.notecounter; j++)
		{
			if(tempdata.notedate[temporder[i]]/100 > tempdata.notedate[temporder[j]]/100 )
			{
				//nasty switch
				swipe(&temporder[i], &temporder[j]);
			}
			else if( tempdata.notedate[temporder[i]]/100 == tempdata.notedate[temporder[j]]/100 && tempdata.notedate[temporder[i]]%100 > tempdata.notedate[temporder[j]]%100)
			{
				swipe(&temporder[i], &temporder[j]);
			}
		}
	}
}


void readtxt ()
{
	char temp[1000];
	ifstream extractdata("data.txt");
	
	if(extractdata.is_open())
	{	
		while(extractdata.getline(temp,1000))
		{
			
			if(temp[0]=='n')
			{

				data.notedate[data.notecounter]= ((temp[1]-48)*10 + (temp[2]-48))*100 + ((temp[3]-48)*10 + (temp[4]-48));
				
				for (int i=0; temp[5+i]; i++)
				{
					data.note[data.notecounter][i]=temp[5+i];
				}
				data.notecounter ++;
			}
			else if (temp[0]=='f')
			{
				data.flagdate[data.flagcounter]= ((temp[1]-48)*10 + (temp[2]-48))*100 + ((temp[3]-48)*10 + (temp[4]-48));
				data.flagcounter ++;
			}
			else if (temp[0]=='r')
			{
				data.Repetive[data.Repetivecounter] = temp[1] - 48;
				for (int i=0; temp[2+i]; i++)
				{
					data.RN[data.Repetivecounter][i]=temp[2+i];
				}
				data.Repetivecounter ++;

			}
			else if(temp[0]=='s')
			{
				data.reminder[data.remindercounter] = ((temp[1]-48)*10 + (temp[2]-48))*100 + ((temp[3]-48)*10 + (temp[4]-48));
				data.remindercounter ++ ;
			}
			else if(temp[0] == 'd') // friend = doost
			{
				int k;
				data.friendbirthday[data.friendcounter] = ((temp[1]-48)*10 + (temp[2]-48))*100 + ((temp[3]-48)*10 + (temp[4]-48));
				for(k=5; temp[k]!='#'; k++) data.friendname[data.friendcounter][k - 5] = temp[k];
				int l;
				for( l=k+1 ; temp[l]!='#'; l++) data.phonenumber[data.friendcounter][l - k - 1] = temp[l]; 
				data.friendcounter ++;
			}
		}
		extractdata.close();
	}
	else
	{
		ofstream createfile("data.txt");
		createfile.close();
	}
	return ;
}
void emptybar(int left, int top, int right, int down)
{
	line(left, top, left, down);
	line(left , top, right , top);
	line(right, top, right, down);
	line(right ,down, left, down );
	return ;
}
string marktoday ( int *a)
{
	struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    string s = asctime(ptr);
	string month = (s.substr(4,3));
	string day = s.substr (8, 2); 
	for(int i=0; i<12; i++)
	{
		int f=0;
		for(int j=0; j<3; j++)
		{
			if(month[j]!=monthname[i][j])
				f=1;
		}
		if(f==0)
		{
			*a=i;
			return day;
		}
			
	}
	return "";
}
void calenderframe()
{
	void sortnote();
	//sortnote();
	void sorttempnote();
	sorttempnote();
	void sortflag(int date[], int lim);
	//sortflag (data.flagdate, data.flagcounter);
	sortflag (tempdata.flagdate, tempdata.flagcounter);
	string marktoday ( int *a);
	void emptybar(int left, int top, int right, int down);
	
	initwindow(1920, 1080, "2023");
	
	//readimagefile("C:/Users/Kiarash/Pictures/creed-bratton-post.png",0,0,1920,1080);
	//readimagefile("C:/Users/Kiarash/Pictures/4986d7c7b927ef7dfc9955f1d05267b7.jpg",0,0,1920,1080); //STORM TROOPER
	
	readimagefile("e6d70d313a98a6b3551c3ddff66caafe.jpg",0,0,1920,1080); //DARTH VADER
	delay(4000);
	//readimagefile("C:/Users/Kiarash/Pictures/High_resolution_wallpaper_background_ID_77701587033.jpg",0,0,1920,1080); //PATERN
	// int points[]={320,150,440,340,230,340,320,150};
	// fillpoly(4, points);
	//dpm= day per month
	int dpm[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 , 31 };
	settextstyle(5, HORIZ_DIR, 4);
	int length;
	//setbkcolor(RGB(20, 20, 20));
	
	int k=0, tempi;
	//month headers
	for(int i=0; i<12; i++)
	{
		if(i>5){
			k=540;
			tempi=i-6;
		}
		else
			tempi=i;
			
		//length=stringlength(monthname[i]);
		length= textwidth(monthname[i]);
		length/=2;
		//setcolor(RED);
		//bar(120+ 296*i, 25, 320+ 296*i, 75);
		HDC hDC;
     	hDC = GetDC(NULL);
		COLORREF color = GetPixel(hDC, 220+ 296*tempi - length, 40 + k);
		setbkcolor(RGB(GetRValue(color), GetGValue(color), GetBValue(color)));
		if (i==4) setbkcolor(RGB(100, 100, 100));
		outtextxy(220+ 296*tempi - length, 40 + k , monthname[i]);
		emptybar(90+ 296*tempi, 25+k, 340+ 296*tempi, 90+k );
	}
	//day headers
	//starts in 115 and ends in 470
	settextstyle(5, HORIZ_DIR, 1);
	length=textwidth(dayname[0]);
	k=0;
	//version 1
	
	// for(int i=0; i<12; i++)	
	// {
	// 	if(i>5){
	// 		k=540;
	// 		tempi=i-6;
	// 	}
	// 	else
	// 		tempi=i;
	// 	for( int j=0; j<7; j++)
	// 	{
	// 		outtextxy(88-length + 296*tempi, 110 + j*60 + k, dayname[j]);
	// 	}
	// }
	//version 2
	for( int j=0; j<7; j++)
	{
		HDC hDC;
     	hDC = GetDC(NULL);
		COLORREF color = GetPixel(hDC, 70-length, 110 + j*60);
		setbkcolor(RGB(GetRValue(color), GetGValue(color), GetBValue(color)));
		outtextxy(70-length , 110 + j*60 , dayname[j]);
	}
	for( int j=0; j<7; j++)
	{
		HDC hDC;
     	hDC = GetDC(NULL);
		COLORREF color = GetPixel(hDC,70-length,110 + j*60 + 540);
		setbkcolor(RGB(GetRValue(color), GetGValue(color), GetBValue(color)));
		outtextxy(70-length , 110 + j*60 + 540 , dayname[j]);
	}


	//puting days
	int tomonth;
	string today= marktoday (&tomonth);
	int place=0, notectr=0, flagctr=0, tempnotectr=0, tempflagctr=0, tempRctr=0, Rctr=0;
	k=0;
	int  flagflag=0;
	for(int i=0; i<12; i++)
	{
		place%=7;
		if(i>5){
			k=540;
			tempi=i-6;
		}
		else
			tempi=i;
		
		for(int j=0; j<dpm[i]; j++)
		{
			int flag =0;
			string s=to_string(j+1);
			char *c=&s[0];
			if(tomonth==i && s==today)
			{
				setcolor(RED);
				ellipse(80 + 40 * ((place/7) +1) + 296*tempi+ textwidth(c)/2, (place%7)*60 + 110 + k +textheight(c)/2 , 0, 360, textheight(c),textwidth(c));
				setcolor(WHITE);
				flag =1;
			}

			if ((data.notecounter > notectr) && (data.notedate[order[notectr]]/100 == i) && (data.notedate[order[notectr]] % 100 == j))
			{
				setcolor(CYAN);
				setfillstyle(1,CYAN);
				bar(80 + 40 * ((place/7) +1) + 296*tempi , (place%7)*60 + 110 + k + 10 , 80 + 40 * ((place/7) +1) + 296*tempi + textwidth(c), (place%7)*60 + 110 + k + 30);
				setcolor(WHITE);
				notectr ++;
			}
			for (int l=0; l< data.Repetivecounter; l++){
				if ((place%7 == data.Repetive[l] - 1))
				{
					setcolor(CYAN);
					setfillstyle(1,CYAN);
					bar(80 + 40 * ((place/7) +1) + 296*tempi , (place%7)*60 + 110 + k + 10 , 80 + 40 * ((place/7) +1) + 296*tempi + textwidth(c), (place%7)*60 + 110 + k + 30);
					setcolor(WHITE);
				}
			}
			for (int l=0; l< tempdata.Repetivecounter; l++){
				if ((place%7 == tempdata.Repetive[l] - 1))
				{
					setcolor(CYAN);
					setfillstyle(1,CYAN);
					bar(80 + 40 * ((place/7) +1) + 296*tempi , (place%7)*60 + 110 + k + 10 , 80 + 40 * ((place/7) +1) + 296*tempi + textwidth(c), (place%7)*60 + 110 + k + 30);
					setcolor(WHITE);
				}
			}
			if ((tempdata.notecounter > tempnotectr) && (tempdata.notedate[temporder[tempnotectr]]/100 == i) && (tempdata.notedate[temporder[tempnotectr]] % 100 == j))
			{
				setcolor(CYAN);
				setfillstyle(1,CYAN);
				bar(80 + 40 * ((place/7) +1) + 296*tempi , (place%7)*60 + 110 + k + 10 , 80 + 40 * ((place/7) +1) + 296*tempi + textwidth(c), (place%7)*60 + 110 + k + 30);
				setcolor(WHITE);
				tempnotectr ++;
			}

			if ((data.flagcounter > flagctr) && (data.flagdate[flagctr]/100 == i) && (data.flagdate[flagctr] % 100 == j))
			{
				setcolor(YELLOW);
				setfillstyle(1,YELLOW);
				fillellipse(80 + 40 * ((place/7) +1) + 296*tempi + textwidth(c) + 5 , (place%7)*60 + 110 + k - textheight(c)+10, 5, 5);
				setcolor(WHITE);
				flagctr ++;
			}
			if ((tempdata.flagcounter > tempflagctr) && (tempdata.flagdate[tempflagctr]/100 == i) && (tempdata.flagdate[tempflagctr] % 100 == j))
			{
				setcolor(YELLOW);
				setfillstyle(1,YELLOW);
				fillellipse(80 + 40 * ((place/7) +1) + 296*tempi + textwidth(c) + 5 , (place%7)*60 + 110 + k - textheight(c)+10, 5, 5);
				setcolor(WHITE);
				tempflagctr ++;
			}
			if (i==4 || i==10 )
			{
				setbkcolor(RGB(10, 10, 10));
			}
			else if (i==11 && j==15) setbkcolor(RGB(10, 10, 10));
			else
			{
				HDC hDC;
				hDC = GetDC(NULL);
				COLORREF color = GetPixel(hDC, 80 + 40 * ((place/7) +1) + 296*tempi, (place%7)*60 + 110 + k);
				setbkcolor(RGB(GetRValue(color), GetGValue(color), GetBValue(color)));
			}
			/* colored day
			if(flagflag == 1)
			{
				setcolor(GREEN);
			}
			if ( flag == 1)
			{
				setcolor(BLUE);
				flagflag=1;
			}
			*/
			outtextxy (80 + 40 * ((place/7) +1) + 296*tempi, (place%7)*60 + 110 + k, c);
			place++;
		}
	}
	//temp
	getch();
	closegraph();
	return ;
}


void inputedit (char c[])
{
	for(int i=0; c[i]!='\0'; i++)
	{
		if(isupper(c[i]))
		{
			c[i]=tolower(c[i]);
		}
	}
	return;
}
void addnote()
{
	int month, day;
	cout << "add your note : "; cin.getline(tempdata.note[tempdata.notecounter], 100);
	cout << "month number : "; cin >> month; month --;
	cout << "day number : "; cin >> day;day --;
	tempdata.notedate[tempdata.notecounter]=month*100 + day;
	tempdata.notecounter ++;
	return ;
}
void addflag()
{
	int month, day;
	cout << "month number : "; cin >> month; month --;
	cout << "day number : "; cin >> day;day --;
	tempdata.flagdate[tempdata.flagcounter]=month*100 + day;
	tempdata.flagcounter ++;
	return ;
}
void printnotes()
{
	string s;
	for(int i=0; i<30; i++)
		s+='-';
	cout << "Temp Notes:" << endl;

	for(int i=0; i< tempdata.notecounter; i++)
	{
		printf("Date: %d%s%d\n%s\n",tempdata.notedate[temporder[i]]/100 +1 ,"/",tempdata.notedate[temporder[i]]%100 +1 , tempdata.note[temporder[i]]);
		cout << s <<endl;
	}
	cout << "Saved Notes:" << endl;

	for(int i=0; i< data.notecounter; i++)
	{
		printf("Date: %d%s%d\n%s\n",data.notedate[order[i]]/100 +1 ,"/",data.notedate[order[i]]%100 +1 , data.note[order[i]]);
		cout << s <<endl;
	}
	cout << "Temp Repetive Notes" << endl;
	for(int i=0; i< tempdata.Repetivecounter; i++)
	{
		printf("Day of Week: %s\n%s\n",dayname[tempdata.Repetive[i] -1] , tempdata.RN[i]);
		cout << s <<endl;
	}
	cout << "Saved Repetive Notes" << endl;
	for(int i=0; i< data.Repetivecounter; i++)
	{
		printf("Day of Week: %s\n%s\n",dayname[data.Repetive[i] - 1] , data.RN[i]);
		cout << s <<endl;
	}
	
	return ;

}

int findnote(int a)
{
	for(int i=0; i<data.notecounter; i++)
	{
		if(data.notedate[i]==a)
			return i;
	}
	return -1;
	
}
int findtempnote(int a)
{
	for (int i=0; i<tempdata.notecounter; i++)
		if(tempdata.notedate[i]==a)
			return i;
	return -1;
}
void printnote()
{
	cout << "if the note is repetive, enter 0, otherwise, enter 1: ";int l; cin >> l;
	if(l == 1)
	{	
		int month, day, k; 
		cout << "month number : "; cin >> month; month --;
		cout << "day number : "; cin >> day;day --;
		cout << "if the note is saved, enter 1 otherwise enter 0 : "; cin >> k;
		if (k==1) {cout << data.note[findnote(month*100 + day)] << endl; return;}
		else if (k==0) {cout << tempdata.note[findtempnote(month*100 + day)] << endl; return;}
		cout << "note doesn't exist"; return;
	}
	if(l == 0)
	{
		int day , k;
		cout << "enter the number of day : "; cin >> day;;
		cout << "if the note is saved, enter 1 otherwise enter 0 : "; cin >> k;
		if( k == 0) {for(int i=0; i< tempdata.Repetivecounter; i++) if(tempdata.Repetive[i] == day) {cout << tempdata.RN[i] << endl; return ;}}
		if( k == 1) {for(int i=0; i< data.Repetivecounter; i++) if(data.Repetive[i] == day) {cout << data.RN[i] << endl; return ;}}
	}
}
void deletorder(int a[], int n, int key)
{
	int i;
	for(i=0; i<n; i++)
		if(a[i] == key)
			break;
	int c= a[i];
	for(int j=i+1; j<n; j++)
	{
		a[j-1]=a[j];
	}
	a[n-1]=c;
}
void deletenote ()
{
	int month, day, k; 
	cout << "month number : "; cin >> month; month --;
	cout << "day number : "; cin >> day;day --;
	cout << "if the note is saved, enter 1 otherwise enter 0 "; cin >> k;
	if (k==1) 
	{
		int l=findnote(month*100 + day);
		data.notedate[l] = 0;
		deletorder(order, data.notecounter, l);
		data.notecounter--;
		return;
	}
	if (k==0)
	{
		int l=findtempnote(month*100 + day);
		tempdata.notedate[l]=0;
		deletorder(temporder, tempdata.notecounter, l);
		tempdata.notecounter--;
		return ;
	}
	cout << "note doesn't exist"; return;

}
int findflag(int key, int date[], int lim)
{
	for(int i=0; i< lim; i++)
	{
		if(date[i] == key)
			return i;
	}
	return -1;
}
void unflag()
{
	int month, day, k; 
	cout << "month number : "; cin >> month; month --;
	cout << "day number : "; cin >> day;day --;
	cout << "if the note is saved, enter 1 otherwise enter 0 : "; cin >> k;
	if(k==1)
	{
		int l= findflag(month*100 + day, data.flagdate, data.flagcounter);
		data.flagdate[l] = 1130;
		sortflag(data.flagdate, data.flagcounter);
		data.flagcounter--;
		return;
	}
	if(k==0)
	{
		int l= findflag(month*100 + day, tempdata.flagdate, tempdata.flagcounter);
		tempdata.flagdate[l] = 1130;
		sortflag(tempdata.flagdate, tempdata.flagcounter);
		tempdata.flagcounter--;
		return;
	}
	cout << "flag doesn't exist"; return;

}
void save ()
{
	for(int i=data.notecounter; i< data.notecounter + tempdata.notecounter; i++)
	{
		data.notedate[i] = tempdata.notedate[ i - data.notecounter];
		tempdata.notedate[ i - data.notecounter] = 0;
		for(int j=0; tempdata.note[i - data.notecounter][j]!='\0'; j++) data.note[i][j] = tempdata.note[i - data.notecounter][j];
	}
	data.notecounter +=tempdata.notecounter;
	tempdata.notecounter = 0;
	for(int i=data.flagcounter; i< data.flagcounter + tempdata.flagcounter; i++)
	{
		data.flagdate[i] = tempdata.flagdate[ i - data.flagcounter];
		tempdata.flagdate[ i - data.flagcounter] = 0;
	}
	data.flagcounter +=tempdata.flagcounter;
	tempdata.flagcounter = 0;
	for(int i=data.Repetivecounter; i< data.Repetivecounter + tempdata.Repetivecounter; i++)
	{
		data.Repetive[i] = tempdata.Repetive[ i - data.Repetivecounter];
		tempdata.Repetive[ i - data.Repetivecounter] = 0;
		for(int j=0; tempdata.RN[i - data.Repetivecounter][j]!='\0'; j++) data.RN[i][j] = tempdata.RN[i - data.notecounter][j];
	}
	data.Repetivecounter +=tempdata.Repetivecounter;
	tempdata.Repetivecounter = 0;
	//infile sorted
	sortnote();
	sortflag(data.flagdate, data.flagcounter);
	ofstream write("data.txt");
	for(int i=0; i< data.notecounter; i++)
	{
		if(data.notedate[order[i]] / 100 == 0 && data.notedate[order[i]] % 100 <10)
			write <<'n' << "000" <<data.notedate[order[i]] << data.note[order[i]] << endl;
		else if(data.notedate[order[i]] / 100 == 0 && data.notedate[order[i]] % 100 >9)
			write <<'n' << "00" <<data.notedate[order[i]] << data.note[order[i]] << endl;
		else if(data.notedate[order[i]] / 100 < 10)
			write <<'n' << '0' << data.notedate[order[i]] << data.note[order[i]] << endl;
		else
			write <<'n' << data.notedate[order[i]] << data.note[order[i]] << endl;
	}

	for(int i=0; i< data.Repetivecounter; i++)
	{
		write << 'r' <<data.Repetive[i] << data.RN[i]<<endl;
	}

	for(int i=0; i< data.flagcounter; i++)
	{
		if(data.flagdate[i] / 100 == 0 && data.flagdate[i] % 100 <10)
			write <<'f' << "000" <<data.flagdate[i] << endl;
		else if(data.flagdate[i] / 100 == 0 && data.flagdate[i] % 100 >9)
			write <<'f' << "00" <<data.flagdate[i] << endl;
		else if(data.flagdate[i] / 100 < 10)
			write <<'f' << '0' << data.flagdate[i] <<endl;
		else
			write <<'f' << data.flagdate[i] <<endl;
	}
	for(int i=0; i< data.remindercounter; i++)
	{
		if(data.reminder[i] / 100 == 0 && data.reminder[i] % 100 <10)
			write <<'s' << "000" <<data.reminder[i] << endl;
		else if(data.reminder[i] / 100 == 0 && data.reminder[i] % 100 >9)
			write <<'s' << "00" <<data.reminder[i] << endl;
		else if(data.reminder[i] / 100 < 10)
			write <<'s' << '0' << data.reminder[i] <<endl;
		else
			write <<'s' << data.reminder[i] <<endl;
	}
	for( int i=0; i<data.friendcounter; i++)
	{
		if(data.friendbirthday[i] / 100 == 0 && data.friendbirthday[i] % 100 <10)
			write <<'d' << "000" <<data.friendbirthday[i] ;
		else if(data.friendbirthday[i] / 100 == 0 && data.friendbirthday[i] % 100 >9)
			write <<'d' << "00" <<data.friendbirthday[i];
		else if(data.friendbirthday[i] / 100 < 10)
			write <<'d' << '0' << data.friendbirthday[i];
		else
			write <<'d' << data.friendbirthday[i];
		write << data.friendname[i] << '#' <<data.phonenumber[i] << '#' << endl;
	}
	write.close();
	return ;
}
void reminder_check()
{
	int k;
	string s = marktoday(&k);
	for (int i=0; i<data.remindercounter; i++)
	{
		if(to_string((data.reminder[i] %100)+1) == s && data.reminder[i] / 100 == k)
		{
			system ("crazy.exe");
    		system ("pause");
			data.reminder[i] = 1130;
			sortflag(data.reminder, data.remindercounter);
			data.remindercounter--;
			return;
		}		
	}
}
void birthday_check()
{
	int k;
	string s = marktoday(&k);
	for (int i=0; i<data.friendcounter; i++)
	{
		if(to_string((data.friendbirthday[i] %100)+1) == s && data.friendbirthday[i] / 100 == k)
		{
			cout << "TODAY IS YOUR FRIENDS BIRTHDAY!\ndue to window's dumbassness, this feature is available on linux" << endl;
			// system ("friend.exe");
    		// system ("pause");
			// return;
		}		
	}
}
void sendrequest()
{
	int month , k, day; 
	cout << "month number : "; cin >> month; month--;
	cout << "day number : "; cin >> day; day --;
	string s = marktoday(&k);
	data.reminder[data.remindercounter] = (month)*100 + day;
	data.remindercounter ++;
	return;
}
void repetive()
{
	cout << "add your note : "; cin.getline((tempdata.RN[tempdata.Repetivecounter]), 100);
	cout <<"Number of Day of week: "; cin >> tempdata.Repetive[tempdata.Repetivecounter];
	tempdata.Repetivecounter ++;
}
void showrn()
{
	int dayofweek, k;
	cout << "If the repetive note is saved, enter 1 otherwise enter 0: "; cin >> k;
	cout << "Enter the day of week: ";cin >> dayofweek;
	if(k==0){
		for (int l=0; l< tempdata.Repetivecounter; l++){
			if(tempdata.Repetive[l] == dayofweek)
			{
				cout << tempdata.RN[l];
				return ;
			}
		}
	}
	if(k==1){
		for (int l=0; l< data.Repetivecounter; l++){
			if(data.Repetive[l] == dayofweek)
			{
				cout << data.RN[l] << endl;
				return ;
			}
		}
	}
	return ;
}
bool digit_test(int start, int end, char c[])
{
	int flag=0; 
	for(int i=start; i<end; i++)
		if((isdigit(c[i])) == 0)
			return 0;
	return 1;
}
bool phonenumber_validation(char c[])
{
	int length;for (length=0; c[length]!='\0'; length++);
	if(length == 13)
	{
		if(c[0]=='+' && c[1] == '9' && c[2] == '8' && c[3] == '9' && c[4] == '1' && c[5] == '2' && digit_test(6, length, c))
			return 1;
		else 
			return 0;
	}
	if(length == 12)
	{
		if(c[0]=='9' && c[1] == '8' && c[2]=='9' && c[3]=='1' && c[4]=='2' && digit_test(5, length, c)) return 1;
		else return 0;
	}
	if(length == 11)
	{
		if(c[0]=='0' && c[1] == '9' && c[2]=='1' && c[3]=='2' && digit_test(4, length, c)) return 1;
		else return 0;
	}
	return 0;
}
void addFriend()
{
	int month, day, counter=0;
	cout << "Enter your friend's name: "; cin.getline(data.friendname[data.friendcounter], 100);
	cout << "Now the Birthday\n"; cout << "Number of month : ";cin >> month; month--; cout << "Number of day : "; cin >> day; day--;
	cout << "Enter your friend's phone number : "; scanf("%s",data.phonenumber[data.friendcounter]);
	while (phonenumber_validation(data.phonenumber[data.friendcounter]) == 0)
	{
		if(counter > 2)
			printf("Help: This program Only supports 912 and doesn't support 937 or ...\n");
		cout << "Error. Phone number format is incorrect. Enter the phone number again : "; scanf("%s",data.phonenumber[data.friendcounter]);
		counter ++;
	}
	data.friendbirthday[data.friendcounter] = month*100 + day;
	data.friendcounter ++; 
}
void remove_friend()
{
	string s;
	for(int i=0; i<50; i++) s+='-';
	int code;
	for(int i=0; i< data.friendcounter; i++)
	{
		printf("Name : %s   code : %d\nPhone number : %s\nDate of birth : %d/%d\n", data.friendname[i], i, data.phonenumber[i], data.friendbirthday[i]/100, data.friendbirthday[i]%100);
		cout << s << endl;
	}
	cout << "if you regret removing a friend, enter -1, otherwise, enter the code of your friend you want to remove : ";cin >> code;
	if(code == -1) return ;
	for( int i= code + 1; i<data.friendcounter; i++)
	{
		snprintf(data.phonenumber[i-1], 14, "%s" ,data.phonenumber[i]);
		snprintf(data.friendname[i-1], 100, "%s", data.friendname[i]);
		data.friendbirthday[i-1] = data.friendbirthday[i]; 
	}
	data.friendcounter --;
	return ;
}
int main()
{
	for (int w=0; w<MAX_INPUT; w++)	
	{
		order[w]=w;
		temporder[w]=w;
	}

	readtxt();
	calenderframe();
	char c[20];
	while(c[0]!='l')
	{
		cout << "Waiting for Commands..." << endl;

		cin.getline(c, 20);
		inputedit(c);
		string s(c);
		if( s == "add note" ) addnote();
		else if( s == "show all") printnotes();
		else if( s == "show") printnote();
		else if( s == "flag") addflag();
		else if( s == "delete note") deletenote();
		else if( s =="unflag") unflag();
		else if( s == "save") save();
		else if( s == "calender") calenderframe();
		else if( s == "exit") break;
		else if( s == "add reminder") sendrequest();
		else if( s == "add repetive note") repetive();
		else if( s == "show repetive note") showrn();
		else if( s == "add friend") addFriend();
		else if( s == "remove friend") remove_friend();
		else	{system("Color 0C"); cout << "Unknown Command" << endl; system("Color 0F");}
		reminder_check();
		birthday_check();
	}

	
	return 0;
}