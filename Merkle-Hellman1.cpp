#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<fstream>
#define LL long long
#define N 8
using namespace std;
bool is_prime(int n)
{
	int i=2;
	for(i=2;i*i<=n;i++)
	{
		if(n%i==0)
			return false;
	}
	return true;
}
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
LL pow_mod(LL a,LL b,LL p)
{
	LL res=1;
	while(b)
	{
		if(b&1)
			res=(res*a)%p;
		a=(a*a)%p;
		b=b>>1;
	}
	return res;
}
LL Fermat(LL a,LL p)
{
	return pow_mod(a,p-2,p);

}
int main()
{
	vector<int> privatekey;
	vector<int> publickey;
	int sum=0,a=1,modnumber,mulnumber,inversemul;
	for(int i=1;i<=N;i++)
	{
		privatekey.push_back(a);
		sum+=a;
		a=sum+1;
	}
	sum=a;
	srand(time(0));
	do
	{
		modnumber=rand()%500;
	}while(modnumber<=sum||!is_prime(modnumber));
	do
	{
		mulnumber=rand()%100;
	}while(gcd(modnumber,mulnumber)!=1);
	inversemul=Fermat(mulnumber,modnumber);
	ofstream fout("privatekey.txt");
	streambuf *coutbackup;
	coutbackup=cout.rdbuf(fout.rdbuf());
	for(int i=1;i<=N;i++)
	{
		cout<<privatekey[i-1]<<" ";
	}
	cout<<endl;
	//cout<<mulnumber<<endl;
	cout<<inversemul<<endl;
	cout<<modnumber<<endl;
	fout.close();
	fout.open("publickey.txt");
	//ofstream fout("publickey.txt");
	//streambuf *coutbackup;
	coutbackup=cout.rdbuf(fout.rdbuf());
	for(int i=1;i<=N;i++)
	{
		a=(mulnumber*privatekey[i-1])%modnumber;
		publickey.push_back(a);
		cout<<a<<" ";
	}
	cout<<endl;
	cout<<mulnumber;
	fout.close();
 }
