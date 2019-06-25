#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <time.h>
//#include <values.h>
#include <stdlib.h>
#include <string.h>

#include <string.h>
#include <ctype.h>

using namespace std;

const int Up =72;
const int Down =80;
const int UP =72+128;
const int DOWN =80+128;

const int F3=61+128;
const int F2=60+128;
const int F1=59+128;
const int ENTER =13;
const int ESC =27;
const int MAX=3;

int bx1=10,by1=14,bx2=105,by2=82-65,bclor=14;//x=105

void Yescursortype()//hien dau nhay
{
CONSOLE_CURSOR_INFO Info;
Info.bVisible = TRUE;
Info.dwSize=20;
SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}
void gotoxy(int x=0,int y=0){
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x,y};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void Nocursortype()//an dau nhay
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize=20;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}
void resizeConsole(int width, int height){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void Setcolor(WORD color){
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;color &= 0x000f;
	wAttributes &= 0xfff0;wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

//void multiPuts(int x=0,int y=0,char *c="nguyen minh vuong", int color=15){//tao chuoi ki tu
//	gotoxy(x,y);
//	Setcolor(color);
//	printf("%s",c);
//}
void multiPut(int x=0,int y=0,char c=(char)178, int color=15){
	gotoxy(x,y);
	Setcolor(color);
	cout<<c;
}

void drawNgang(int x1=0,int y1=0,int x2=0,int  y2=0,int color =14){
	for(int i=x1;i<x2-1;i++)
		multiPut(i+1,y1,(char)196,color);
}
void drawDoc(int x1=0,int y1=0,int x2=0,int y2=0,int color=14){
	for(int i=0;i<y2-y1-1;i++)
		multiPut(x1,y1+i+1,(char)179,color);
}
void drawChar(int x1=0,int y1=0,int x2 =0,int y2=0,char c=(char)178,int color=14){
		for(int i=x1;i<x2-1;i++)
			multiPut(i+1,y1,c,color);
}
void ClearBoard(int x1=0,int y1=0,int x2=0,int  y2=0,int color =0){
	Nocursortype();
	for(int i=x1;i<x2+1;i++)
		for(int j=y1;j<y2;j++)
			multiPut(i,j,(char)32,0);
}

//V? m?t hình ch? nh?t có toa do? 2 d?nh (trên, trái – du?i, ph?i) l�  (x1,y1)-(x2,y2), voi tiêu de l�  ttColor
class cBoard{
	public:int x1,y1,x2,y2,width,height;
	public: 
		void SetBoard(int,int,int,int);
 
inline void drawBoard(int x1, int y1, int x2, int y2, int color=14,char *title=NULL,int ttColor=15){
	int i;
	multiPut(x1,y1,(char)218,color); //top-left
	multiPut(x2,y1,(char)191,color); //top-right
	multiPut(x1,y2,(char)192,color); //bottom-left
	multiPut(x2,y2,(char)217,color); //bottom-right
	Setcolor(color);
	for(i=x1;i<x2-1;i++) //top border */
		multiPut(i+1,y1,(char)196,color);
	for(i=x1;i<x2-1;i++) //bottom border */
		multiPut(i+1,y2,(char)196,color);
		
	for(i=0;i<y2-y1-1;i++) /* left border */
		multiPut(x1,y1+i+1,(char)179,color);
		
	for(i=0;i<y2-y1-1;i++) /* right border */
		multiPut(x2,y1+i+1,(char)179,color);
		
	if (title!=NULL&&strlen(title)<(x2-x1))
		for(i=0;i<strlen(title);i++)
		multiPut(i+(x2+x1)/2-strlen(title)/2,y1,*(title+i),ttColor);
	SetBoard(x1,y1,x2,y2);
	}
	
}
	board;
	void cBoard::SetBoard(int x1,int y1,int x2,int y2){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;	
}
	cBoard board1,board2,board3;
	//==================

void Normal(){
	Setcolor(15);
	SetBGColor(0);
}
void HighLight(){
	Setcolor(15);
	SetBGColor(1);
}



void XoaManHinh()
{
HANDLE hStdOut;
CONSOLE_SCREEN_BUFFER_INFO csbi;
DWORD count;
DWORD cellCount;
COORD homeCoords = { 0, 0 };
 
hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
if (hStdOut == INVALID_HANDLE_VALUE) return;
 
/* Get the number of cells in the current buffer */
if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
cellCount = csbi.dwSize.X *csbi.dwSize.Y;
 
/* Fill the entire buffer with spaces */
if (!FillConsoleOutputCharacter(
hStdOut,
(TCHAR) ' ',
cellCount,
homeCoords,
&count
)) return;
 
/* Fill the entire buffer with the current colors and attributes */
if (!FillConsoleOutputAttribute(
hStdOut,
csbi.wAttributes,
cellCount,
homeCoords,
&count
)) return;
 
/* Move the cursor home */
SetConsoleCursorPosition( hStdOut, homeCoords );
}
void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}
char* Nhap_Word1( int x, int y, int n , int &endchar) {
	char *S=new char [n+1]; 
	int i=0; 
	int c;
	gotoxy (x, y);
	while (1) { 
	    endchar =' ';
		c=getch(); 	
		c=tolower(c);
	
		if (c==224 || c==0) { 
		 	c=getch();		
			c+=128;
		}
		if ((c==ENTER ||c==UP || c==DOWN || c==F2|| c==ESC || c==F1 || c==F3) ) 
		{ 
			endchar = c ; 
			break ;
		}
		if(c==8&&i)
			printf("\b \b"),i--;
		if((!(isalpha(c)||c==' ')) || i>=n-1 || (i&&c==' '&& S[i-1]==' ')||(i==0 && c ==' ')||!(isalnum(c)||strchr(" ?.\":`~!@#$\%^&*()",c))) 
		{
			continue;  
		}
		cout <<char(c);// printf(("%s",char(c));
		S[i++]=c;
		if (i==n) 
			break ;	
	}
	S[i]=NULL; 
	return S;
}

//==================================================================================================
void TopUI(){
	Normal();
	gotoxy(bx1,5);
	printf("[F1]:Them tu vao TU DIEN\n");
	gotoxy(bx1,wherey()+2);
	printf("[F2]:Xem toan bo TU DIEN\n");
	gotoxy(bx1,wherey()+2);
	printf("[ESC]:Thoat chuong trinh");
}
void GiaoDienChinh(){
	XoaManHinh();
	Normal();
	Nocursortype();
	
	TopUI();
	
//	board1.drawBoard(bx1   ,by1   ,bx2   ,by2-65,18,"Dictionary-Tu dien-Anh Viet",14);
//	board2.drawBoard(bx1   ,by2-65,bx2-40,by2-40,bclor);
//	board3.drawBoard(bx2-40,by2-65,bx2   ,by2-40,196);	

//	board1.drawBoard(bx1   		,by1   		,bx2   			,by2			,18	,"Dictionary-Tu dien-Anh Viet",14);
//	board2.drawBoard(bx1   		,by2   		,bx2-40			,by2+25			,bclor);
//	board3.drawBoard(bx2-40		,by2   		,bx2   			,by2+25,196);	
	
	board1.drawBoard(bx1   		,by1		,bx2   			,by2			,18,"Dictionary-Tu dien-Anh Viet",14);
	board2.drawBoard(board1.x1	,board1.y2  ,board1.x2-65	,board1.y2+25	,bclor);//=65
	board3.drawBoard(board2.x2	,board2.y1  ,board1.x2  	,board1.y2+25	,196);	//board3.drawBoard(board2.x2	,board2.y1  ,board1.x2  	,board1.y2+25	,196);	//
	
	printf("\n\n");
	
}
char *substr(char *s, int start, int end,int n)
{
	char p[n];
	int indext = 0;

	for (int i = start; i <= end; i++)
	{
		p[indext] = s[i];
		indext++;
	}
	p[indext] = '\0';

	return p;
}
struct tachchuoi{
	char str1[30];
	char str2[200];
};
typedef struct tachchuoi *Plit;
char* printxuongdong(Plit str,char *chuoi,int n){
	char temp[n];
	memset(temp,'\0',sizeof(temp));
	memset(str->str1,'\0',sizeof(str->str1));
	memset(str->str2,'\0',sizeof(str->str2));
	
	strncpy(temp,chuoi,sizeof(temp)-1);
		
	strcpy(str->str1,strrchr(temp,' '));
				
	strcpy(str->str2,substr(chuoi,strlen(temp)-strlen(str->str1)+1,strlen(chuoi),sizeof(str->str2)));
	
	strncpy(str->str1,temp,strlen(temp)-strlen(str->str1));

	return  str->str2;
}
void xuongdong(Plit str,int n,char *s,int x,int y,int i){
	do{
	str = new tachchuoi;
	s=printxuongdong(str,s,n);
	gotoxy(x,wherey()+1);
	printf("%d: %s",i,str->str1);
	}
	while(strlen(str->str2)>n);	
	gotoxy(x,wherey()+1);
	printf("%s",str->str2);
}	


