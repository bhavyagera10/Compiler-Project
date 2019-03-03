#include "parser.h"

int hash_size = 1000;
#define PTrows 50
#define PTcols 55
#define Ngrammar 90

int hashcode(char* string){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*37 + string[i])%hash_size;
	}
	return hash;
}

hashtable createHashTable(){
	hashtable ht = (hashtable)malloc(sizeof( helement)*(hash_size+1));
	//addMem(sizeof(element)*(hash_size+1), "Creatinn HashTable");
	if(ht==NULL) printf("Memory Error!\n");	
	return ht;
}

void insertToHash(helement e,hashtable ht){

	helement e_1 = searchInTable(ht, e->value);
	if(e_1 != NULL) {
		printf("***************Collision*************** %s %s\n",e->value, e_1 -> value);
		// return e_1;
	}
	int hash = hashcode(e->value);
	ht[hash] = e;
	return ;
}


helement searchInTable(hashtable ht,char* string){
	int hash = hashcode(string);
	if(ht[hash]==NULL)
		return NULL;
	else 
		return ht[hash];
}

helement createHashElement(char* string){
	helement e = (helement)malloc(sizeof(struct Helement));
	// addMem(sizeof(struct elementOfHash), "createElement");
	e->rules = (int*)malloc(sizeof(int)*10);
	e->first = NULL;
	e->follow =NULL;
	e->nrules=0;
	e->value = (char*) malloc(sizeof(char)*40);
	strcpy(e->value,string);
	if(string[0]>='A' && string[0]<='Z'){
    			e->flag=1;
    		}
    		else if(strcmp(string,"eps")==0){
    			e->flag=0;
    		}
    		else
    			e->flag=-1;
	return e;
}

node* readGrammar(char* filename,hashtable ht){
	
	node* grules=(node*)malloc(Ngrammar*sizeof(node));

	FILE* fp=fopen(filename,"r");
	if(fp==NULL){
		printf("FILE ERROR\n");
		exit(1);
	}
	char* tok;
	int i=0;
	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
    while(fgets(grLine,400,fp)!=NULL){
    	
    	grules[i]=(node)malloc(sizeof(struct Node));
    	tok = strtok (grLine,delimit);
    	
    	node temp=grules[i];
		temp->string=(char*)malloc(40*sizeof(char));
		strcpy(temp->string,tok);
 		temp->flag=-1;
 		
 		helement h= searchInTable(ht,tok);
 		if(h==NULL){
 			h=createHashElement(tok);
 			insertToHash(h,ht);
 		}
 		h->rules[h->nrules]=i;
 		h->nrules++;
 		tok = strtok (NULL, delimit);

 		
     	while (tok != NULL){
     		
     		temp->next=(node)malloc(sizeof(struct Node));;
     		temp=temp->next;
    	 	temp->string=(char*)malloc(40*sizeof(char));
    		strcpy(temp->string,tok);
     		if(tok[0]>='A' && tok[0]<='Z'){
    			temp->flag=1;
    		}
    		else if(strcmp(tok,"eps")==0){
    			temp->flag=0;
    		}
    		else
    			temp->flag=-1;
		
			helement h= searchInTable(ht,tok);
	 		if(h==NULL){
	 			h=createHashElement(tok);
	 			insertToHash(h,ht);
	 		}

			tok = strtok (NULL, delimit);
			
		}
    	
    	// printrule(grules[i]);
    	i++;
    }
    // printf("%s\n",grules[45]->next->string);
   // printrule(grules[0]);
    fclose(fp);
    return grules;
}


void getFirst(hashtable ht,char* firstfile){
	FILE * fp = fopen(firstfile, "r");
	if (fp == NULL) {
		printf("Unable to read follow file.\n");
		return ;
	}	

	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
	
	char *tok;
   	tok = (char*) malloc(sizeof(char)*50);
    
    while(fgets(grLine,400,fp)!=NULL){    
    	node sr = (node)malloc(sizeof(struct Node));
   		tok = strtok (grLine,delimit);
   		helement nonterminal = searchInTable(ht, tok);
   		tok = strtok(NULL, delimit);

   		nonterminal->first=(node)malloc(sizeof(struct Node));
   		node temp=nonterminal->first;

  		while (tok != NULL){

  				temp->string=(char*)malloc(sizeof(char)*40);
  				temp->flag=1;
  				strcpy(temp->string,tok);
  				tok = strtok (NULL, delimit);
  				if(tok!=NULL){
  				temp->next=(node)malloc(sizeof(struct Node));
  				temp=temp->next;
    			}

  		}
  		temp=NULL;
  		// printf("PRINTING FIRST\n");
  		// printf("%s\n",nonterminal->value );
  		// printrule(nonterminal->first);
   	}  
	fclose(fp);
	return;



}

