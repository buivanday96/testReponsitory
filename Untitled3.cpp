#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;
const int UP =72+128;
const int DOWN =80+128;

const int F3=61+128;
const int F2=60+128;
const int F1=59+128;

const int ENTER =13;
const int ESC =27;
const int BACKSPACE = 8;
const int MAX=3;
char* KeyboardHit_alpha(int x,int y,int n,int &endchar){
	char *S=new char [n+1]; 
	int i=0; 
	int c;
	//gotoxy (x, y);
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
struct means{
	char mean[50];
};
typedef struct means MEAN;
struct nodeMEAN{
	MEAN data;
	struct nodeMEAN *pNext;
};
typedef struct nodeMEAN *NODEMEAN;
struct listMEAN{
	NODEMEAN pHead;
	NODEMEAN pTail;
};
typedef struct listMEAN LISTMEAN;
// khoi tao
void Initialize_Mean(LISTMEAN &l){
	l.pHead=l.pTail=NULL;
}
int main()
{
	LISTMEAN l;
	printf("LIST:%x\n",&l);
	printf("chua gi het\n");
	printf("%x,->next: %x\n",&l.pHead,&l.pHead->pNext);
	printf("%x,->next: %x\n",&l.pTail,&l.pTail->pNext);
	Initialize_Mean(l);
	printf("goi hàm Init_mean()+ new node p\n");
	NODEMEAN p = new nodeMEAN;
	strcpy(p->data.mean,"aaa");
	printf("LIST:%x\n",&l);
	printf("%x,->next: %x\n",&l.pHead,&l.pHead->pNext);
	printf("%x,->next: %x\n",&l.pTail,&l.pTail->pNext);
	printf("%x,->next: %x\n",&p,&p->pNext);
	printf("head=tail=p \n");
	l.pHead=l.pTail=p;
	printf("LIST:%x\n",&l);
	printf("%x,->next: %x\n",&l.pHead,&l.pHead->pNext);
	printf("%x,->next: %x\n",&l.pTail,&l.pTail->pNext);
	printf("%x,->next: %x\n",&p,&p->pNext);
	printf("con tro ->next cua head tail p\n");
	printf("%x\n",&l.pHead->pNext);
	printf("%x\n",&l.pTail->pNext);
	printf("%x\n",&p->pNext);
	


	return 0;
	
}

