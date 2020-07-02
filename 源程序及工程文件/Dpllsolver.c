#include "define.h"

/*------------------------DPLL�㷨------------------------*/

/*�жϵ��Ӿ䣬���ص��Ӿ��������*/ 
int isUnitClause(struct Clause * root){
    struct Clause * T = root;
    while(T != NULL){
        if(T->head == NULL) continue;
        if(T->head->next == NULL) return T->head->value;
        T = T->next;
    }
    return 0;
}

/*�����Ӿ�*/ 
status removeClause(struct Clause * root){
    temp = isUnitClause(root);
    if(temp == 0) return ERROR; //��ʾû�е��Ӿ�
    variate[abs(temp)] = temp > 0 ? 1 : 0;
    struct Clause * T = root, *pre_T = createClause();
    while(T != NULL){
        struct Literal * current_Literal = T->head, * pre_Literal = createLiteral();
        while(current_Literal != NULL){
            if(current_Literal->value == temp){  //ɾ�����������ֵ��Ӿ� 
                if(T == root){
                    *(root) = *(root->next);
                    T = NULL;
                }
				else{
                    pre_T->next = T->next;
                    T = pre_T;
                }
                break;
            } 
			else if (current_Literal->value == -temp){ //ɾ����Ϊ�෴�������� 
                if(current_Literal == T->head) T->head = current_Literal->next;
				else pre_Literal->next = current_Literal->next;
                current_Literal = pre_Literal;
                continue;
            }
            pre_Literal = current_Literal;
            current_Literal = current_Literal->next;
        }
        pre_T = T;
        T = (T == NULL) ? root : T->next;
    }
    return OK;
}

/*�ж�����*/ 
int judgesign(int a){
    return a>0 ? 1 : -1;
}

/*�ж�ֻ��һ�ֳ�����ʽ�����֣��������ֵ�ֵ*/
int isPureLiteral(struct Clause * root){
    int *mark = (int *)calloc(wordnumber + 1, sizeof(int));//��־���飬��ʼ��Ϊ0 
    struct Clause * T = root;
    while(T != NULL){
        struct Literal * current_Literal = T->head;
        while(current_Literal != NULL){
        	if (mark[abs(current_Literal->value)] != 2){
            	temp = mark[abs(current_Literal->value)];
            	if(temp == 0) mark[abs((current_Literal->value))] = judgesign(current_Literal->value);
            	else if(temp == 1 && judgesign(current_Literal->value) == -1) mark[abs(current_Literal->value)] = 2;
				else if(temp == -1 && judgesign(current_Literal->value) == 1) mark[abs(current_Literal->value)] = 2;//�����ִ�����ʽ���Ϊ2
			}
            current_Literal = current_Literal->next;
        }
        T = T->next;
    }
    for(i = 1; i <= wordnumber; i++){
        if(mark[i] == -1 || mark[i] == 1) return i * mark[i];
    }
    return 0; //û����һ����ʽ���ֵ����� 
}

/*����ֻ��һ�ֳ�����ʽ������*/ 
status removePureLiteral(struct Clause * root){
    temp = isPureLiteral(root);
    if(temp == 0) return ERROR; //��ʾû��ֻ��һ�ֳ�����ʽ������ 
    variate[abs(temp)] = temp > 0 ? 1 : 0;
    struct Clause * T = root, * pre_T = createClause();
    while(T != NULL){  //ɾ����Ӧ�Ӿ� 
        struct Literal * current_literal = T ->head;
        while(current_literal != NULL){
            if(current_literal->value == temp){
                if(T == root){
                    *(root) = *(root->next);
                    T = NULL;
                }
				else{
                    pre_T->next = T->next;
                    T = pre_T;
                }
                break;
            }
            current_literal = current_literal->next;
        }
        pre_T = T;
        T = (T == NULL) ? root : T->next;
    }
    return OK;
}


/*ѡȡ������ֵ����*/ 
int chooseLiteral(struct Clause *root){
	return root->head->value;
}

/*��¡�Ӿ� */
struct Clause * cloneClause(struct Clause * re_clause){
    struct Clause * clone_Clause = createClause();
    struct Literal * current_Literal = re_clause->head, * pre_Literal = NULL;
    while(current_Literal != NULL){
        struct Literal * clone_Literal = createLiteral();
        clone_Literal->value = current_Literal->value;
        if(clone_Clause->head == NULL) clone_Clause->head = clone_Literal;
        if(pre_Literal != NULL) pre_Literal->next = clone_Literal;
        pre_Literal = clone_Literal;
        current_Literal = current_Literal->next;
    }
    return clone_Clause;
}


