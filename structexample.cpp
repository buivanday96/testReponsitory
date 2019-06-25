#include "structmean.cpp"
#define MAXLIST 5
struct examples{
	char ex[200];
};
typedef struct examples EX;
struct listEX{
	int n;
	EX *nodeEX[MAXLIST];
};
typedef struct listEX LISTEX;
// khoi tao
void Initialize_Example(LISTEX &l){
	l.n = -1;
}
// kiem tra rong
bool IsEmpty_Example(LISTEX &l){
	return l.n== -1 ? true :false ;
}
//nhap
int Input_ExampleUI(LISTEX &l,int x,int y){
	char str[200];
	int count =0,endchar;
	EX *node;
	gotoxy(x,y);
	if(IsEmpty_Example(l))
		Initialize_Example(l);
	else if(l.nodeEX[0]==NULL){
		Initialize_Example(l);
	}
	do{
		if(l.n==MAXLIST-1)// 0 1 2 3 4  => maxlist  = 5 => l.n >=5-1
			break;
		node = new EX;
		ClearLine(x,wherey(),50);//clear line search
		Yescursortype();
		gotoxy(x,wherey());
		printf("Nhap vi du %d	: ",++count);
		fflush(stdin);
		strcpy(str,KeyboardHit_alpha(wherex()+1,wherey(),200,endchar));
		if(IsEmpty_Example(l)&& !strlen(str))
		{
			printf("Vui long nhap 1 vd cho word");
			getch();
			count--;
			continue;
		}
		strcpy(node->ex,str);
		++l.n;
		l.nodeEX[l.n] = node;	
		
		if(!strncmp(str,"0",1)  || !strlen(str) || (str[0]==(char)ENTER  && str[1]=='\0'&&  endchar == ENTER) || endchar == ESC)
			return endchar;
		printf("\n");
	}while(1);
	return 0;
}
//xuat
void Print_ExampleUI(LISTEX &l,int x,int y)	{
	if(IsEmpty_Example(l)){
		gotoxy(x,y);
		printf("List is empty");
		return;
	}
	for(int i=0;i<l.n;i++){
		gotoxy(x,y+i);
		printf("%d: %s",i+1,l.nodeEX[i]->ex);
	}		
}
//xoa
void Delete_Example(LISTEX &l,int pos){
	if(IsEmpty_Example(l))
		return;
	for(int i=pos;i<MAXLIST;i++){
		l.nodeEX[i] = l.nodeEX[i+1];
	}	
--l.n;
	
}
void Delete_ExampleUI(LISTEX &l,int x,int y){
	{
		gotoxy(x,y);
		printf("Please enter the position to delete 1-max: ");
		int pos;
		scanf("%d",&pos);
		EX *infor= l.nodeEX[pos-1];
		if(infor==NULL){
			printf("The position to delete is not in the list\n");
			return;
		}
		Delete_Example(l,pos-1);
		printf("Deleted : %s",infor->ex);
	}
}
//int main(){
//	LISTEX list;
//	Initialize_Example(list);
//	do{
//		
//		system("cls");
//		printf("1.Input ex:\n");
//		printf("2.Output :\n");
//		printf("3.Del :\n");
//		printf("4.Quit\n");
//		printf("Make a choice: ");
//		int chon;
//		fflush(stdin);
//		scanf("%d",&chon);
//		switch(chon){
//			case 1:{
//				gotoxy(1,wherey());
//				printf("Input example: enter = 0 or  empty to stop typing!\n");
//				Input_ExampleUI(list,20,wherey());
//				break;
//			}
//			case 2:{
//				Print_ExampleUI(list,wherex(),wherey());
//				break;
//			}	
//			case 3:{
//				Delete_ExampleUI(list,wherex(),wherey()+1);
//				break;
//			}
//			default:{
//				break;
//			}
//		}
//		if(chon==4)
//			break;	
//		getch();
//	}while(1);	
//}


