#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void GetSblock(int i,int j,unsigned char key[],unsigned char s[]);
char PRG(int i,int j,unsigned char s[]);
void encrypt(int i,int j,unsigned char s[]);
void decrypt(int i,int j,unsigned char s[]);

int main() 
{
	unsigned char key[] = "decrypt";
	unsigned char s[256];
	int i;
	int j;
	encrypt(i,j,s);
	decrypt(i,j,s);
}

void encrypt(int i,int j,unsigned char s[])
{
	ifstream InFile;
	ofstream OutFile;
	InFile.open("InFile.txt", ios::binary);
	OutFile.open("OutFile.txt",ios::trunc);
	OutFile.close();
	OutFile.open("OutFile.txt",ios::binary);
	while(!InFile.eof())
	{
		unsigned char symbol  = InFile.get();
		if (InFile.eof()) break;
		OutFile.put(symbol^PRG(i,j,s));
	}
	InFile.close();
	OutFile.close();
	i=j=0;
}

void decrypt(int i,int j,unsigned char s[])
{
	ifstream OutFile;
	ofstream DeFile;
	OutFile.open("OutFile.txt", ios::binary);
	DeFile.open("DeFile.txt",ios::trunc);
	DeFile.close();
	DeFile.open("DeFile.txt",ios::binary);
	while(!OutFile.eof())
	{
		unsigned char symbol  = OutFile.get();
		if (OutFile.eof()) break;
		DeFile.put(symbol^PRG(i,j,s));
	}
	OutFile.close();
	DeFile.close();
	i =j=0;
}

void GetSblock(int i, int j,unsigned char key[],unsigned char s[])
{
	for (i = 0;i < 256;i++) s[i] = i;
	j = 0;
	for (i = 0; i < 256;i++)
	{
		j = (j+s[i]+key[i % sizeof(key)]) % 256;
		unsigned char buffer = s[i];
		s[i] = s[j];
		s[j] = buffer;
	}
	i = j = 0;
}

char PRG(int i,int j,unsigned char s[])
{
	i = (i + 1) %256;
	j = (j+ s[i])%256;
	unsigned char buffer = s[i];
	s[i] = s[j];
	s[j] = buffer;
	unsigned char k = s[(s[i]+s[j])%256];
	return k;
}
