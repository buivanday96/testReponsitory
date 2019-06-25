#include "mylibrary.cpp">
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
// kiem tra rong
bool IsEmpty_Mean(LISTMEAN &l){
	return l.pHead==NULL ? true :false ;
}
// tao node
NODEMEAN GetNode_Mean(MEAN m){
	NODEMEAN p= new nodeMEAN;
	p->data=m;
	p->pNext=NULL;
	return p;
}
// so sanh 2 mean
int Compare_Mean(NODEMEAN node1,NODEMEAN node2){
	return strcmp(node1->data.mean,node2->data.mean);
}
// tim theo vi tri 
NODEMEAN SearchByPostion_Mean(LISTMEAN &l,int pos){
	NODEMEAN p;
	int count=0;
	for(p=l.pHead;p!=NULL;p=p->pNext){
		if(pos==count)
			return p;
		count++;
	}
	return NULL;
}
NODEMEAN SearchBefore_Mean(LISTMEAN &l,NODEMEAN infor){
	NODEMEAN p;
	for(p=l.pHead;p!=NULL;p=p->pNext){
	
	}
}
//them dau
void InsertHead_Mean(LISTMEAN &l,NODEMEAN infor){
	if(IsEmpty_Mean(l))
		l.pHead=l.pTail=infor;
	else{
		infor->pNext=l.pHead;
		l.pHead=infor;
	}
}
//them cuoi
void InsertTail_Mean(LISTMEAN &l,NODEMEAN infor){
	if(IsEmpty_Mean(l))
		l.pHead=l.pTail=infor;
	else{
		l.pTail->pNext=infor;
		l.pTail=infor;
	}
}

//them node infor sau node before 
void InsertAfter_Mean(LISTMEAN &l,NODEMEAN infor,NODEMEAN before){
	if(before==NULL){
		return;
	}
	for(NODEMEAN p=l.pHead;p!=NULL;p=p->pNext)
		if(!Compare_Mean(p,before)){
			p->pNext = infor; // before -> next = infor
			infor->pNext=p->pNext->pNext; // before - infor - before->next
			return;
		}
}
//xoa node dau
void DelHead_Mean(LISTMEAN &l){
	if(IsEmpty_Mean(l))
		return;
	NODEMEAN q = l.pHead;
	l.pHead = l.pHead->pNext;
	delete q;
}
//xoa node cuoi
void DelTail_Mean(LISTMEAN &l){
	if(IsEmpty_Mean(l))
		return;
	NODEMEAN before;
	for(NODEMEAN p=l.pHead;p!=NULL;p=p->pNext){
		if(p==l.pTail){
			l.pTail = before;
			p->pNext =NULL;
			delete p;
		}
		before =p;
	}
}
//xoa sau node before
void DelAfter_Mean(LISTMEAN &l,NODEMEAN before,NODEMEAN &infor){
	infor = before->pNext;
	before->pNext = infor->pNext;
	delete infor;
}
void DelAfter_Mean(LISTMEAN &l,NODEMEAN before){
	for(NODEMEAN p=l.pHead;p!=NULL;p=p->pNext)
		if(!Compare_Mean(p,before)){
			NODEMEAN infor= p->pNext;//inforr=before->
			p->pNext = infor->pNext;//before->=before-> ->
			delete infor;
			return;
		}
}

//xoa node bat ky
void DelOrder_Mean(LISTMEAN &l,NODEMEAN infor){
	if(!Compare_Mean(l.pHead,infor)){
		DelHead_Mean(l);
		return;
	}
	if(!Compare_Mean(l.pTail,infor)){
		DelTail_Mean(l);
		return;
	}
	NODEMEAN before;
	for(NODEMEAN p=l.pHead;p!=NULL;p=p->pNext){
		if(!Compare_Mean(p,infor)){
			DelAfter_Mean(l,before,p);
			break;
		}
		before = p;
	}
}

//nhap du lieu
int Input_MeanUI(LISTMEAN &l,int x,int y){
	NODEMEAN infor;
	int count=0;
	gotoxy(x,y);
	char str[50];
	int endchar;
	if(IsEmpty_Mean(l))
	{
		Initialize_Mean(l);
	}
	do{
		MEAN mean;
		ClearLine(x,wherey(),50);//clear line search
		Yescursortype();
		gotoxy(x,wherey());
		printf("Nhap nghia %d	: ",++count);
		fflush(stdin);
		strcpy(str,KeyboardHit_alpha(wherex()+1,wherey(),50,endchar));
		fflush(stdin);
		if(IsEmpty_Mean(l)&& !strlen(str))
		{
			printf("Vui long nhap 1 nghia cho word");
			getch();
			count--;
			continue;
		}
		if(!strncmp(str,"0",1)  || !strlen(str) || (str[0]==(char)ENTER  && str[1]=='\0'&&  endchar == ENTER) || endchar == ESC ||endchar ==F1||endchar==F2)
			return endchar;
		
		strcpy(mean.mean,str);
		infor = GetNode_Mean(mean);
		InsertTail_Mean(l,infor);
		printf("\n");
	}while(1);
	return 0;
}
//xuat du lieu
void Print_MeanUI(LISTMEAN l,int x,int y){
	if(IsEmpty_Mean(l)){
		gotoxy(x,y);
		printf("List is empty");
		return;
	}
	int count=0;
	for(NODEMEAN p=l.pHead;p!=NULL;p=p->pNext){
		gotoxy(x,y+count);
		printf("%d: %s",++count,p->data.mean);
	}
}
void Delete_MeanUI(LISTMEAN &l,int x,int y){
	{
		gotoxy(x,y);
		printf("Please enter the position to delete 1-max: ");
		int pos;
		scanf("%d",&pos);
		NODEMEAN infor = SearchByPostion_Mean(l,pos-1);
		char *data_infor= new char;
		strcpy(data_infor,infor->data.mean);
		if(infor==NULL){
			printf("The position to delete is not in the list\n");
			return;
		}
		DelOrder_Mean(l,infor);
		printf("Deleted : %s",data_infor);
	}
}
//int main(){
//	LISTMEAN listmean;
//	Initialize_Mean(listmean);
//	do{
//		
//		system("cls");
//		printf("1.Input means:\n");
//		printf("2.Output means:\n");
//		printf("3.Del mean:\n");
//		printf("4.Quit\n");
//		printf("Make a choice: ");
//		int chon;
//		fflush(stdin);
//		scanf("%d",&chon);
//		switch(chon){
//			case 1:{
//				gotoxy(1,wherey());
//				printf("Input mean: enter = 0 or  empty to stop typing!\n");
//				Input_MeanUI(listmean,20,wherey());
//				break;
//			}
//			case 2:{
//				Print_MeanUI(listmean,wherex(),wherey());
//				break;
//			}	
//			case 3:{
//				Delete_MeanUI(listmean,wherex(),wherey()+1);
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
//	return 0;
//}






