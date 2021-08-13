
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<ctime>
std::string polynomial(int[],int);
int ndec(float *k);
int cmp(int);
using namespace std;
std::string to_string (int Number)
{
	stringstream ss; ss << Number;
	return ss.str();
}
int main()
{
	int a[256],n,k,nd,*dw[256],*cw[256],crc[9]={1,0,0,0,0,0,1,1,1},*syn[16];string s1;
	cout<<"Input:\n\n";
	cout<<"Enter the Number of Bits (Should be more than 32):";
	cin>>n;
	k=16-n%16;
	if(k==16)
	k=0;
	nd=(n+k)/16;
	for(int i=0;i<k;i++)
		a[i]=0;
	cout<<"Enter the datastream: ";
	for(int i=k;i<n+k;i++)
	cin>>a[i];
	cout<<"\nOutput:\n\n";
	cout<<"Data stream that was fed is given: ";
	for(int i=k;i<n+k;i++)
		cout<<a[i]<<" ";
		cout<<"\n";
	cout<<"No of 16-bit data words can be formed is: "<<nd<<"\n                                       Table-1:\n";
	cout<<"+----+---------------------------------+-------------------------------------------------+-------------------------------------------------------------------+\n";
	cout<<"| S.n|           Dataword              |           CodeWord forms using crc-8            |   Polynomial form of Codeword                                     |\n";
	cout<<"+----+---------------------------------+-------------------------------------------------+-------------------------------------------------------------------+\n";
	for(int i=0;i<nd;i++)
	{
		dw[i]=new int[25];
		for(int j=0;j<16;j++)
		*(dw[i]+j)=a[16*i+j];
	}
	for(int i=0;i<nd;i++)
	{
		cout<<"| "<<i+1<<"  | ";
		cw[i]= new int[25];
		syn[i]=new int[10];
		for(int j=0;j<16;j++)
			cout<<*(dw[i]+j)<<" ";
			cout<<"| ";
		for(int j=0;j<16;j++)
			*(cw[i]+j)=*(dw[i]+j);
		for(int j=16;j<24;j++)
			*(dw[i]+j)=0;
		for(int j=0;j<16;j++)
		{
			if(*(dw[i]+j)==1)
			for(int u=j;u<j+9;u++)
				*(dw[i]+u)=(*(dw[i]+u))^crc[u-j];
		}
		for(int j=16;j<24;j++)
		{
			*(syn[i]+j-16)=*(dw[i]+j);
			*(cw[i]+j)=*(dw[i]+j);
		}
		for(int j=0;j<24;j++)
		cout<<*(cw[i]+j)<<" ";
		cout<<"| ";
		cout<<polynomial(cw[i],24);
		cout<<"|\n";
		cout<<"+----+---------------------------------+-------------------------------------------------+-------------------------------------------------------------------+\n";
	}
	cout<<"\nSending code word to reciever\n";float p,q;int t1,t2,r1,h,P[4],y,l;char c;string s="";
	cout<<"Enter the Number of hopes: ";
	cin>>h;
	if(h==1)
	{
		cout<<"Enter the probability for the hop to be fliped the bit: p=";
		cin>>p;
		cout<<"probality to not change the bit Will be:"<<1-p<<"\n";
		t1=ndec(&p);
	}
	else if(h==2)
	{
		cout<<"Enter the probability for the hop-1 to be fliped the bit: p=";
		cin>>p;
		cout<<"probality to be not changed the bit Will be:"<<1-p<<"\n";
		cout<<"Enter the probability for the hop-2 to be fliped the bit: p=";
		cin>>q;
		cout<<"probality to be not changed the bit Will be:"<<1-q<<"\n";
		t1=ndec(&p);
		t2=ndec(&q);
	}

	srand(time(0)*time(0));
	cout<<"\n                                         Table-2\n";
	cout<<"+----+-------------------------------------------------+-------------------------------------------------+---------------------------------+\n";
	cout<<"| S.n|        CodeWord at sender end                   |         codeword at reciever end                |           Dataword              |\n";
	cout<<"+----+-------------------------------------------------+-------------------------------------------------+---------------------------------+\n";
	for(int i=0;i<nd;i++)
	{
		cout<<"| "<<i+1<<"  | ";
		for(int j=0;j<24;j++)
		cout<<*(cw[i]+j)<<" ";
		cout<<"| ";
		for(int j=0;j<24;j++)
		if(rand()%t1<p)
			*(cw[i]+j)=cmp(*(cw[i]+j));
		if(h==2)
		for(int j=0;j<24;j++)
		if(rand()%t2<q)
			*(cw[i]+j)=cmp(*(cw[i]+j));
			for(int j=0;j<24;j++)
			cout<<*(cw[i]+j)<<" ";
			cout<<"| ";
		for(int j=0;j<16;j++)
		*(dw[i]+j)=*(cw[i]+j);
		for(int j=0;j<16;j++)
		{
			if(*(cw[i]+j)==1)
			for(int u=j;u<j+9;u++)
				*(cw[i]+u)=(*(cw[i]+u))^crc[u-j];
		}
		int sum=0;
		for(int j=16;j<24;j++)
		sum=sum+*(cw[i]+j);
		if(sum==0)
		{
			for(int j=0;j<16;j++)
			cout<<*(dw[i]+j)<<" ";
			cout<<"|\n";
	 	}
		else cout<<"           DISCARD              |\n";
	cout<<"+----+-------------------------------------------------+-------------------------------------------------+---------------------------------+\n";
	}
	cout<<"NOTE:- \'DISCARD\' will display if there is found errors in the recieved code. ";
}
std::string polynomial(int a[],int n)
{
	char c;
	string s="";
	for(int i=0;i<n;i++)
	{
		if(a[i]==1)
		{
			if(i!=n-1)
			s=s+"x^"+to_string(n-i-1)+"+";
			else s=s+"1+";
		}
	}
	return s.substr(0,s.length()-1);
}
int ndec(float *k)
{
	int n=1;
	while(*k-int(*k))
	{
		n=n*10;
		*k=(*k)*10;
	}
	return n;
}
int cmp(int k)
{
	if(k==0)
	return 1;
	else return 0;
}

