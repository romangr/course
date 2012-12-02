#include "fun.h"
using namespace std;
typedef unsigned int uint;

int main() {
BITMAPFILEHEADER bfh;
BITMAPINFOHEADER bih;	
tdmatrix *picture=new tdmatrix();
if (readBMP(*picture,bfh,bih)) {
	applyFilter(*picture, 0.2);
	writeBMP(*picture,bfh,bih);} 
else {	printf("%s\n", "File is not supported!");
		return -1;}


return 0;
}