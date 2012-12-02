#include <windows.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef vector<vector<vector<uchar> > > tdmatrix;

//read BMP-file and create matrix of pixels
bool readBMP(tdmatrix &picture,BITMAPFILEHEADER &bfh, BITMAPINFOHEADER &bih) {
FILE * f;

uchar *buf=new uchar();

f=fopen("in.bmp","r");
fread(&bfh,14,1,f);
fread(&bih,40,1,f);

int padding = bih.biHeight*(bih.biBitCount/8)%4;	//find number of last bits was added to picture to complete a row 

fseek(f,54,SEEK_SET);	//go to begin of picture

for (uint i = 0; i < bih.biHeight; i++) {
	picture.push_back(vector<vector<uchar> >());
		for (uint j=0; j<bih.biWidth; j++) {
			picture.at(i).push_back(vector<uchar>());
			for (uint k=0; k<(bih.biBitCount/8); k++) {
				fread(buf, 1,1,f);
				picture.at(i).at(j).push_back(*buf);
			}
		}
	fseek(f,padding,SEEK_CUR);
}
delete(buf);
fclose(f);

return true;
}

bool applyFilter(tdmatrix &picture, int key) {
int width=picture[0].size();
int height=picture.size();
int bytesOnPixel=picture[0][0].size();

int applyArea=int(min(width*key, height*key));

//left side of picture
for (int i=0;i<height; i++) {
	for (int j = 0;j<10; j++)
	{
		for (int n = 0; n < bytesOnPixel; n++)
		{	picture[i][j][n]*=0.4;
			/*if (j<height/2) {
				picture[j][i][n]*=char((j/applyArea)/i); }
			else {
				picture[j][i][n]*=char((applyArea/j)/i);
			}*/
		}
	}
}

return true;
}

bool writeBMP(tdmatrix &picture,BITMAPFILEHEADER &bfh, BITMAPINFOHEADER &bih) {
FILE * f;
f=fopen("out.bmp","w");
fwrite(&bfh,14,1,f);
fwrite(&bih,40,1,f);
int padding = bih.biHeight*(bih.biBitCount/8)%4;
uchar *buf=new uchar();

for (uint i=0; i<bih.biHeight; i++) {
	for (uint j=0; j<bih.biWidth; j++){
		for (uint k=0; k<(bih.biBitCount/8); k++) {
			*buf=picture[i][j][k];
			fwrite(buf,1,1,f);
		}
		if (j==bih.biWidth-1) {fwrite(0,1,padding,f);};
	}
}
delete(buf);
}