#include "define.h"

/*------------------------������------------------------*/
int main()
{
	char filename[100], copy_filename[100];//cnf�ļ���ȡ���������� 
	char sudo_filename[20];//�����ļ� 
	int op = 1, SAT = 1, SuDoKu = 1;//����swith��֧
	int flag_cnf = 0;//�����ж�cnf�ļ��Ƿ��ȡ�ɹ�
	int flag_sudo = 0;//�����ж������ļ��Ƿ��ȡ�ɹ�
	int way_sudo = 0;//sudo����ʽ 
	while (op) {
		system("cls");
		printf("\n---Menu For Puzzle Or SAT-----\n");
		printf("1.SAT        2.BinaryPuzzle\n");
		printf("0.Exit\n");
		printf("------------------------------\n");
		printf("������0~2��\n");
		printf("----------\n");
		scanf("%d", &op);
		switch (op) {
			case 1:
				while (SAT) {
					system("cls");
					printf("\n--------Menu For SAT--------------\n");
					printf("1.Readfile		2.Savefile\n");
					printf("3.Traversefile		4.Dpll\n");
					printf("0.Exit\n");
					printf("----------------------------------\n");
					printf("������0~4��\n");
					printf("----------\n");
					scanf("%d", &SAT);
					switch (SAT) {
						case 1:
							printf("�������ȡ��cnf�ļ�����\n");
							scanf("%s", filename);
							strcpy(copy_filename, filename);
							struct Clause * root = Readfile(filename);
							if (root != NULL){
								printf("�ļ���ȡ�ɹ���\n");
								flag_cnf = 1;
							} 
							else printf("�ļ���ȡʧ�ܣ�\n");
							getchar();getchar();
							break;
						case 2:
							if (flag_cnf) {
								if (Savefile(root)) {
									printf("�ļ�����ɹ���\n");
								}
								else printf("�ļ�����ʧ�ܣ�\n");
							}
							else printf("�ļ���δ��ȡ��\n");
							getchar();getchar();
							break;
						case 3:
							if (flag_cnf) Traversefile(root);
							else printf("�ļ���δ��ȡ��\n");
							getchar();getchar();
							break;
						case 4:
							if (flag_cnf) {
								printf("��ѡȡ��ⷽʽ��\n");
								printf("1.�Ż�ǰ	2.�Ż���\n");
								scanf("%d", &WAY); 
								clock_t start, end; 
								    start = clock();
							    if(dpll(root) == OK){
							        end = clock();
							        printf("�ļ��н�!\n");
							        printf("���ʱ�䣺%dms\n", end - start);
							        for (i = 1; i <= wordnumber; i++) {
							            temp = (variate[i] == 0 ? -1 : 1) * i;
							            printf("%d ", temp);
							            if (i%10==0) putchar('\n');
							        } 
							        putchar('\n');
							        writeResult(copy_filename, 1, end - start);
							    }
								else{
							        end = clock();
							        printf("�ļ��޽�!\n");
							        printf("���ʱ�䣺%dms\n", end - start);
							        putchar('\n');
							        writeResult(copy_filename, 0, end - start);
							    }
							    flag_cnf = 0;
							    //destoryClauses(root);
							}
							else printf("�ļ���δ��ȡ��\n");
							getchar();getchar();
							break;
						case 0:
							break;
						default:
							printf("�������\n");
							getchar();getchar();
							break;
					}
				}
				getchar();getchar();
				break;
			case 2:
				while (SuDoKu) {
					system("cls");
					printf("\n--------Menu For BinaryPuzzle-----------------\n");
					printf("1.ReadSudokuBureau	2.Play\n");
					printf("3.SetCNFfile		4.Dpll For Answer Check\n");
					printf("0.Exit\n");
					printf("----------------------------------------------\n");
					printf("������0~4��\n");
					printf("----------\n");
					scanf("%d", &SuDoKu);
					switch (SuDoKu) {
						case 1:
							printf("������Ҫ��ȡ�����������ļ�����\n");
							scanf("%s", sudo_filename);
							Readqipan(sudo_filename);
							Showqipan(qipan);
							flag_sudo = 1;
							getchar();getchar();
							break;
						case 2:
							if (flag_sudo) PlaySuDoKu(qipan);
							else printf("�����ļ���δ��ȡ��\n");
							getchar();getchar();
							break;
						case 3:
							if (flag_sudo){
								printf("��ѡ��\n1.ֱ����⣡	2.����Play��Ľ����\n");
								scanf("%d", &way_sudo);
								if (way_sudo == 1){
									Resetqipan(qipan);
									SetCNFfile(qipan);	
								}
								else{
									if (Checkqipan(qipan)) SetCNFfile(qipan);
									else printf("���̻�δ����������������ϣ�\n");
								}
							}
							else printf("�����ļ���δ��ȡ��\n");
							getchar();getchar();
							break;
						case 4:
							if (flag_sudo){
								char filename_sudocopy[15];
								strcpy(filename_sudocopy, filename_setcnf);
								struct Clause * root_sudo = Readfile(filename_sudocopy);
								clock_t t1, t2;
								t1 = clock();
								if(dpll(root_sudo) == OK){
									t2 = clock();
									char file_sudoresult[15];
									strcpy(file_sudoresult, filename_setcnf);
									if (way_sudo == 1){
										printf("Dpll���ɹ������Ϊ��\n");
										for (i = 0; i < 36; i++){
											printf("%d ", variate[i + 1]);
											if ((i + 1) % 6 == 0) putchar('\n');
										}	
									}
									else printf("Dpll���ɹ��������ȷ��\n");
									writeResult(file_sudoresult, 1, t2 - t1);
									//destoryClauses(root_sudo);
								}
								else printf("Dpll���ʧ�ܣ��������\n�ɼ������ԣ�\n");
							}
							else printf("�����ļ���δ��ȡ��\n");
							getchar();getchar();
							break;
						case 0:
							break;
						default:
							printf("�������\n");
							getchar();getchar();
							break;
					}
				}
				getchar();getchar();
				break;
			case 0:
				break;
			default:
				printf("�������\n");
				getchar();getchar();
				break;	
		}//end of switch	
	}//end of while
	printf("��ӭ�´�ʹ�ñ�ϵͳ��\n");
	system("pause");
	return 0; 
}//end of main
