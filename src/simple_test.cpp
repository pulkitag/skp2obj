#include "modelUtils.h"
#include "materials.h"

int main(){

	SUColor color;
	color.red = 1;
	color.blue = 2;
	color.green = 3;

	Material mat = Material();
	mat.SetKa(color);
}
