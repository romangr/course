#include "fun.h"
using namespace std;
typedef unsigned int uint;

int main(int argc, char *argv[]) {
int inFile=0;
direction dir=BW;
if (argc==1) {help(); return 0;} else {
	for (int i=1; i<argc; i++) {
		if (strstr(argv[i],".bmp")) {
			inFile=i;
		}
		else {
			if (strstr(argv[i],"BW")) {dir=BW;}
			else { if (strstr(argv[i],"negative")) {dir=NEGATIVE;} }
		} 
	}
}

if (inFile==0) {help(); printf("%s\n", "Arguments are incorrect!"); return -1;}

BITMAPFILEHEADER bfh;
BITMAPINFOHEADER bih;	
tdmatrix *picture=new tdmatrix();

if(!readBMP(*picture,bfh,bih,argv[inFile])) {printf("%s\n", "Input error!"); return -1;}

applyFilter(*picture, dir);
writeBMP(*picture,bfh,bih);



return 0;
}