#include <fstream>
//#include <wingdi.h>
#include <vector>
#include "bitmap.h"
//#include <windows.h>
//#include <stdio.h>
using namespace std;
typedef unsigned int uint;

int main() {
fstream bmp_in;
/*BITMAPFILEHEADER bfh;
BITMAPINFOHEADER bih;*/

bmp_in.open ("in.bmp", ios::in | ios::out | ios::binary);
bmp_in.close();
//ifstream bmp_in ("in.bmp", ios::in | ios::binary);

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