/*��¡ȫ���ṹ����ѡȡ��������Ϊ���Ӿ����洢�ṹ��*/ 
struct Clause * cloneAll(int a, struct Clause * root){
    variate[abs(a)] = a > 0 ? 1 : 0;
    struct Clause * T = root, * new_root = NULL, *pre_Clause = NULL;
    while(T != NULL){
        struct Clause * current_Clause = cloneClause(T);
        if(new_root == NULL) new_root = current_Clause;
        if(pre_Clause != NULL) pre_Clause->next = current_Clause;
        pre_Clause = current_Clause;
        T = T->next;
    }
    struct Clause * new_Clause = createClause();
    struct Literal * new_literal = createLiteral();
    new_literal->value = a;
    new_Clause->head = new_literal;
    new_Clause->next = new_root;
    return new_Clause;
}

/*���ٴ洢�ṹ*/ 
void destoryClauses(struct Clause * root){
    while(root != NULL){
        struct Clause * next_r = root->next;
        if(root->head != NULL){
            struct Literal * current_Literal = root ->head;
            while(current_Literal != NULL){
                struct Literal * next_Literal = current_Literal->next;
                free(current_Literal);
                current_Literal = next_Literal;
            }
        }
        free(root);
        root = next_r;
    }
}


/*�ж������Ƿ��Ϊ��һ��ʽ����*/ 
status isAllPureLiteral(struct Clause * root){
    int *mark = (int *)calloc(wordnumber+1,sizeof(int));
    struct Clause * T = root;
    while(T != NULL){
        struct Literal * current_literal = T->head;
        while(current_literal != NULL){
            temp = mark[abs(current_literal->value)];
            if(temp == 0) mark[abs(current_literal->value)] = judgesign(current_literal->value);
            else if(temp != judgesign(current_literal->value)) return ERROR;
            current_literal = current_literal->next;
        }
        T = T ->next;
    }
    T = root;
    while(T != NULL){
        struct Literal * current_literal = T ->head;
        while(current_literal != NULL){
            if(variate[abs(current_literal->value)] == -1) variate[abs(current_literal->value)] = current_literal->value > 0 ? 1 : 0;
            current_literal = current_literal->next;
        }
        T = T->next;
    }//��ʱ��Ȼ��Ϊ�ռ������Ѿ�����ɽ��������������������ֵ 
    return OK;
}

/*�ж��Ƿ���ڿ��Ӿ�*/ 
status isEmptyClause(struct Clause * root){
    struct Clause * T = root;
    while(T != NULL){
        if(T->head == NULL) return OK;
        T = T->next;
    }
    return ERROR;
}

/*��鵱ǰ�Ƿ�����*/ 
status check(struct Clause * root){
    if(isEmptyClause(root)) return ERROR; //��������
    if(isAllPureLiteral(root)) return OK; //�������� 
    return Untrue;//����δȷ�� 
}


/*dpll�㷨*/ 
status dpll(struct Clause * root){
    temp = check(root);
    if(temp != Untrue){
        destoryClauses(root);
        return temp;
    }//����δȷ������������ؽ�� 
    while(1){//�����Ӿ� 
        temp = check(root);
        if(temp != Untrue){
            destoryClauses(root);
            return temp;
        }//ͬ�� 
        if(!removeClause(root)) break;//�����Ӿ䣬û�еĻ�����ѭ�� 
    }
    if (WAY == 2){
		while(1){ //����ֻ��һ����ʽ���ֵ����� 
        	temp = check(root);
        	if(temp != Untrue){
            	destoryClauses(root);
            	return temp;
        	}
        	if(!removePureLiteral(root)) break; 
    	}
	}
    int new_count = chooseLiteral(root);//ѡȡ������ֵ 
    if(dpll(cloneAll(new_count, root)) == OK) return OK;
    else{
        temp = dpll(cloneAll(-new_count, root));//������ɹ���ѡȡ������ֵ���෴�� 
        destoryClauses(root);
        return temp;
    }
}

/*�����д��ͬ���ļ�*/ 
void writeResult(char * filename, int flag, int time){
    int temp = 0;
    for (i = 0; i < 100; i++){
		if (filename[i] == '.'){
			filename[i + 1] = 'r';
			filename[i + 2] = 'e';
			filename[i + 3] = 's';
			break;
		}
	}
	FILE * fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("���������ʧ�ܣ�\n");
        exit(1);
    }
    if(flag == 1){
        fprintf(fp,"s 1\n");
        fprintf(fp,"v ");
        for (i = 1; i <= wordnumber; i++) {
            temp = (variate[i] == 0 ? -1 : 1) * i;
            fprintf(fp, "%d ", temp);
            if (i%10 == 0) fprintf(fp, "\n");
        }
        fprintf(fp, "\nt %d ms\n", time);
    }
    else{
        fprintf(fp,"s 0\n");
        fprintf(fp,"v \n");
        fprintf(fp, "t %d ms\n", time);
    }
    printf("���������ɹ���\n");
    fclose(fp);
}
