#include "define.h"

/*------------------------CNF�ļ�����------------------------*/

/*��������ʼ������*/

/*�½��Ӿ�*/ 
struct Clause * createClause(){
    struct Clause * new_clause = malloc(sizeof(struct Clause));
    new_clause->head = NULL;
    new_clause->next = NULL;
    return new_clause;
}

/*�½�����*/ 
struct Literal * createLiteral(){
    struct Literal * new_literal = malloc(sizeof(struct Literal));
    new_literal->next = NULL;
    new_literal->value = 0;
    return new_literal;
}

/*cnf�ļ���ȡ*/
struct Clause * Readfile(char * filename){
    FILE * fp;
    fp = fopen(filename,"r");
    if(fp == NULL){
        printf("�ļ���ʧ��!\n");
        exit(1);
    }
    char s[100];
    char *c;
    struct Clause * root = NULL, * current_Clause = NULL, * pre_Clause = NULL;
    struct Literal * current_Literal = NULL, * pre_Literal = NULL;
    while(fgets(s, 100, fp)){//���ж�ȡ 
        if(s[0] == 'c') continue;
        else if(s[0] == 'p'){
            sscanf(s, "p cnf %d %d", &wordnumber, &formulanumber);//����ʽ�����������빫ʽ�� 
			printf("������: %d	��ʽ��: %d\n", wordnumber, formulanumber);
            variate = (int *)calloc(wordnumber + 1, sizeof(int));
            for(i = 1; i <= wordnumber; i++) variate[i] = -1;//��ʼ��������飬-1��ʾδ��ȷ����ֵ 
        }
        else{
			//�����洢�ṹ 
            current_Clause = createClause();
            if(root == NULL) root = current_Clause;
            if(pre_Clause != NULL)  pre_Clause->next = current_Clause;
            c = strtok(s, (const char *) " ");//�ָ��ַ��� 
            while(c != NULL){
                current_Literal = createLiteral();
                temp = atoi(c);
                current_Literal->value = temp;
                if(temp != 0){
                    if(current_Clause->head == NULL) current_Clause->head = current_Literal;
                    if(pre_Literal != NULL) pre_Literal->next = current_Literal;
                }
                pre_Literal = current_Literal;
                c = strtok(NULL, (const char *) " ");
            }
            pre_Clause = current_Clause;
        }
    }
    fclose(fp);
    return root;
}

/*�������CNF�ļ���ʽ*/ 
void Traversefile(struct Clause * root){
    struct Clause* T = root;
    while (T != NULL){
        struct Literal * current_Literal = T->head;
        printf("��ʽ�� "); 
        while (current_Literal != NULL){
            printf("%d ", current_Literal->value);
            current_Literal = current_Literal->next;
        }
        if(T->next != NULL) printf("\n");
        T = T->next;
    }
    printf("\n�ļ�����ɹ���\n");
}

/*CNF�ļ�����*/ 
status Savefile(struct Clause * root){
	FILE *fp;
	char filename[20];
	struct Clause * T = root;
	printf("�������ļ���:\n");
	scanf("%s", filename);
	if ((fp = fopen(filename, "wb")) == NULL){
		printf("�ļ���ʧ�ܣ�\n");
		return ERROR;
	}
	else {
		fprintf(fp, "%s ", "p cnf");
		fprintf(fp, "%d ", wordnumber);
		fprintf(fp, "%d\n", formulanumber);
		while (T){
			struct Literal * current_Literal = T->head;
			while (current_Literal){
				fprintf(fp, "%d ", current_Literal->value);
				current_Literal = current_Literal->next;
			}
			if (T->next != NULL) fprintf(fp, "0\n");
			T = T->next;
		}
		fprintf(fp, "0");
	}
	fclose(fp);
	return OK;
}
