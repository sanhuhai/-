#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#define OVERFLOW -1
#define OK 1
#define ERROR 0

typedef char ElemType;
using namespace std;

typedef struct BiTNode {          //二叉树
	ElemType data;           //数据域,存储结点名称
	struct BiTNode* lchild, * rchild;   //左右孩子指针
}BiTNode, * BinTree;

typedef struct CSNode {           //孩子—兄弟二叉链表结构的树
	ElemType data;              //数据域,存储结点名称
	struct CSNode* firstchild, * nextsibling;  //孩子指针域和兄弟指针域
}CSNode, * CSTree;

BinTree creatbintree() {      //先序建立二叉树
	BinTree BT;
	ElemType ch;
	while ((ch = getchar()) == '\n');
	if (ch == '#')
		BT = NULL;
	else {
		BT = (BiTNode*)malloc(sizeof(BiTNode));
		if (!BT)
			exit(OVERFLOW);
		BT->data = ch;
		BT->lchild = creatbintree();
		BT->rchild = creatbintree();
	}
	return BT;
}

void CreateCSTree(CSTree& CT) { 	  // 建立孩子—兄弟二叉链表结构的树
	char c[20];           // 临时存放孩子结点(设不超过20个)的值
	CSTree p, p1;
	queue<CSTree> q;
	int i, l;
	cout << "请输入根结点: ";
	scanf("%c%*c", &c[0]);      //%*c吃掉回车键，不然直接跳出来执行下面的语句了
	if (c[0]) {   // 非空树
		CT = (CSTree)malloc(sizeof(CSNode)); // 建立根结点
		CT->data = c[0];
		CT->nextsibling = NULL;
		q.push(CT); // 入队根结点的指针
		while (!q.empty()) {    // 队不空
			p = q.front();
			q.pop(); // 出队一个结点的指针
			cout << "请按长幼顺序输入结点" << p->data << "的所有孩子(无孩子请直接按回车键): ";
			scanf("%s", c);   //从键盘接收一个字符放入数组，以回车结束
			l = strlen(c);
			if (l > 0) {    // 有孩子
				p1 = p->firstchild = (CSTree)malloc(sizeof(CSNode)); // 建立长子结点
				p1->data = c[0];
				for (i = 1; i < l; i++) {
					p1->nextsibling = (CSTree)malloc(sizeof(CSNode)); // 建立下一个兄弟结点
					q.push(p1); // 入队上一个结点
					p1 = p1->nextsibling;
					p1->data = c[i];
				}
				p1->nextsibling = NULL;
				q.push(p1); // 入队最后一个结点
			}
			else
				p->firstchild = NULL; // 长子指针为空
		}
	}
	else
		CT = NULL; // 空树
}

int ExchangeToBiTree(CSTree& CT, BinTree& BT) {      //将一棵用二叉链表表示的普通树转换为二叉树
	if (!CT) {
		BT = NULL;
	}
	else {
		if (!(BT = (BiTNode*)malloc(sizeof(BiTNode)))) {
			exit(OVERFLOW);
		}
		BT->data = CT->data;
		ExchangeToBiTree(CT->firstchild, BT->lchild);
		ExchangeToBiTree(CT->nextsibling, BT->rchild);
	}
	return OK;
}

void PreorderTraversal(BinTree BT) {        //先序递归遍历二叉树
	if (BT) {
		cout << BT->data << " ";
		PreorderTraversal(BT->lchild);
		PreorderTraversal(BT->rchild);
	}
}

void PreOrder(CSTree CT) {       //先序递归遍历孩子—兄弟二叉链表结构的树CT
	if (CT) {
		cout << CT->data << " ";
		PreOrder(CT->firstchild);
		PreOrder(CT->nextsibling);
	}
}

void InorderTraversal(BinTree BT) {      //中序递归遍历二叉树
	if (BT) {
		InorderTraversal(BT->lchild);
		cout << BT->data << " ";
		InorderTraversal(BT->rchild);
	}
}

void PostorderTraversal(BinTree BT) {    //后序递归遍历二叉树
	if (BT) {
		PostorderTraversal(BT->lchild);
		PostorderTraversal(BT->rchild);
		cout << BT->data << " ";
	}
}

void PostOrderTraverse(CSTree CT) {      // 后序递归遍历孩子—兄弟二叉链表结构的树CT
	CSTree p;
	if (CT) {
		if (CT->firstchild) {   // // 有长子
			PostOrderTraverse(CT->firstchild); // 后序遍历长子的子树
			p = CT->firstchild->nextsibling; // p指向长子的下一个兄弟
			while (p) {
				PostOrderTraverse(p); // 后序遍历下一个兄弟子树
				p = p->nextsibling; // p指向再下一个兄弟
			}
		}
		cout << CT->data << " ";// 最后访问根结点
	}
}

void LevelorderTraversal(BinTree BT) {     //层序遍历二叉树
	BinTree Q[100];
	BinTree p;
	int front = -1;
	int rear = -1;
	if (!BT)
		return;
	if (BT) {
		Q[++rear] = BT;
		while (front != rear) {
			p = Q[++front];     //赋值问题
			cout << p->data << " ";
			if (p->lchild)
				Q[++rear] = p->lchild;
			if (p->rchild)
				Q[++rear] = p->rchild;
		}
	}
}

