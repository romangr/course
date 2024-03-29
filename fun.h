#include <windows.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef vector<vector<vector<uchar> > > tdmatrix;
enum direction {BW,NEGATIVE};

//read BMP-file and create matrix of pixels
bool readBMP(tdmatrix &picture,BITMAPFILEHEADER &bfh, BITMAPINFOHEADER &bih,char *file) {
FILE * f;

uchar *buf=new uchar();

try {f=fopen(file,"r");} catch(int e)
{return false;}
fread(&bfh,sizeof(bfh),1,f);
fread(&bih,sizeof(bih),1,f);


if (bfh.bfOffBits!=54) {printf("%s\n", "File is not supported1"); return false;};

if (int(bfh.bfType)!=19778) {printf("%s\n", "File is not supported"); return false;};
int padding = bih.biWidth*(bih.biBitCount/8)%4;	//find number of last bits was added to picture to complete a row 

fseek(f,bfh.bfOffBits,SEEK_SET);	//go to begin of picture

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

bool applyFilter(tdmatrix &picture, direction key) {
int width=picture[0].size();
int height=picture.size();
int bytesOnPixel=picture[0][0].size();
int bytesForWork=bytesOnPixel;
int applyArea=int(min(width*key, height*key));


double red;
/*uchar green;
uchar blue;*/

if (bytesOnPixel==4) {bytesForWork=3;};

if (key==BW) {
		for (int i=0;i<height; i++) {
			for (int j = 0;j<width; j++)
			{
				for (int n = 0; n < bytesOnPixel; n++)
				{	
					switch (n) {
					case 0:red=picture[i][j][n]; break;
					case 1:red+=picture[i][j][n];  break;
					case 2:red+=picture[i][j][n];  break;
					}
				}
				red/=3;
				picture[i][j][0]=uchar(red);
				picture[i][j][1]=uchar(red);
				picture[i][j][2]=uchar(red);
				red=0;
			}
		}
}
else {
		for (int i=0;i<height; i++) {
			for (int j = 0;j<width; j++)
			{
				for (int n = 0; n < bytesOnPixel; n++)
				{	switch (n) {
					case 0:picture[i][j][n]=255-picture[i][j][n]; break;
					case 1:picture[i][j][n]=255-picture[i][j][n];   break;
					case 2:picture[i][j][n]=255-picture[i][j][n]; break;
					} 
				}
			}
		}
}

return true;
}

bool writeBMP(tdmatrix &picture,BITMAPFILEHEADER &bfh, BITMAPINFOHEADER &bih) {
FILE * f;
uchar *nullic=new uchar();
*nullic;
f=fopen("out.bmp","w");
fwrite(&bfh,sizeof(bfh),1,f);
fwrite(&bih,sizeof(bih),1,f);
int padding = bih.biWidth*(bih.biBitCount/8)%4;
uchar *buf=new uchar();
fseek(f,bfh.bfOffBits,SEEK_SET);
for (uint i=0; i<bih.biHeight; i++) {
	for (uint j=0; j<bih.biWidth; j++){
		for (uint k=0; k<(bih.biBitCount/8); k++) {
			*buf=picture[i][j][k];
			fwrite(buf,1,1,f);
		}
		//if (j==bih.biWidth-1) {fwrite(0,padding,1,f);};
	}
	fwrite(nullic,padding,1,f);
	//fseek(f,padding,SEEK_CUR);
}
delete(buf);
}

void help() {
	printf("\n%s\n\n", "filter <filename>.bmp [<type_of_filter>]");
	printf("%s\n", "types: BW - Black & white picrure");
	printf("%s\n", "negative - picrure with inverted colors");
}