#include<iostream>
#include<cstdlib>
#include<ctime>
int ndec(float *);
int cmp(int);
using namespace std;
int main()
{
	int a[32],n,k,nd,*dw[20],*cw[20];
	cout<<"Input:\n\n";
	cout<<"Enter the Number of Bits (Should be more than 16):";
	cin>>n;
	k=4-n%4;if(k==4)k=0;nd=(n+k)/4;
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
	cout<<"No of 4-bit data words can be formed is: "<<nd<<"\n                 Table-1:\n"; 
	cout<<"+----+----------+------------------------+\n";
	cout<<"| S.n| Dataword | CodeWord at sender End |\n";
	cout<<"+----+----------+------------------------+\n";
	for(int i=0;i<nd;i++)
	{
		dw[i]=new int[5];
		for(int j=0;j<4;j++)
		*(dw[i]+j)=a[4*i+j];
	}
	for(int i=0;i<nd;i++)
	{
		cout<<"| "<<i+1<<"  | ";
		cw[i]= new int[8];
		for(int j=0;j<4;j++)
			cout<<*(dw[i]+j)<<" ";
			cout<<" | ";
		for(int j=0;j<7;j++)
		{
			if(j<3)
			*(cw[i]+j)=*(dw[i]+j);
			else if(j==3)
			*(cw[i]+j)=(*(dw[i])+*(dw[i]+1)+*(dw[i]+2))%2;
			else if(j==4)
			*(cw[i]+j)=*(dw[i]+3);
			else if(j==5)
			*(cw[i]+j)=(*(dw[i])+*(dw[i]+1)+*(dw[i]+3))%2;
			else if(j==6)
			*(cw[i]+j)=(*(dw[i])+*(dw[i]+2)+*(dw[i]+3))%2;
			cout<<*(cw[i]+j)<<" ";
		}
		cout<<"         |\n";
		cout<<"+----+----------+------------------------+\n";
	}
	cout<<"\nNOTE: Codeword is in the form of- D7 D6 D5 P4 D3 P2 P1. Here D represents datawords and P parity.\n";
	cout<<"\nRandom Error Generation:\n";float p;int t,r1,P[4],y,l;char c;string s="";
	cout<<"Enter the chance(probability) to generate error: ";
	cin>>p;
	t=ndec(&p);
	srand(time(0)*time(0));
	cout<<"\n                                         Table-2\n";
	cout<<"+----+------------------------+--------------------------+----------+----------+--------------------+\n";
	cout<<"| S.n| CodeWord at sender End | codeword at reciever end |   EDP    |   ECP    | corrected codeword |\n";
	cout<<"+----+------------------------+--------------------------+----------+----------+--------------------+\n";
	for(int i=0;i<nd;i++)
	{
		s="  ";
		cout<<"| "<<i+1<<"  | ";
		for(int j=0;j<7;j++)
		cout<<*(cw[i]+j)<<" ";
		cout<<"         | ";
		if(rand()%t<p)
		{
			r1=rand()%6+1;
			*(cw[i]+r1)=cmp(*(cw[i]+r1));
		}
		for(int j=0;j<7;j++)
		cout<<*(cw[i]+j)<<" ";
		cout<<"           | ";
		P[4]=(*(cw[i]+0)+*(cw[i]+1)+*(cw[i]+2)+*(cw[i]+3))%2;
		P[2]=(*(cw[i]+0)+*(cw[i]+1)+*(cw[i]+4)+*(cw[i]+5))%2;
		P[1]=(*(cw[i]+0)+*(cw[i]+2)+*(cw[i]+4)+*(cw[i]+6))%2;
		for(int j=1;j<=4;j=j*2)
		{
			if(P[j]==1)
			{
				c=j+'0';
				s=s+c+", ";
			}
		}
		if(P[1]==0&&P[2]==0&&P[4]==0)
		cout<<"NO ERROR | ";
		else
		{
			s=s.substr(0,s.length()-2);
			cout<<s;
			l=1+s.length();
			for(int j=0;j<10-l;j++)
			cout<<" ";
			cout<<"| ";
		}
		y=4*P[4]+2*P[2]+P[1];
		if(y==0)
		cout<<"NO ERROR | ";
		else
		cout<<"   "<<y<<"     | ";
		if(y!=0)
		*(cw[i]+7-y)=cmp(*(cw[i]+7-y));
		for(int j=0;j<7;j++)
		cout<<*(cw[i]+j)<<" ";
		cout<<"     |\n";
		cout<<"+----+------------------------+--------------------------+----------+----------+--------------------+\n";
	}
	cout<<"NOTE: EDP stands for position(s) of Error detection and ECP for Error correction. ";
	cout<<"Positions are consiedered from the lsb.";
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