void getFollow(hashtable ht,char* followfile){
	FILE * fp = fopen(followfile, "r");
	if (fp == NULL) {
		printf("Unable to read follow file.\n");
		return ;
	}	

	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
	
	char *tok;
   	tok = (char*) malloc(sizeof(char)*50);
    
    while(fgets(grLine,400,fp)!=NULL){    
    	node sr = (node)malloc(sizeof(struct Node));
   		tok = strtok (grLine,delimit);
   		helement nonterminal = searchInTable(ht, tok);
   		tok = strtok(NULL, delimit);

   		nonterminal->follow=(node)malloc(sizeof(struct Node));
   		node temp=nonterminal->follow;

  		while (tok != NULL){

  				temp->string=(char*)malloc(sizeof(char)*40);
  				temp->flag=1;
  				strcpy(temp->string,tok);
  				tok = strtok (NULL, delimit);
  				if(tok!=NULL){
  				temp->next=(node)malloc(sizeof(struct Node));
  				temp=temp->next;
    			}

  		}
  		temp=NULL;
  		// printf("PRINTING FOLLOW\n");
  		// printf("%s\n",nonterminal->value );
  		// printrule(nonterminal->follow);
   	}  
	fclose(fp);
	return;

}



void printrule(node ls){

	node temp=ls;
	while(temp!=NULL){
		printf("%s %d\t",temp->string, temp->flag );
		
		temp=temp->next;
	}
	printf("\n");

return ;


}

void printRuleNo(helement h){
	for(int i=0;i<h->nrules;i++){
		printf("%d \n", h->rules[i]);
	}
}


int hashFun(char* string ){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*397 + string[i])%5000;
	}
	return hash;
}


