#include "structwords.cpp"
#define B 26
LISTWORD Bucket[B];

char *filename="tudien";
// ham bam
int Hashfunc(char *word){
	char ch = toupper(word[0]);
	return ((ch-65) % B);
}
// khoi tao cac bucket
void InitializeBucket(){
	for(int b=0;b<B;b++){
		Bucket[b].pHead = NULL;
		Bucket[b].pTail = NULL;
	}
}
int Position(char *word){
	int i = Hashfunc(word),k=1;
	for(NODEWORD p =Bucket[i].pHead;p;p=p->pRight){
		if(strcmp(p->data.word,word)>0)
			return k;
		k++;
	}
	return k;
}
//v

// luu file
 void Save(LISTWORD &l,char *tenfile,char *mode){
	FILE *f =fopen(tenfile,mode);
	if(f==NULL)
		return;

	for(NODEWORD p=l.pHead;p;p=p->pRight){
		fwrite(&p->data.word,sizeof(p->data.word),1,f);
		fwrite(&p->data.wtype,sizeof(p->data.wtype),1,f);
		for(NODEMEAN m=p->data.mean.pHead;m!=NULL;m=m->pNext)
		{
			fwrite(&m->data,sizeof(MEAN),1,f);
		}
		MEAN temp;
		strcpy(temp.mean,"0000");
		fwrite(&temp,sizeof(MEAN),1,f);
		for(int i=0;i<p->data.ex.n+1;i++){
			fwrite(p->data.ex.nodeEX[i],sizeof(EX),1,f);
		}
//		EX *temp2= new EX;
//		strcpy(temp2->ex,"0000");
//		fwrite(temp2,sizeof(EX),1,f);
	}
	fclose(f);
}
// load file
void Load(char *tenfile,char *mode){
	FILE *f =fopen(tenfile,mode);
	if(f==NULL)
		return;
	fseek(f,0,SEEK_SET);
	WORDS w;
	MEAN m;
	
	while(fread(&w.word,sizeof(w.word),1,f)){
		if(strcmp(w.word,"0000")==0 || strlen(w.word)==0) continue;
		printf("w%s\n",w.word);
		fread(&w.wtype,sizeof(w.wtype),1,f);
		if(strcmp(w.wtype,"0000")==0 || strlen(w.wtype)==0) continue;
		printf("wt%s\n",w.wtype);
		Initialize_Mean(w.mean);
		while(fread(&m,sizeof(MEAN),1,f)){
			if(strcmp(m.mean,"0000")==0 || strlen(m.mean)==0 ) break;
			else 
			{
				printf("m%s\n",m.mean);
				NODEMEAN node = GetNode_Mean(m);
				InsertTail_Mean(w.mean,node);	
			}
		}
		w.ex.n = -1;
		while(fread(w.ex.nodeEX[++w.ex.n] = new EX,sizeof(EX),1,f)){
				printf("ex%d%s\n",w.ex.n,w.ex.nodeEX[w.ex.n]->ex);
		if(!strcmp(w.ex.nodeEX[w.ex.n]->ex,"0000") || strlen(w.ex.nodeEX[w.ex.n]->ex )==0 || w.ex.n>=MAXLIST-1)
			break;
		}
		NODEWORD infor = GetNode_Word(w);
		int i = Hashfunc(w.word);
		InsertAZ_Word(Bucket[i],infor);
	}
	fclose(f);
}
void SaveBucket(){
	FILE *f =fopen(filename,"wb");
	fclose(f);
	for(int i=0;i<B;i++){
		Save(Bucket[i],filename,"ab");
	}
}
//===========================================
void Print(LISTWORD l){
	NODEWORD p= l.pHead;
	char ch[2];
	memset(ch, '\0', sizeof(ch));
	
	int flag = 0;
	while(p!=NULL){
		if(p == l.pHead)
		{
			strncpy(ch,p->data.word,1);
			printf("%s:\n",ch);
		}
		
		printf("\t%s ",p->data.word);
		printf("\n");
		p=p->pRight;
	}
}
void PrintBucketUI_LineNumber(){
	gotoxy(board2.x1+1,board2.y1);
	int line=0;
	for(int i=0;i<B;i++){
		for(NODEWORD p=Bucket[i].pHead;p!=NULL;p=p->pRight){
			if(line<25){
				gotoxy(board2.x1+1,wherey()+1);
				printf("%s",p->data.word);
				line++;
			}
			else
				break;	
		}
	}
}
void PrintBucketUI3(int hash,int n,char *word){
	Setcolor(15);
	int line =0;
	gotoxy(board2.x1+1,board2.y1);
	for(NODEWORD p=Bucket[hash].pHead;p!=NULL;p=p->pRight){
		if(line<25 && strncmp(word,p->data.word,n)==0){
			gotoxy(board2.x1+1,wherey()+1);
			printf("%s",p->data.word);
			line++;
		}
	}
}
void DisplayDictionary(){
	for(int i =0;i<B;i++){

		Print(Bucket[i]);
	}
}
//=====================================
int F2_Dictionary(){
	Loop:
		XoaManHinh();
		DisplayDictionary();
		Nocursortype();
		char c=getch();
		if(c==0||c==128){
			c=getch();
			c+=128;
		}
		if(c==ESC)
			return 1;
		else
			goto Loop;
}
//
int  FunctionKeys_Input(int endchar){
	Nocursortype();
	if(endchar==F1)// f1
	{
		XoaManHinh();
		Nocursortype();
		SaveBucket();
		gotoxy(bx1,25);
		printf("Da luu!");
		getch();
		return 1;
	}
	if(endchar==F2){
		return F2_Dictionary();
	}
	if(endchar==ESC){
		return 0;
	}
}
//
void Input_UI(int x,int y){
	NODEWORD infor;
	int count=0,endchar,key;
	gotoxy(x,y);
	char str[20];
	char wt[10];
	do{
		XoaManHinh();
		TopUIInput();
		printf("\n");
		WORDS word;
		Initialize_Mean(word.mean);
		Initialize_Example(word.ex);
		Yescursortype();
		//=======================================
	WORD:	
		gotoxy(x,wherey());
		printf("Nhap word	: ");
//		fflush(stdin);
		strcpy(str,KeyboardHit_alpha(wherex(),wherey(),20,endchar));
		printf("\n");
		key=FunctionKeys_Input(endchar);	
		if(endchar==F1||endchar==F2)
			continue;
		if(!key || !strncmp(str,"0",1) || !strcmp(str,"") )
			break;
		int hash = Hashfunc(str);
		if(SearchNodeX_Word(Bucket[hash],str)!=NULL){
			gotoxy(wherex(),wherey());
			printf("\n [%s] da ton tai trong TU DIEN!",str);
			getch();
			count--;
			XoaManHinh();
			continue;
		}
		strcpy(word.word,str);
		//=========================
		gotoxy(x,wherey());
		printf("Nhap wordtype 	: ");
	//	fflush(stdin);
		strcpy(wt,KeyboardHit_alpha(wherex(),wherey(),10,endchar));
		printf("\n");	
		key=FunctionKeys_Input(endchar);	
		if(!key || !strncmp(wt,"0",1) || !strcmp(wt,"") )
			break;
		if(endchar==F1||endchar==F2)
			continue;	
		strcpy(word.wtype,wt);
		//nhap mean===========================
		endchar=Input_MeanUI(word.mean,x,wherey()+1);
		printf("\n");
		key=FunctionKeys_Input(endchar);	
		if(!key )
			break;
		if(endchar==F1||endchar==F2)
			continue;
		//nhap example=========================
		endchar=Input_ExampleUI(word.ex,x,wherey()+1);
		key=FunctionKeys_Input(endchar);	
		if(!key )
			break;
		if(endchar==F1||endchar==F2)
			continue;
		printf("=======================================\n");
		
		infor = GetNode_Word(word);
		InsertAZ_Word(Bucket[hash],infor);
		XoaManHinh();
	}while(1);
}
//

