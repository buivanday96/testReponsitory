#include "structexample.cpp"

struct words{
	char word[20];
	char wtype[10];
	LISTMEAN mean;
	LISTEX ex;
};
typedef struct words WORDS;
struct nodeWORD{
	WORDS data;
	struct nodeWORD *pLeft;
	struct nodeWORD *pRight;
};
typedef struct nodeWORD *NODEWORD;


struct listWORD{
	NODEWORD pHead;
	NODEWORD pTail;
};
typedef struct listWORD LISTWORD;

// khoi tao
void Initialize_Word(LISTWORD &l){
	l.pHead=l.pTail=NULL;
}
// kiem tra rong
bool IsEmpty_Word(LISTWORD &l){
	return l.pHead==NULL ? true :false ;
}
// tao node
NODEWORD GetNode_Word(WORDS w){
	NODEWORD p= new nodeWORD;
	p->data=w;
	p->pLeft=NULL;
	p->pRight=NULL;
	return p;
}
// so sanh 2 mean
int Compare_Word(NODEWORD node1,NODEWORD node2){
	return strcmp(node1->data.word,node2->data.word);
}
// tim theo vi tri 
NODEWORD SearchByPostion_Word(LISTWORD l,int pos){
	NODEWORD p;
	int count=0;
	for(p=l.pHead;p!=NULL;p=p->pRight){
		if(pos==count)
			return p;
		count++;
	}
	return NULL;
}
//tim node co data = infor
NODEWORD SearchNodeX_Word(LISTWORD &l,char *infor){
	for(NODEWORD p=l.pHead;p!=NULL;p=p->pRight){
		if(strcmp(p->data.word,infor)==0)
			return p;
	}
	return NULL;
}
// tim node duoc truoc node info
NODEWORD SearchNodeBefore_Word(LISTWORD &l,NODEWORD infor){
	for(NODEWORD p=l.pHead;p!=NULL;p=p->pRight){
		if(Compare_Word(p,infor)>=0)
			return p;
	}
	return NULL;
}
//them dau`
void InsertHead_Word(LISTWORD &l,NODEWORD infor){
	if(IsEmpty_Word(l))
		l.pHead =l.pTail =infor;
	else{
		infor->pRight=l.pHead;
		l.pHead->pLeft=infor;
		l.pHead=infor;
	}	
}
//them cuoi'
void InsertTail_Word(LISTWORD &l,NODEWORD infor){
	if(IsEmpty_Word(l))
		l.pHead =l.pTail =infor;
	else{
		l.pTail->pRight=infor;
		infor->pLeft =l.pTail;
		l.pTail=infor;
	}	
}
//them node infor sau node before 
void InsertAfter_Word(LISTWORD &l,NODEWORD infor,NODEWORD before){
	if(before==l.pTail){
		InsertTail_Word(l,infor);
		return;
	}
	NODEWORD after = before->pRight;
	before->pRight = infor;
	infor->pLeft = before;
	infor->pRight=after;
	after->pLeft=infor;
}
void InsertBefore_Word(LISTWORD &l,NODEWORD infor,NODEWORD after){
	if(after==l.pHead){
		InsertHead_Word(l,infor);
		return;
	}
	NODEWORD before = after->pLeft;
	after->pLeft = infor;
	infor->pRight = after;
	infor->pLeft = before;
	before->pRight = infor;
}
//them node infor sau node before 
void InsertAZ_Word(LISTWORD &l,NODEWORD infor){
	if(infor==NULL)
	 	return;
	 	//truong hop them dau
	if(IsEmpty_Word(l) || Compare_Word(l.pHead,infor)>0)
	{
		InsertHead_Word(l,infor);
		return;
	}
	// truong hop them cuoi
	if(Compare_Word(l.pTail,infor)<=0){
		InsertTail_Word(l,infor);
		return;
	}
	//truong hop vao giua
	NODEWORD before =l.pHead;
	for(NODEWORD p=l.pHead->pRight;p!=NULL;p=p->pRight){
			
		if(Compare_Word(p,infor)>0){
			//before =  p->l;
			InsertAfter_Word(l,infor,before);
			printf("\n > 0");
			break;
		}
		before =p;
	}	
}
//xoa dau
void DelHead_Word(LISTWORD &l){
	if(IsEmpty_Word(l))
		return;
	NODEWORD q = l.pHead;
	l.pHead =l.pHead->pRight;
	delete q;
}
//xoa cuoi
void DelTail_Word(LISTWORD &l){
	if(IsEmpty_Word(l))
		return;
	NODEWORD q = l.pTail;
	l.pTail =l.pTail->pLeft;
	l.pTail->pRight = NULL;
	delete q;
}
//xoa sau
void DelAfter_Word(LISTWORD &l,NODEWORD before){
	NODEWORD infor,after;
	infor = before->pRight;
	after = before->pRight->pRight;
	
	before->pRight = after;
	after->pLeft = before;
	
	delete infor;
}
//xoa bat ky
void DelOrder_Word(LISTWORD &l,NODEWORD infor){
	if(IsEmpty_Word(l))
		return;
	if(Compare_Word(l.pHead,infor)==0){
		DelHead_Word(l);
		return;
	}
	if(Compare_Word(l.pTail,infor)==0){
		DelTail_Word(l);
		return;
	}
	for(NODEWORD p=l.pHead;p!=NULL;p=p->pRight){
		
		if(Compare_Word(p,infor)==0){
			DelAfter_Word(l,infor->pLeft);
			break;
		}
	}
}
//nhap du lieu
void Input_WordUI(LISTWORD &l,int x,int y){
	NODEWORD infor;
	int count=0,endchar;
	gotoxy(x,y);
	char str[20];
	char wt[10];
	do{
		WORDS word;
		Initialize_Mean(word.mean);
		Initialize_Example(word.ex);
		gotoxy(x,wherey());
		printf("Nhap word %d: ",++count);
		fflush(stdin);
		gets(str);	
		if(!strncmp(str,"0",1) || !strcmp(str,""))
			break;
		if(SearchNodeX_Word(l,str)!=NULL){
			gotoxy(wherex(),wherey());
			printf("\n Word da ton tai trong ds!");
			break;
		}
		strcpy(word.word,str);
		gotoxy(x,wherey());
		printf("Nhap word  type %d: ",count);
		fflush(stdin);
		gets(wt);
		strcpy(word.wtype,wt);
			
		//nhap mean
	
		endchar=Input_MeanUI(word.mean,x,wherey()+1);
		if(endchar==ESC)
			break;
		//nhap example
	
		endchar=Input_ExampleUI(word.ex,x,wherey()+1);
		if(endchar==ESC)
			break;
		printf("=======================================\n");
		infor = GetNode_Word(word);
		InsertAZ_Word(l,infor);
		
	}while(1);
}
//
void Delete_WordUI(LISTWORD &l,int x,int y){
	{
		gotoxy(x,y);
		printf("Please enter the word to delete 1-max: ");
		char word[20];
		fflush(stdin);
		gets(word);
		NODEWORD infor = SearchNodeX_Word(l,word);
		if(infor==NULL){
			printf("The word to delete is not in the list\n");
			return;
		}
		DelOrder_Word(l,infor);
		printf("Deleted : %s",word);
	}
}
//xuat du lieu
void Print_WordUI(LISTWORD l,int x,int y){
	if(IsEmpty_Word(l)){
		gotoxy(x,y);
		printf("List is empty");
		return;
	}
	int count=0;
	for(NODEWORD p=l.pHead;p!=NULL;p=p->pRight){
		gotoxy(x,wherey()+1);
		printf("word: %s\n",p->data.word);
		printf("word type: %s\n",p->data.wtype);
		printf("Mean:\n");
		Print_MeanUI(p->data.mean,20,wherey());
		gotoxy(x,wherey()+1);
		printf("\nEx:\n");
		Print_ExampleUI(p->data.ex,10,wherey()+1);
		count++;
	}
	printf("\n%d",count);
	
}
//int main(){
//	LISTWORD list;
//	Initialize_Word(list);
//	do{
//		
//		system("cls");
//		printf("1.Input word:\n");
//		printf("2.Output word:\n");
//		printf("3.Del word:\n");
//		printf("4.Quit\n");
//		printf("Make a choice: ");
//		int chon;
//		fflush(stdin);
//		scanf("%d",&chon);
//		switch(chon){
//			case 1:{
//				gotoxy(1,wherey());
//				printf("Input word: enter = 0 or  empty to stop typing!\n");
//				Input_WordUI(list,20,wherey());
//				break;
//			}
//			case 2:{
//				Print_WordUI(list,wherex(),wherey());
//				break;
//			}	
//			case 3:{
//				Delete_WordUI(list,wherex(),wherey()+1);
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




