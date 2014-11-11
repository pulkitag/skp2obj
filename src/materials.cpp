#include "materials.h"
#include "modelUtils.h"

using namespace std;
Texture::Texture(SUTextureRef texture){
	SUResult res;
	size_t imsize, bits_per_pixel;
	res = SUTextureGetImageDataSize(texture, &imsize, &bits_per_pixel);
	ErrorHandler(res);
	
	imsize_ = imsize;
	bits_per_pixel_ = bits_per_pixel;

	if (imsize>0){
		//Image dimensions
		size_t width, height;
	  double	s, t;
		res = SUTextureGetDimensions(texture, &width, &height, &s, &t);
		ErrorHandler(res);
		width_  = width;
		height_ = height;
		std::cout << imsize << "\t" << width_ << "\t" << height_ << "\n";
		}else{
		std::cout <<"Material Has No Image";
		//Do Nothing
	}

	//Texture Name
	SUStringRef file_name = SU_INVALID;
	res = SUStringCreate(&file_name);
	ErrorHandler(res);
	res = SUTextureGetFileName(texture, &file_name);
	ErrorHandler(res);
	name_ = 	SUString2String(file_name);
	std::cout << name_ << "\n";
	res = SUStringRelease(&file_name);
	ErrorHandler(res);
}

void Texture::add_imdata(SUTextureRef texture){
	SUResult res;	

	//Image Data
	data_ = new SUByte[imsize_];
	res = SUTextureGetImageData(texture, imsize_, data_);
	ErrorHandler(res);
}

Material::Material(SUMaterialRef material){
	SUResult res;

	//Mat name
	string name = GetMaterialName(material);
	SetName(name);
	if (name=="")
		return;
	//Opacity
	bool use_opacity;
	res = SUMaterialGetUseOpacity(material, &use_opacity);
	ErrorHandler(res);
	SetIsOpacity(use_opacity);
	if (use_opacity){
		double alpha;
		res = SUMaterialGetOpacity(material, &alpha);
		ErrorHandler(res);
		SetAlpha(alpha);
	}


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

	is_kdmap_ = false;
	SUTextureRef texture = SU_INVALID;
	res = SUMaterialGetTexture(material, &texture);
	switch (res){
		case SU_ERROR_NONE:
			{
				texture_ = new Texture(texture);
				if (texture_->imsize() > 0){
					is_kdmap_ = true;
					texture_->add_imdata(texture);
				}
				break;
			}
		case SU_ERROR_NO_DATA:
			{
			std::cout <<"No Texture \n";
			break;
			}
		default :
			ErrorHandler(res);
	}
	
}