//
void Detail_Word(int x,int y,NODEWORD p){
		gotoxy(x,y);
		printf("[%s](%s) \n",p->data.word,p->data.wtype);
		gotoxy(x,wherey()+1);
		Setcolor(18);
		printf("Nghia la:");
		gotoxy(x,wherey()+1);
		Setcolor(15);
		Print_MeanUI(p->data.mean,x,wherey());
		gotoxy(x,wherey()+1);
		Setcolor(18);
		printf("Vi du:");
		Setcolor(15);
		Print_ExampleUI(p->data.ex,x,wherey()+1);
}
//
int ResultUI(int x,int y,char *word,NODEWORD &infor){
	int hash = Hashfunc(word);
	NODEWORD p= SearchNodeX_Word(Bucket[hash],word);
	if(p==NULL || !strcmp(word," ")){
			char str1[50]="[";
			char str2[25]="]";
			strcat(str1,word);
			strcat(str1,str2);
			ErrUI(str1,x,y);
			gotoxy(x,y+1);
			printf("khong co trong tu dien");
			return 0;
		}
	else{
		Detail_Word(x,y,p);
		infor = p;
		return 1;
	}
	printf("\n");
}
//
int ResultUI(int x,int y,char *word){
	Nocursortype();
	int hash = Hashfunc(word);
	NODEWORD p= SearchNodeX_Word(Bucket[hash],word);
	if(p==NULL || !strcmp(word," ")){
			char str1[50]="[";
			char str2[25]="]";
			strcat(str1,word);
			strcat(str1,str2);
			ErrUI(str1,x,y);
			gotoxy(x,y+1);
			printf("khong co trong tu dien");
			return 0;
		}
	else{
		Detail_Word(x,y,p);
		return 1;
	}
	printf("\n");
}
//
int FunctionKeys_Update(int endchar,NODEWORD infor){
	Nocursortype();
	char str1[50]="Ban co muon xoa tu [";
	char str2[25]="] Yes/No(Y/N): ";
	strcat(str1,infor->data.word);
	strcat(str1,str2);
	int result;
	if(endchar==F1){
		gotoxy();
		result=YesNoUI(bx1,1,str1);
		if(!result)
		{
			int hash=Hashfunc(infor->data.word);
			DelOrder_Word(Bucket[hash],infor);
			return 0;
		}	
		return 1;
	}
	if(endchar==F2){
		XoaManHinh();
		Yescursortype();
		printf("Sua tu\n");
		return 1;
	}
	if(endchar==ESC){
		return 0;
	}
}
//
void UpdateUI(int x,int y,NODEWORD infor){
	int endchar,key;
	while(1){
		XoaManHinh();
		gotoxy(x-5,1);
		Setcolor(18);
		printf("CHI TIET VA CHINH SUA WORD\n");
		Setcolor(15);
		TopUIUpdate();
		Detail_Word(x,y,infor);
		endchar=getch();
		if(endchar==128 || endchar ==0){
			endchar= getch();
			endchar+=128;
		}
		key=FunctionKeys_Update(endchar,infor);
		if(!key)
			break;
		else
			continue;
	}
}
//
int  FunctionKeys_Search(int endchar){
	Nocursortype();
	if(endchar==F1)// f1
	{
		XoaManHinh();
		Yescursortype();
		Input_UI(15,5);
		return 1;
	}
	if(endchar==F2){
		return F2_Dictionary();
	}
	if(endchar==ESC) // esc
	{
		return YesNoUI(board1.x1+30,9,"Ban co muon thoat chuong trinh Yes/No(Y/N):");
	}
}
//
int  FunctionKeys_Search(int endchar,bool turn,NODEWORD infor){
	Nocursortype();
	if(endchar==F1)// f1
	{
		XoaManHinh();
		Yescursortype();
		Input_UI(15,5);
		return 1;
	}
	if(endchar==F2){
		return F2_Dictionary();
	}
	if(endchar==F3&&turn){
		XoaManHinh();
		UpdateUI(15,11,infor);
		return 1;
	}
	if(endchar==ESC) // esc
	{
		return YesNoUI(board1.x1+30,9,"Ban co muon thoat chuong trinh Yes/No(Y/N):");
	}
}