int getColumnIndex(char* string){

	char* tokens[54]= {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID", "TK_WITH", "TK_PARAMETERS", 
	"TK_END", "TK_WHILE", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA",
	 "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV",
	  "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "$"};

	for(int i=0; i<54; i++){
		if(strcmp(string, tokens[i])==0)
		{
		  return i+1;
		}
		
	}
	return -1;
}

int getRowIndex(char* string){
  char* nt[50]= {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype",
  "constructedDatatype","remaining_list","stmts","typeDefinitions","typeDefinition","fieldDefinitions","fieldDefinition","moreFields",
  "declarations","declaration","global_or_not","otherStmts","stmt","assignmentStmt","singleOrRecId","new_24","funCallStmt","outputParameters","inputParameters",
  "iterativeStmt","conditionalStmt","elsePart","ioStmt","allVar","arithmeticExpression","expPrime","term","termPrime","factor","lowPrecedenceOperators",
  "highPrecedenceOperators","all","temp","booleanExpression","var","logicalOp","relationalOp","returnStmt","optionalReturn","idList","more_ids"};
  for(int i=0; i<50; i++)
  {
    if(strcmp(string, nt[i])==0)
    {
      return i;
    }
  }
  return -1;
}


parseTable createParseTable(hashtable ht,node* grules){

	// parseTable pt;
	parseTable pt=(parseTable)malloc(PTrows*sizeof(int*));

	for(int i=0;i<PTrows;i++){
		pt[i]=(int*)malloc(PTcols*sizeof(int));
	}

	for(int i=0;i<PTrows;i++){
		for(int j=0;j<PTcols;j++){
			pt[i][j]=-1;
			// printf("%d ",pt[i][j] );
		}
		// printf("\n");
	}

	node firstalpha;
	
	for(int i=0;i<Ngrammar;i++){
		
		
		firstalpha=(node)malloc(Ngrammar*sizeof(struct Node));
		firstalpha=getFirstAlpha(grules[i]->next, ht);

		char* nonterminal=(char*)malloc(40*sizeof(char));
		nonterminal=grules[i]->string;

		node temp=firstalpha;
		int eps=0,dollar=0;
		while(temp!=NULL){
			if(strcmp(temp->string,"eps")){
				pt[getRowIndex(nonterminal)][getColumnIndex(temp->string)]=i;
				
			}
			else{
				eps=1;
				node temp2= ht[hashcode(nonterminal)]->follow;
				while(temp2!=NULL){
				if(strcmp(temp2->string,"$")){
					dollar=1;
				}
				pt[getRowIndex(nonterminal)][getColumnIndex(temp2->string)]=i;
				temp2=temp2->next;
				}

			}
			temp=temp->next;
		}
		if(eps==0){
				node follow= ht[hashcode(nonterminal)]->follow;
				node temp2 = follow;
				while(temp2!=NULL){
				if(strcmp(temp2->string,"$")){
					dollar=1;
				}
				pt[getRowIndex(nonterminal)][getColumnIndex(temp2->string)]=-2;
				temp2=temp2->next;
				}
			}
		if(dollar==1 && eps==1){
			pt[getRowIndex(nonterminal)][getColumnIndex("$")]=i;
		}

		free(firstalpha);
	}
	return pt;
}

node getFirstAlpha(node rule, hashtable ht){//be careful while using this. first set ka first element is garbage. use first->next
	node first=(node)malloc(sizeof(struct Node));
	first->next=NULL;
	node temp=rule;
	while(temp!=NULL){

		mergeLists(first,ht[hashcode(temp->string)]->first);
		if(epsinFirst(temp,ht)){
			temp=temp->next;
			if(temp==NULL){
				// printf("eps detected\n");
				node temprandom=first->next;
				node addeps=(node)malloc(sizeof(struct Node));
				addeps->string = (char*)malloc(sizeof(char)*40);
				strcpy(addeps->string,"eps");
				//printf("%s\n",tempprev->next->string);
				addeps->flag=0;
				addeps->next=temprandom;
				first->next=addeps;
			}
			//printf("%s\n",first->string );
			continue;
		}

		break;
		
	}
	return first->next;

}

void mergeLists(node list1,node list2){//copies second list into first without duplicates


		node temp2=list2;
		node temp;
		node tempprev;
		while(temp2!=NULL){
			temp=list1;

			int flag=0;
			while(temp!=NULL){

				if(!strcmp(temp->string,temp2->string)){
					flag=1;
					break;
				}
				tempprev=temp;
				temp=temp->next;
			}
			if(flag==0 && strcmp(temp2->string,"eps")!=0 ){
				tempprev->next=(node)malloc(sizeof(struct Node));
				tempprev->next->string = (char*)malloc(sizeof(char)*40);
				strcpy(tempprev->next->string,temp2->string);
				//printf("%s\n",tempprev->next->string);
				tempprev->next->flag=temp2->flag;
				tempprev->next->next=NULL;

			}
			//printrule(list1);
			temp2=temp2->next;
		}


		//printrule(list1);
}


int epsinFirst(node nonterminal,hashtable ht){
	node temp=ht[hashcode(nonterminal->string)]->first;

	while(temp!=NULL){
		if(!strcmp(temp->string,"eps"))
			return 1;
		temp=temp->next;
	}
	return 0;
}

void main(){
	hashtable ht=createHashTable();
	node* grules=readGrammar("Grammar.txt",ht);
	// helement h=searchInTable(ht,"booleanExpression");
	getFollow(ht,"Follow.txt");
	getFirst(ht,"First.txt");
	parseTable pt=createParseTable(ht,grules);

	//parseTable pt=createParseTable(ht,grules);
	// printf("THIS IS THE FIRST ");
	// printrule(ht[hashcode(grules[46]->string)]->first);
	// node temp=getFirstAlpha(grules[1]->next,ht);
	
	// printrule(ht[hashcode(grules[46]->string)]->first);
	// printrule(temp);
	//printf("%d ",grules);


	// for(int i=56;i<Ngrammar;i++){
		// node firstalpha=(node)malloc(Ngrammar*sizeof(struct Node));
		// firstalpha=getFirstAlpha(grules[18]->next, ht);
		// printrule(firstalpha);
	// }
	
	for(int i=0;i<PTrows;i++){
		for(int j=0;j<PTcols;j++){
			printf("%d  ",pt[i][j] );
		}
		printf("\n");
	}	
	printf("%d\n",pt[getRowIndex("typeDefinitions")][getColumnIndex("TK_TYPE")]);
	// printf("%d\n",getColumnIndex("TK_MAIN"));
	// printf("%d\n",getRowIndex("booleanExpression"));

}