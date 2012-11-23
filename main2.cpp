#include <vector>
#include "bitmap.h"
//#include <windows.h>
#include <stdio.h>
using namespace std;
typedef unsigned int uint;

int main() {
FILE * f;
BITMAPFILEHEADER bfh;
BITMAPINFOHEADER bih;
int *a=new int();
int *c=new int();
short *b=new short();

f=fopen("in.bmp","r");
fread(a,1,1,f);
printf("%s",a);
fread(a,1,1,f);
printf("%s\n",a);


fread(c,4,1,f);
//printf("%d",c);

printf("%s","\n");
fseek(f,10,SEEK_SET);
fread(a,1,4,f);
printf("%o",a);
fclose(f);

 //bmp_in.read( (char*)&bfh, sizeof(bfh) );
 //bmp_in.read( (char*)&bih, sizeof(bih) );

/*if (bfh.bfType != 0x4D42) {return -1;}
if (bih.biBitCount!=24) {return -1;};*/

//int padding = ((24 / bih.biBitCount) * bih.biWidth) % 4;
//tdmatrix *picture = new tdmatrix();

//bmp_in.seekg(bfh.bfOffBits, ios::beg);

/*
for (uint i = 0; i < bih.biWidth; i++) {
	picture->push_back(vector<vector<char> >());
		for (uint j=0; j<bih.biHeight; j++) {
			picture->push_back(<vector<char>());
			for (uint k=0; k<3; k++) {
				bmp_in.read(picture->at(i).at(j).at(k), 1);
				//in.seekg(padding, ios::cur);
			}
	}
}*/


return 0;
}