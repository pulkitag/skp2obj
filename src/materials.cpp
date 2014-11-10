#include "materials.h"
#include "modelUtils.h"

using namespace std;
Material::Material(SUMaterialRef material){
	SUResult res;

	//Mat name
	string name = GetMaterialName(material);
	SetName(name);

	//Opacity
	bool use_opacity;
	res = SUMaterialGetUseOpacity(material, &use_opacity);
	ErrorHandler(res);
	SetIsOpacity(use_opacity);

	//Material Type
	SUMaterialType type;
	res = SUMaterialGetType(material, &type);
	ErrorHandler(res);
	SetType(type);

	//Material Color
	SUColor color = SU_INVALID;
	res = SUMaterialGetColor(material, &color);
	ErrorHandler(res);
	SetKd(color);
	//std::cout << (unsigned int)color.red << "\t" << (unsigned int)color.green << "\t" << (unsigned int)color.blue << "\n";

	SUTextureRef texture = SU_INVALID;
	res = SUMaterialGetTexture(material, &texture);
	switch (res){
		case SU_ERROR_NONE:
			break;
			SetTexture(texture);
		case SU_ERROR_NO_DATA:
			break;
		default :
			ErrorHandler(res);
	}
}
