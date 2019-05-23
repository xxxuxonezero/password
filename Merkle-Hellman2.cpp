#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<stack>
#include<fstream>
#define LL long long
#define N 8
using namespace std;
vector<int> publickey;
vector<int> privatekey;
int inversemul,modnumber,mulnumber;
int toSecretWord(int a)
{
	int n=publickey.size()-1,sum=0;
	while(a)
	{
		bool b=a&1;
		sum+=b*publickey[n-1];
		--n;
		a>>=1;
	}
	return sum;
}
char encode(int secretWord)
{
	int cw = (inversemul*secretWord)%modnumber,sum=0,n=privatekey.size();
	stack<bool> bit_b;
	while(cw&&--n)
	{
		if(cw>=privatekey[n])
		{
			bit_b.push(1);
			cw-=privatekey[n];
		}
		else
		{
			bit_b.push(0);
		}
	}
	while(!bit_b.empty())
	{
		sum=sum*2+bit_b.top();
		bit_b.pop();
	}
	return sum;
}

int main()
{
	vector<char> clearWord;
	vector<int> secretWord;
	char a[200];
	int b;
	cout<<"所要加密的明文为："; 
	gets(a);
	for(int i=0;i<strlen(a);i++)
	{
		clearWord.push_back(a[i]);
	} 
	ifstream fin("publickey.txt");
	streambuf *cinbackup;
	cinbackup=cin.rdbuf(fin.rdbuf());
	cout<<"生成的公钥序列为：";
	while(cin>>b)
	{
		publickey.push_back(b);
	}
	modnumber=publickey[publickey.size()-1];
	for(int i=0;i<publickey.size()-1;i++) 
	{
		cout<<publickey[i]<<" "; 
	}
	cout<<endl;
	cout<<"模数为："<< modnumber;
	cout<<endl;
	cout<<"生成的密文为：";
	for(int i=0;i<clearWord.size();i++)	
	{
		secretWord.push_back(toSecretWord(clearWord[i]));
		cout<<secretWord[i]<<" ";
	}
	fin.close();
	fin.open("privatekey.txt");
	cinbackup=cin.rdbuf(fin.rdbuf());
	for(int i=0;i<publickey.size()-1;i++)
	{
		cin>>b;
		privatekey.push_back(b);
	}
	cin>>b;inversemul=b;
	cin>>b;modnumber=b; 
	cout<<endl;
	cout<<"解密得到的明文为："; 
	for(int i=0;i<secretWord.size();i++)
	{
		cout<<encode(secretWord[i]);
	}
	
}
