#include <iostream>
#include <fstream>
// #include <ctime> if you can rand sequency
#include <cmath>
#include <cstdlib>
int randSequency(int sumPrev);
int getNum(char *tmp,int razr);
void encrypt(int publickey[7]);
void decrypt(int sequency[7],int p,int q);
int convertToBinary(char symbol,int publicKey[7]); //
int convertFromBinary(int mas[7]);
int modInverse(int p,int q);
int getPublicKey(int publicKey[7],int sequency[7],int q,int p);
int main(int argc, char** argv) 
{
	
	int q,p;	
//	std::srand(std::time(0)); // rand sequency
	int sequency[7]={2,7,11,21,42,89,180};
	int publicKey[7]; 
	int sumPrev=352;

	std::cout<<"Please Enter q>"<<sumPrev<<": ";
	std::cin>>q;	
	std::cout<<"Please Enter 1<p<"<<q<<": ";
	std::cin>>p;
	if(q<sumPrev || p>q || p<1 || p==1 || p==q||q==sumPrev)
	{
		std::cout<<"Error count Q or P";
		return 0;
	}
	std::cout<<"Count True";
	std::cout<<"\n"; 
	for(int i=0;i<7;i++)
	{
		std::cout <<sequency[i]<<" ";
	}
	getPublicKey(publicKey,sequency,q,p);
	std::cout<<"\n"; 
	for(int i=0;i<7;i++)
	{
		std::cout<<publicKey[i]<<" ";
	}
	encrypt(publicKey);
	decrypt(sequency,p, q);
	return 0;
}
//int randSequency(int sumPrev) //Выдает рандомную последовательность
//{ 
//	int randNum;
//	do
//	{
//		randNum = sumPrev+std::rand()%10;
//	}
//	while(randNum < sumPrev);
//	return randNum;
//}
void encrypt(int publicKey[7])
{
	std::ifstream InFile;
	InFile.open("InFile.txt");
	std::ofstream OutFile;
	OutFile.open("OutFile.txt",std::ios::trunc);
	char symbol;	
	while(!InFile.eof())
	{
		symbol = InFile.get();
		if(InFile.eof())break;
		int num = convertToBinary(symbol,publicKey);
		OutFile<<num<<" ";
	}
}
void decrypt(int sequency[7],int p, int q)
{
	std::ifstream OutFile;
	std::ofstream DeFile;
	OutFile.open("OutFile.txt");
	DeFile.open("DeFile.txt",std::ios::trunc);
	char readSymbol;
	std::string str;	
	while(!OutFile.eof())
	{
		OutFile.get(readSymbol);
		if(OutFile.eof())
		{
			break;
		}
		if(readSymbol == ' ')
		{
		 	int num = atoi(str.c_str());
		 	int bit[7]= {0};
			int a = modInverse(p,q);
			a = num * a % q;
			int i =7;
			while(a!=0)
			{
				if(i<0) break;
				while(i>=0)
				{
					int count = a;
					a = a - sequency[i];
					if(a>0)
					{
						bit[i] = 1;
						i--;
					}
			
					if(a<0)
					{
						a = count;
						bit[i] = 0;
						i--;
					}
					if(a==0)
					{
						bit[i]=1;
						break;
					}
				}
			}
			for(int i=0;i<3;i++)
			{ 	
				int buf = bit[i];
				bit[i] = bit[6-i];
				bit[6-i] = buf;
			}
			char convertSymbol = convertFromBinary(bit);
			DeFile.put(convertSymbol);
		 	str.clear();
		}
		else str += readSymbol;
	}
}
int getPublicKey(int publicKey[7],int sequency[7],int q,int p) //Создает публичный ключ 
{
	for(int i=0;i<7;i++)
	{
		publicKey[i] = sequency[i]*p%q;
	}
	return publicKey[7];
}
int modInverse(int p,int q) //Находит обратное
{
	int t =0;
	int newT=1;
	int r = q;
	int newR = p;
	while( newR !=0)
	{
		int a = r / newR;
		int nnT = t - a * newT;
		t = newT;
		newT = nnT;
		int nnR = r - a*newR;
		r = newR;
		newR = nnR; 
	}
	if (r>1) std::cout<<"No solution";
	if (t<0) t += q;
	return t;
}
int convertToBinary(char symbol,int publicKey[7]) // Переводит текст в двоичный код
{
	int mas[7] = {0};
	int n= 0;
	int count = 0;
	int num = symbol;
	while(num!=0)
	{
		if(num%2==0) mas[n]=0;
		else mas[n]=1;
		num = num/2;
		n++;
	}
	for(int i=0;i<3;i++)
	{ 	
		int buf = mas[i];
		mas[i] = mas[6-i];
		mas[6-i] = buf;
	}
	for (int i=0;i<7;i++)
	{
		 count = count + mas[i] * publicKey[i];
	}
	return count;
}
int convertFromBinary(int mas[7]) // Переводит из двоичного кода и возвращает символ
{	
	char sim = 0;
	int b;
	for(int i=0;i<7;i++)
	{
		b = std::pow(2,i);
		sim = sim + (mas[i]*b);
	}
	return sim;
}
