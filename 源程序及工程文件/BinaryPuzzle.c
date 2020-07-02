#include "define.h"

int j, k, z, final, add, num1, num2, r, l;//r, lΪ����

/*------------------------SuDoKu------------------------*/

/*��ȡ�����ļ�*/
void Readqipan(char *filename){
	FILE *fp;
    fp = fopen(filename,"r");
    if(fp == NULL){
        printf("�ļ���ʧ��!\n");
    }
    else {
    	int integer;//���ڽ�������
		i = 0; 
		while (fscanf(fp, "%d", &integer) != EOF){
			qipan[i].num = integer;
			if (integer != -1) qipan[i].flag = 1;
			else qipan[i].flag = 0;
			i++;
		}
    }
    fclose(fp);
    printf("��ȡ�ɹ���\n");
}

/*�����ǰ����*/
void Showqipan(struct Qipan qipan[]){
	for (i = 0; i < 36; i++){
		if (qipan[i].num == -1) printf("_ ");
		else printf("%d ", qipan[i].num);
		if ((i + 1)%6 == 0) putchar('\n');
	}
}

/*��ʼ������*/
void Resetqipan(struct Qipan qipan[]){
	for (i = 0; i < 36; i++){
	    if(qipan[i].flag != 1) qipan[i].num = -1;
	}
} 

/*��������*/
void PlaySuDoKu(struct Qipan qipan[]){
	printf("��ǰ���̣�\n");
	Showqipan(qipan);
	printf("��ֱ������У��У�1��0�����ȱ��\n");
	printf("���¿�ʼ��������������0.\n������д������Ctrl+Z.\n");
	int answer[3] = {-1};
	while (scanf("%d", &answer[0])!=EOF){
		for(i = 1; i < 3; i++){
			scanf("%d",&answer[i]); 
	    }
	    if (answer[0] == 0 && answer[1] == 0 && answer[2] == 0){
			Resetqipan(qipan);
			printf("���¿�ʼ��\n");
		}
		else {
			temp = (answer[0] - 1)*6 + answer[1];
	        if (qipan[temp - 1].flag == 1){
	    	printf("��λ��Ϊ��ʼλ�ã����ɸģ�\n");
			}
			else qipan[temp - 1].num = answer[2];
		}
		putchar('\n');
	    Showqipan(qipan);
	    printf("\n��������!\n");
	}
}

/*��������Ƿ������*/
status Checkqipan(struct Qipan qipan[]){
	for (i = 0; i < 36; i++){
		if (qipan[i].num == -1) return ERROR;
	}
	return OK;
}