int Search(int x,int y){
	gotoxy(x,y);
	int xcur= wherex(),ycur =wherey();
	int endchar,key,result;
	bool turn=false;
	char word[20];
	NODEWORD infor;
	while(1){
		turn = false;
		gotoxy(xcur,ycur); // di chuyen con tro toi sau chuoi~ nhap tu can tim
		Setcolor(15); 
		Yescursortype();
		strcpy(word,KeyboardHit_alpha(xcur,ycur,20,endchar));
		//if(!strncmp(word,"0",1)  || !strlen(word) || (word[0]==(char)ENTER  && word[1]=='\0'&&  endchar == ENTER))
		if(endchar==F1||endchar==F2||endchar==ESC)	
		{
			//if f1 f2 thi chay functionkey 
			key=FunctionKeys_Search(endchar);
			if(key==1)
				return 1;
			if(key==0)
				break;
		//else binh thuongv
		}
		else if(!strlen(word))
			continue;
		//bat dau tim word trong ds
		else if(endchar==ENTER){
			result=ResultUI(board3.x1+1,board3.y1+1,word,infor);
		}
			
		//if tim duoc word thi f3 co hieu luc( hien nut f3)
	
		if(result){
			turn = true;
			gotoxy(bx1+40,5);
			printf("[F3]: Xem chi tiet va chinh sua tu \n");
		}
		//else an nut f3
		else
		{
			turn = false;
			ClearLine(bx1+40,5,35);//clear printf f3
		}
		//if ma hien kq ,ma muon an tiep cac phim f1 f2 ecs 
		endchar=getch();
		if(endchar==128 || endchar ==0){
			endchar= getch();
			endchar+=128;
		}
		if(endchar==F1||endchar==F2||endchar==F3||endchar==ESC)	
		{
			//if f1 f2 f3 thi chay functionkey , if reult!=NULL thi turn = true-> f3 co hieu luc
			key=FunctionKeys_Search(endchar,turn,infor);
			if(key==1)
				return 1;
			if(key==0)
				break;
		}
		
		//xoa cac khung de tim 1 word khac
		ClearLine(bx1+40,5,35);//clear printf f3
		ClearLine(xcur,ycur,strlen(word));//clear line search
		ClearBoard(board3.x1+1,board3.y1,board3.x2-board3.x1-1,board3.y2-board3.y1-1);//clear b3
	}	
	return 0;
}
char* KeyboardHit_Search(int x,int y,int n,int &endchar,NODEWORD &infor,bool &turn){
	char *S=new char [n+1]; 
	int i=0; 
	int c,hash;
	int	result;
	gotoxy (x, y);
	while (1) { 
		Yescursortype();
	    endchar =' ';
		c=getch(); 		
		c=tolower(c);
		if (c==224 || c==0) { 
		 c=getch() ;		 
		 c+=128;
		}
		if( c== ESC || c==F1 || c==F2|| (result&&c==F3))
		{ 
			endchar = c ; 
			break ;
		}
		if(c==BACKSPACE){
			if(i){
				printf("\b \b");
				i--;
				if(i>0)
				goto Find;
			}
		}
			
		if (!(isalnum(c)||strchr(" ?.\":`~!@#$\%^&*()",c))||i>=n-1||c==ENTER) 
			continue;  
		printf("%c",char(c));
		S[i++]=c;
	Find:
		S[i]=NULL;
		hash= Hashfunc(S);
		Nocursortype();
		ClearBoard(board2.x1+1,board2.y1,board2.x2-board2.x1-1,board2.y2-board2.y1-1);//clear b3
		ClearBoard(board3.x1+1,board3.y1,board3.x2-board3.x1-1,board3.y2-board3.y1-1);//clear b3
		PrintBucketUI3(hash,i,S); 
		result=ResultUI(board3.x1+1,board3.y1+1,S,infor);
		//if tim duoc word thi f3 co hieu luc( hien nut f3)	
		if(result){
			turn = true;
			gotoxy(bx1+40,5);
			printf("[F3]: Xem chi tiet va chinh sua tu \n");
		}
		//else an nut f3
		else
		{
			turn = false;
			ClearLine(bx1+40,5,35);//clear printf f3
		}
		gotoxy(x+i,y);
		if (i==n) 
			break ;
	}
	S[i]=NULL;
	return S;	
}
int Search2(int x,int y){
	gotoxy(x,y);
	int xcur= wherex(),ycur =wherey();
	int endchar,key,result=0;
	bool turn=false;
	char word[20];
	NODEWORD infor;
	while(1){
		turn = false;
		gotoxy(xcur,ycur); // di chuyen con tro toi sau chuoi~ nhap tu can tim
		Setcolor(15); 
		Yescursortype();
		strcpy(word,KeyboardHit_Search(xcur,ycur,20,endchar,infor,turn));
		//if(!strncmp(word,"0",1)  || !strlen(word) || (word[0]==(char)ENTER  && word[1]=='\0'&&  endchar == ENTER))
		if(endchar==F1||endchar==F2||endchar==ESC)	
		{
			//if f1 f2 thi chay functionkey 
			key=FunctionKeys_Search(endchar);
			if(key==1)
				return 1;
			if(key==0)
				break;
		}			
		
		//if ma hien kq ,ma muon an tiep cac phim f1 f2 ecs 
		if(endchar==128 || endchar ==0){
			endchar= getch();
			endchar+=128;
		}
		if(endchar==F1||endchar==F2||endchar==F3||endchar==ESC)	
		{
			//if f1 f2 f3 thi chay functionkey , if reult!=NULL thi turn = true-> f3 co hieu luc
			key=FunctionKeys_Search(endchar,turn,infor);
			if(key==1)
				return 1;
			if(key==0)
				break;
		}
	}	
	return 0;
}
void mainUI(){
	do{
	Main:
		int xcur=UI();
		gotoxy(xcur,board1.y1+1);
		
		Yescursortype();
		int key=Search2(xcur,board1.y1+1);
		if(key)
			goto Main;
		//ket thuc (esc) va luu file
		if(!key)
		{
			SaveBucket();
			break;
		}
	}while(1);
}
int main(){
	resizeConsole(1200,750);
	Load(filename,"rb");
	mainUI();
	XoaManHinh();
	printf("Chuong trinh da dong!\n");
	getch();
}

