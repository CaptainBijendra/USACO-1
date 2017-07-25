/*
ID: suzyzha1
PROG: heritage
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

string pre_order,in_order,post_order;

struct Node
{
	char c;
	Node *l,*r;
	Node()
	{
		l=r=NULL;
	}
} root;

void get_tree(Node *cur,int st1,int en1,int st2,int en2)
{
	cur->c=pre_order[st1];
	if(st2>=en2) return;

	int mid=in_order.find(cur->c);
	if(mid==std::string::npos) return;

	if(mid>st2)
	{
		cur->l=new Node();
		get_tree(cur->l,st1+1,st1+mid-st2,st2,mid-1);
	}
	if(mid<en2)
	{
		cur->r=new Node();
		get_tree(cur->r,st1+mid-st2+1,en1,mid+1,en2);
	}
}

void get_post(Node *cur)
{
	if(cur->l!=NULL) get_post(cur->l);
	if(cur->r!=NULL) get_post(cur->r);

	post_order+=cur->c;
}

int main()
{
	fstream fin("heritage.in",ios::in);
	fstream fout("heritage.out",ios::out);

	fin>>in_order>>pre_order;

	int n=in_order.length();

	get_tree(&root,0,n-1,0,n-1);

	get_post(&root);

	fout<<post_order<<endl;
	fin.close();
	fout.close();
	return 0;
}