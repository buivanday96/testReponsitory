#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;
int bx1=10,by1=14,bx2=105,by2=82-65,bclor=14;//x=105
const int UP =72+128;
const int DOWN =80+128;

const int F3=61+128;
const int F2=60+128;
const int F1=59+128;

const int ENTER =13;
const int ESC =27;
const int BACKSPACE = 8;
const int MAX=3;

//di chuyen con tro chuot toi vi tri co toa do x,y tren man hinh console
void gotoxy(int x=0,int y=0){
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x,y};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
//tra ve hoanh do x cua con tro chuot hien tai tren console
int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}
//tra ve tung do y cua con tro chuot hien tai tren console
int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
//to mau chu
void Setcolor(WORD color){
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;color &= 0x000f;
	wAttributes &= 0xfff0;wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
// to mau nen
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
//chu~ mau trang , nen` mau den
void Normal(){
	Setcolor(15);
	SetBGColor(0);
}
//chu mau trang  nen xanh
void HighLight(){
	Setcolor(15);
	SetBGColor(1);
}

void multiPut(int x=0,int y=0,char c=(char)178, int color=15){
	gotoxy(x,y);
	Setcolor(color);
	cout<<c;
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
	;
	void cBoard::SetBoard(int x1,int y1,int x2,int y2){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;	
}
	cBoard board1,board2,board3,board4;
	
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
//an dau nhay
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize=20;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}
//hien dau nhay
void Yescursortype()
{
CONSOLE_CURSOR_INFO Info;
Info.bVisible = TRUE;
Info.dwSize=20;
SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}
//size console
void resizeConsole(int width, int height){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
//==================================================================================================
void TopUI(){
	Normal();
	gotoxy(bx1,5);
	printf("[F1]:Them tu vao TU DIEN");
	gotoxy(bx1,wherey()+2);
	printf("[F2]:Xem toan bo TU DIEN");
	gotoxy(bx1,wherey()+2);
	printf("[ESC]:Thoat chuong trinh");
}
void TopUIInput(){
	Normal();
	Setcolor(14);
	gotoxy(bx1,1);
	printf("[F1]:Luu TU DIEN");
	gotoxy(bx1,wherey()+2);
	printf("[F2]:Xem toan bo TU DIEN");
	gotoxy(bx1,wherey()+2);
	printf("[ESC]:Quay lai");
	gotoxy(bx1,wherey()+2);
	Setcolor(18);
	printf("Khi khong muon nhap nua hay ket thuc qua trinh nhap,Vui long nhap '0' hoac enter\n ");
	Normal();
	
}
void TopUIUpdate(){
	Normal();
	Setcolor(14);
	gotoxy(bx1,1);
	printf("[F1]:Xoa tu nay trong TU DIEN \n");
	gotoxy(bx1,wherey()+2);
	printf("[F2]:Sua tu nay\n");
	gotoxy(bx1,wherey()+2);
	printf("[ESC]:Quay lai");
	Normal();
}
//
int UI(){
	XoaManHinh();
	Normal();
	Nocursortype();
	
	TopUI();
	
	board1.drawBoard(bx1   		,by1		,bx2   			,by2			,18,"Dictionary-Tu dien-Anh Viet",14);
	gotoxy(board1.x1+1,board1.y1+1);
	Setcolor(15);
	printf("Nhap tu can tim :");
	int xcur= wherex();
	board2.drawBoard(board1.x1	,board1.y2  ,board1.x2-65	,board1.y2+25	,bclor);//=65
	board3.drawBoard(board2.x2	,board2.y1  ,board1.x2  	,board1.y2+25	,196);	//board3.drawBoard(board2.x2	,board2.y1  ,board1.x2  	,board1.y2+25	,196);	//
	
	printf("\n\n");
	Normal();
	return xcur;
}
//
int YesNoUI(int x,int y,char *str){
	Loop:
	gotoxy(x,y);
	Setcolor(214);
	printf("%s",str);
	char c= getch();
	if(c=='Y'|| c== 'y')
	{
		gotoxy(wherex()+1,wherey());
		Setcolor(15);
		printf("Yes");
		return 0;
	}
	else if(c=='N'|| c== 'n'|| c== ESC)
	{
		gotoxy(wherex()+1,wherey());
		Setcolor(15);
		printf("No");
		return 1;
	}
		
	else goto Loop;

}
	
	//xoa 1 dong tren console
void ClearLine(int x,int y,int length){
	for(int i=1;i<=length;i++){
		gotoxy(x+i,y);
		printf("\b \b");
	}
}
void ClearBoard(int x,int y,int length,int line){
	for(int j=1;j<=line;j++)
		for(int i=1;i<=length;i++)
		{
			gotoxy(x+i,y+j);
			printf("\b \b");
		}
			
}
void ErrUI(char *err,int x,int y){
	gotoxy(x,y);
	Setcolor(15);
	printf(err);
}

//================================================================================================================
char* KeyboardHit_alpha2(int x,int y,int n,int &endchar,int type){// if type 1 = only a-z ,2 only number ,3 normal
	char *S = new char[n+1];
	int i=0;
	int c;
	gotoxy(x,y);
	while(1){
		endchar =' ';
		c= getch();
		c=tolower(c);
		if(c==224 || c==0)
		{
			c= getch();
			c+=128;
		}
		if( (c==ENTER) || c== ESC || c==F1 || c==F2 || c==F3)
		{
			endchar = c;
			break;
		}
		if(c==8&& i)
		{
			printf("\b \b");
			i--;
		}
	//	if( type==1 && ((!(isalpha(c)||c==' ')) || i>=n-1 || (i&&c==' '&& S[i-1]==' ')||(i==0 && c ==' ')||!(isalnum(c)||strchr(" ?.\":`~!@#$\%^&*()",c))) )continue;   
			
	//	if( type==2 && ((isalpha(c)) || i>=n-1 || !(isalnum(c)||strchr(" ?.\":`~!@#$\%^&*()",c)))) 	continue;  
		
		if((strchr(" ?.\":`~!@#$\%^&*()",c))||i>=n-1 ) 	continue;  
		
		printf("%c",char(c));
		S[i++]=c;
		if (i==n) 
			break ;	
	}
	S[i]='\0'; 
	return S;
		
	}
	///
char* KeyboardHit_alpha(int x,int y,int n,int &endchar){
	char *S=new char [n+1]; 
	int i=0; 
	int c;
	gotoxy (x, y);
	while (1) { 
	    endchar =' ';
		c=getch(); 		
		c=tolower(c);
		if (c==224 || c==0) { 
		 c=getch() ;		 
		 c+=128;
		}
		if( (c==ENTER) || c== ESC || c==F1 || c==F2 || c==F3)
		{ 
			endchar = c ; 
			break ;
		}
		if(c==BACKSPACE&&i)
			printf("\b \b"),i--;
		if (!(isalnum(c)||strchr(" ?.\":`~!@#$\%^&*()",c))||i>=n-1) 
			continue;  
		printf("%c",char(c));
		S[i++]=c;
		if (i==n) 
			break ;
	}
	S[i]=NULL; 
	return S;	
}

	