/*ת��ΪCNF�ļ�*/
void SetCNFfile(struct Qipan qipan[]){
	printf("����Ҫת��ΪCNF�ļ����ļ�����\n");
	scanf("%s", filename_setcnf);
	FILE *fp;
	fp = fopen(filename_setcnf, "w");
	if (fp == NULL){
		printf("�ļ���ʧ�ܣ�\n");
		exit(1);
	}
	int f_sum = 0;//��ʽ��������
	for (i = 0; i < 36; i++){
		if (qipan[i].num != -1) f_sum++;
	}
	fprintf(fp,"p cnf 606 %d\n", f_sum + 2286);
	
	/**********************************/
	//����������Ϣ 
	/**********************************/ 
	
	for (i = 0; i < 36; i++){
		if (qipan[i].num == 1)
			fprintf(fp, "%d 0\n", i + 1);
		else if (qipan[i].num == 0)
			fprintf(fp, "%d 0\n", -(i + 1));
		else continue;
	} 
	/**********************************/
	//Լ��1���У�����û������������0��1 
	/**********************************/ 
	
	//����6�� 
	for (r = 1; r <= 6; r++){
		for (l = 1; l <= 4; l++){
			for (i = 0; i < 3; i++){
				temp = (r - 1)*6 + l + i;
				fprintf(fp, "%d ", temp);
				if (i == 2)
					fprintf(fp, "0\n");
			}
			for (i = 0; i < 3; i++){
				temp = (r - 1)*6 + l + i;
				fprintf(fp, "%d ", -temp);
				if (i == 2)
					fprintf(fp, "0\n");
			}
		}
	}
	//����6��
	for (l = 1; l <= 6; l++){
		for (r = 1; r <= 4; r++){
			for (i = 0; i < 3; i++){
				temp = (r + i - 1)*6 + l;
				fprintf(fp, "%d ", temp);
				if (i == 2)
					fprintf(fp, "0\n");
			}
			for (i = 0; i < 3; i++){
				temp = (r + i - 1)*6 + l;
				fprintf(fp, "%d ", -temp);
				if (i == 2)
					fprintf(fp, "0\n");
			}
		}
	}
	/**********************************/
	//Լ��2���У�����0��1�ĸ�����ͬ 
	/**********************************/
	
	int order[16][5] = {{3,4,5,6},{2,4,5,6},{2,3,5,6},{2,3,4,6},{2,3,4,5}
						,{1,4,5,6},{1,3,5,6},{1,3,4,6},{1,3,4,5}
						,{1,2,5,6},{1,2,4,6},{1,2,4,5}
						,{1,2,3,6},{1,2,3,5}
						,{1,2,3,4}};
	//����6�� 
	for (r = 1; r <= 6; r++){
		for (k = 0; k < 15; k++){
			for(j = 0; j < 4; j++){
				temp = (r - 1)*6 + order[k][j];
				fprintf(fp, "%d ", temp);
				if (j == 3) fprintf(fp, "0\n");
			}
		}
	}
	for (r = 1; r <= 6; r++){
		for (k = 0; k < 15; k++){
			for(j = 0; j < 4; j++){
				temp = (r - 1)*6 + order[k][j];
				fprintf(fp, "%d ", -temp);
				if (j == 3) fprintf(fp, "0\n");
			}
		}
	}
	//����6��
	for (l = 1; l <= 6; l++){
		for (k = 0; k < 15; k++){
			for(j = 0; j < 4; j++){
				temp = (order[k][j] - 1)*6 + l;
				fprintf(fp, "%d ", temp);
				if (j == 3) fprintf(fp, "0\n");
			}
		}
	}
	for (l = 1; l <= 6; l++){
		for (k = 0; k < 15; k++){
			for(j = 0; j < 4; j++){
				temp = (order[k][j] - 1)*6 + l;
				fprintf(fp, "%d ", -temp);
				if (j == 3) fprintf(fp, "0\n");
			}
		}
	}
	/**********************************/
	//Լ��3��û����ͬ���л��� 
	/**********************************/
	add = 36;
	//����6��
	for (i = 1; i <= 6; i++){
		for (j = i + 1; j <= 6; j++){
			final = add + 19;
			for (k = 1; k<= 6; k++){
				num1 = (i - 1)*6 + k;
				num2 = (j - 1)*6 + k;
				fprintf(fp,"%d -%d 0\n%d -%d 0\n-%d -%d %d 0\n", num1,add+1,num2,add+1,num1,num2,add+1);
				fprintf(fp,"-%d -%d 0\n-%d -%d 0\n%d %d %d 0\n", num1,add+2,num2,add+2,num1,num2,add+2);
				fprintf(fp,"-%d %d 0\n-%d %d 0\n%d %d -%d 0\n", add+1,add+3,add+2,add+3,add+1,add+2,add+3);
				add+=3;
			}
			for (z = 1; z <= 6; z++){
				fprintf(fp,"%d %d 0\n", final - 3*(z - 1) - 1,final);
			}
			fprintf(fp,"-%d -%d -%d -%d -%d -%d -%d 0\n",final-16,final-13,final-10,final-7,final-4,final-1,final);
			add = final;
		}
	}
	//����6��
	for (i = 1; i <= 6; i++){
		for (j = i + 1; j <= 6; j++){
			final = add + 19;
			for (k = 1; k<= 6; k++){
				num1 = (k - 1)*6 + i;
				num2 = (k - 1)*6 + j;
				fprintf(fp,"%d -%d 0\n%d -%d 0\n-%d -%d %d 0\n", num1,add+1,num2,add+1,num1,num2,add+1);
				fprintf(fp,"-%d -%d 0\n-%d -%d 0\n%d %d %d 0\n", num1,add+2,num2,add+2,num1,num2,add+2);
				fprintf(fp,"-%d %d 0\n-%d %d 0\n%d %d -%d 0\n", add+1,add+3,add+2,add+3,add+1,add+2,add+3);
				add+=3;
			}
			for (z = 1; z <= 6; z++){
				fprintf(fp,"%d %d 0\n", final - 3*(z - 1) - 1,final);
			}
			fprintf(fp,"-%d -%d -%d -%d -%d -%d -%d 0\n",final-16,final-13,final-10,final-7,final-4,final-1,final);
			add = final;
		}
	}
	fclose(fp);
	printf("��������606	��ʽ����%d\n", f_sum + 2286);
}
