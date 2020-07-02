#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

typedef int status;

#define OK 1
#define ERROR 0
#define Untrue -1

//全局变量 
int wordnumber, formulanumber;//文字数，公式数 
int *variate;//用于判别文字的真值 
int i;//用于循环
int temp;//中间变量 
int WAY;//用于选择求解方式 

//存储结构
struct Literal{
    struct Literal * next;
    int value;//文字值 
};

struct Clause{
    struct Clause * next;
    struct Literal * head;
};

//用于保存棋盘 
struct Qipan{
	int flag;//用于标记是否为初始棋盘已确定的位置 
	int num;
};
struct Qipan qipan[36];//用于保存6阶棋盘信息

char filename_setcnf[15];//用于保存数独转化cnf文件名 

/*------------------------CNF文件处理------------------------*/

/*单个结点初始化函数*/

/*新建子句*/ 
struct Clause * createClause();
/*新建文字*/ 
struct Literal * createLiteral();
/*cnf文件读取*/
struct Clause * Readfile(char * filename);
/*遍历输出CNF文件公式*/ 
void Traversefile(struct Clause * root);
/*CNF文件保存*/ 
status Savefile(struct Clause * root);

/*------------------------DPLL算法------------------------*/

/*辅助函数，判断正负*/ 
int judgesign(int a);
/*判断单子句，返回单子句里的文字*/ 
int isUnitClause(struct Clause * root);
/*处理单子句*/ 
status removeClause(struct Clause * root);
/*判断只有一种出现形式的文字*/
int isPureLiteral(struct Clause * root);
/*处理只有一种出现形式的文字*/ 
status removePureLiteral(struct Clause * root);
/*选取假设真值文字*/ 
int chooseLiteral(struct Clause *root);
/*克隆子句*/
struct Clause * cloneClause(struct Clause * headp);
/*克隆全部结构并将选取的文字设为单子句加入存储结构中*/ 
struct Clause * cloneAll(int a, struct Clause * root);
/*销毁存储结构*/ 
void destoryClauses(struct Clause * root);
/*判断是否文字均为单值*/ 
status isAllPureLiteral(struct Clause * root);
/*判断是否存在空子句*/ 
status isEmptyClause(struct Clause * root);
/*检查当前是否满足*/ 
status check(struct Clause * root);
/*dpll算法*/ 
status dpll(struct Clause * root);
/*将结果写入同名文件*/ 
void writeResult(char * filename, int flag, int time);

/*------------------------SuDoKu------------------------*/

/*读取棋盘文件*/
void Readqipan(char *filename);
/*初始化棋盘*/
void Resetqipan(struct Qipan qipan[]);
/*输出当前棋盘*/
void Showqipan(struct Qipan qipan[]);
/*数独交互*/
void PlaySuDoKu(struct Qipan qipan[]);
/*检查棋盘是否填充满*/
status Checkqipan(struct Qipan qipan[]);
/*转化为CNF文件*/
void SetCNFfile(struct Qipan qipan[]);