void LevelOrderTraverse(CSTree CT) { // 层序遍历孩子—兄弟二叉链表结构的树CT
	CSTree p;
	queue<CSTree> q;
	if (CT) {
		cout << CT->data << " "; // 先访问根结点
		q.push(CT); // 入队根结点的指针
		while (!q.empty()) {    // 队不空
			p = q.front();    //获取队头元素
			q.pop(); // 出队一个结点的指针
			if (p->firstchild) {  // 有长子
				p = p->firstchild;
				cout << p->data << " "; // 访问长子结点
				q.push(p); // 入队长子结点的指针
				while (p->nextsibling) {// 有下一个兄弟
					p = p->nextsibling;
					cout << p->data << " "; // 访问下一个兄弟
					q.push(p); // 入队兄弟结点的指针
				}
			}
		}
	}
}

void preOrder1(BinTree BT) {    //非递归先序遍历二叉树
	stack<BinTree> s;
	BinTree p = BT;
	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			cout << p->data << " ";
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty()) {
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}

void preOrder2(CSTree CT) {    //先序非递归遍历孩子—兄弟二叉链表结构的树CT
	stack<CSTree> s;
	CSTree p = CT;
	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			cout << p->data << " ";
			s.push(p);
			p = p->firstchild;
		}
		if (!s.empty()) {
			p = s.top();
			s.pop();
			p = p->nextsibling;
		}
	}
}

void inOrder1(BinTree BT) {    //非递归中序遍历二叉树
	stack<BinTree> s;
	BinTree p = BT;
	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty()) {
			p = s.top();
			cout << p->data << " ";
			s.pop();
			p = p->rchild;
		}
	}
}

void postOrder1(BinTree BT) {   //非递归后序遍历二叉树
	stack<BinTree> s;
	BinTree cur;                      //当前结点
	BinTree pre = NULL;                 //前一次访问的结点
	s.push(BT);
	while (!s.empty()) {
		cur = s.top();
		if ((cur->lchild == NULL && cur->rchild == NULL) ||
			(pre != NULL && (pre == cur->lchild || pre == cur->rchild))) {
			cout << cur->data << " ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过
			s.pop();
			pre = cur;
		}
		else {
			if (cur->rchild != NULL)
				s.push(cur->rchild);
			if (cur->lchild != NULL)
				s.push(cur->lchild);
		}
	}
}

void  postOrder2(CSTree CT) {       //后序非递归遍历孩子—兄弟二叉链表结构的树CT
	stack<CSTree> s;
	while (CT || !s.empty()) {
		while (CT) {
			s.push(CT);
			CT = CT->firstchild;
		}
		CT = s.top(); s.pop();//STL要求这样做的
		cout << CT->data << " ";
		CT = CT->nextsibling;//CT可以为空的
	}
}

void destoryBinTree(BinTree BT) {        //销毁二叉树
	if (!BT)
		return;
	if (BT->lchild)
		destoryBinTree(BT->lchild);//销毁左子树
	if (BT->rchild)
		destoryBinTree(BT->rchild);//销毁右子树
	free(BT);//释放当前结点
}

void clock_delay() {       //时间延时函数
	clock_t tm;
	tm = clock();
	while (clock() < tm + 1000);
}

void menu() {
	char ch;
	cout << endl << endl << endl << "                                                心 中 有 树" << endl << endl;
	cout << "                                      *********************************" << endl << endl;
	cout << "                                                 1.二叉树" << endl << endl;
	cout << "                                                 2.普通树" << endl << endl;
	cout << "                                                 3.退出系统" << endl << endl;
	cout << "                                      *********************************" << endl << endl;
}

int main() {
	system("color b0");
	while (1) {
		system("cls");
		menu();
		cout << "请选择对应菜单项(1-3):";
		int cho;
		cin >> cho;
		switch (cho) {
		case 1: {
			system("cls");
			system("color b0");
			cin.clear();
			cin.sync();
			cout << "请按照先序建立二叉树，以#为空:" << endl;
			BinTree BT = creatbintree();
			cout << "先序遍历结果:"; PreorderTraversal(BT); cout << endl;
			cout << "中序遍历结果:"; InorderTraversal(BT);   cout << endl;
			cout << "后序遍历结果:"; PostorderTraversal(BT); cout << endl;
			cout << "层序遍历结果:"; LevelorderTraversal(BT); cout << endl;
			cout << "先序非递归:"; preOrder1(BT); cout << endl;
			cout << "中序非递归:";  inOrder1(BT); cout << endl;
			cout << "后序非递归:";  postOrder1(BT); cout << endl;
			cout << "正在销毁二叉树...";  destoryBinTree(BT); cout << endl;
			clock_delay();
			cout << "销毁完成！" << endl << endl;
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			system("color b0");
			cin.clear();
			cin.sync();
			CSTree CT;
			BinTree BT;
			CreateCSTree(CT);
			cout << endl << "前序遍历结果:"; PreOrder(CT);   cout << endl;
			cout << "前序非递归遍历结果:"; preOrder2(CT);   cout << endl;
			cout << "后序遍历结果:"; PostOrderTraverse(CT);   cout << endl;
			cout << "后序非递归遍历结果:"; postOrder2(CT);   cout << endl;
			cout << "层次遍历结果:"; LevelOrderTraverse(CT);  cout << endl << endl;
			cout << "正在将输入的树转换为其对应的二叉树..." << endl;
			clock_delay();
			ExchangeToBiTree(CT, BT);
			cout << "转换操作执行完毕!" << endl;
			cout << "转换后的二叉树的先序遍历结果:"; PreorderTraversal(BT); cout << endl;
			cout << "转换后的二叉树的中序遍历结果:"; InorderTraversal(BT);   cout << endl << endl;
			cout << "由此可见，树的前序遍历对应二叉树的前序遍历，树的后序遍历对应二叉树的中序遍历!" << endl << endl;
			system("pause");
			break;
		}
		case 3: {
			cout << "正在退出系统...";
			clock_delay();
			return 0;
		}
		default:return 0;
		}
	}
	return 0;
}