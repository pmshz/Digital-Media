
/*
Huffman树／Huffman编码
只写了核心的编码构造过程其他部分都写的比较初级
只有编码过程然后显示出来没有写解码过程
程序只支持一个不含空格换行的字符串，如：
BABACACADADABBCBABEBEDDABEEEBB
输出结果为：
A : 11
B : 10
C : 111
D : 110
E : 11


*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <queue>
using namespace std;
struct Huffman
{
	map<char,string> ma;
	struct node
	{
		node *pre;//父指针
		node *ch[2];//孩子指针
		int w;//当前节点是1是0
		int leaf;//当前节点是否为叶子节点
		int count;//计数
		char c;//如果是叶子节点的话记录节点对应的字符
		node(int a)
		{
			count=leaf=c=0;
			pre=ch[0]=ch[1]=NULL;//给父指针和孩子指针初始化为NULL
			w=a;
			
		}
	}*root;//整棵霍夫曼树的根结点


	int num=0;／//字符种类个数
	struct cc//用于排序合并的结构
	{
		int count;
		char c;
		node *rot;//该节点所代表的霍夫曼子树的根
		cc(){rot=NULL;c=0;}

		bool operator <(const cc& b)const//因为优先队列本身默认为按权值从大到小所以重载时反过来
		{
			if(count > b.count) return true;
			else return false;
		}
		bool operator >(const cc& b)const
		{
			if(count < b.count) return true;
			else return false;
		}
	}save[10005];

	void build(char s[])//构造huffman树
	{
		
		int len = strlen(s);
		sort(s,s+len);//排序机，包含在algorithm头文件中
		for(int i=0;i<len;i++)
		{
			if(i==0)
			{
				save[num].c=s[0];
				save[num].count=1;
				continue;
			}
			
			if(s[i]==s[i-1])
			{
				save[num].count++;
			}
			else
			{
				save[++num].c=s[i];
				save[num].count=1;
			}
		}
		num++;
		priority_queue<cc> q;//优先队列
		for(int i=0;i<num;i++) q.push(save[i]);
		/*
		for(int i=0;i<num;i++)
		{
			printf("%c :%d\n",save[i].c,save[i].count);
		}
		*/
		while(q.size()>1)
		{
			cc t1=q.top();
			q.pop();
			node *tmp = new node(1);
			if(t1.c!=0)
			{
				node *tt1 = new node(1);
				tt1->c = t1.c;
				tt1->leaf = 1;
				tt1->count = t1.count;
				t1.rot = tt1;

			} 
			tmp->ch[0] = t1.rot;
			t1.rot->pre = tmp;

			cc t2=q.top();
			q.pop();
			if(t2.c!=0)
			{
				node *tt2 = new node(0);
				tt2->c = t2.c;
				tt2->leaf = 1;
				tt2->count = t2.count;
				t2.rot = tt2;
			} 
			tmp->ch[1] = t2.rot;
			t2.rot->pre = tmp;

			cc t3;
			t3.count = t1.count + t2.count;
			tmp->count = t3.count;
			t3.rot = tmp;
			q.push(t3);
		}
		root = q.top().rot;
		string x;
		down(root,x);
	}



	void print(void)
	{
		 map<char,string>::iterator iter;

         for( iter=ma.begin(); iter!=ma.end(); iter++)
         {
         	 cout << iter->first << " : " << iter->second << endl;
         }
	}

	void down(node *p,string x)//递归构成编码
	{
		if(p != root) x.append(1,'0' + p->w);
		if(p->leaf == 1)
		{
			ma[p->c] = x;
		}

		if(p->ch[0] != NULL)
		{
			down(p->ch[0],x);
		}
		if(p->ch[1] != NULL)
		{
			down(p->ch[1],x);
		}
	}
};
int main()
{
	int n,m;
	char s[10005];
	scanf("%s",s);
	Huffman tree;
	tree.build(s);
	tree.print();
	return 0;
}
