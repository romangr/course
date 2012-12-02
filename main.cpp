#include "fun.h"
using namespace std;
typedef unsigned int uint;

int main() {
BITMAPFILEHEADER bfh;
BITMAPINFOHEADER bih;	
tdmatrix *picture=new tdmatrix();
readBMP(*picture,bfh,bih);
applyFilter(*picture, 0.2);
writeBMP(*picture,bfh,bih);

return 0;
}