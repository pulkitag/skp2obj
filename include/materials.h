#ifndef SKP2OBJ_MATERIALS_H
#define SKP2OBJ_MATERIALS_H
#include "modelUtils.h"

using namespace std;
class Color{
	public:
		Color(): r_(0.0), g_(0.0), b_(0.0) {};
		Color(double r, double g, double b): r_(r), g_(g), b_(b) {};
		Color(SUColor col){
			r_ = ((double)(unsigned int)col.red)/255.0;
			g_ = ((double)(unsigned int)col.green)/255.0;
			b_ = ((double)(unsigned int)col.blue)/255.0;
		}

		virtual ~Color() {};
		double r() const {return r_;}
		double g() const {return g_;}
	  double b() const {return b_;}	

	private:
		double r_, g_, b_;
};

class Texture{
	public:
		Texture(){};
		Texture(SUTextureRef texture);
		~Texture(){if (imsize_> 0) delete data_;}

		size_t width() const  {return width_;}
		size_t height()const  {return height_;}
		size_t bits_per_pixel() const {return bits_per_pixel_;}
		size_t imsize() const {return imsize_;}
		string name()   const {return name_;}
		SUByte* data()  const {return data_;}
	
		void add_imdata(SUTextureRef texture);	

	private:
		size_t width_, height_;
		size_t bits_per_pixel_ = 0;
		size_t imsize_= 0;
		SUByte* data_;
		string name_;
};

class Material{
	public:
		Material(){
			name_ = "";
		}

		Material(SUMaterialRef material);
		~Material() { 
			if(is_kdmap_ && texture_ != NULL){ 
				std::cout << "Calling MAterial Destructor \n";
				delete texture_;
			}
		}

		//Set Functions. 
		void SetKa(SUColor col){ka_ = Color(col);}
		void SetKd(SUColor col){kd_ = Color(col);}
		void SetKs(SUColor col){ks_ = Color(col);}
		void SetName(string name){name_ = name;}
		void SetAlpha(double alpha) {alpha_ = alpha;}
		void SetIsOpacity(bool is_opacity) {is_opacity_ = is_opacity;}
		void SetType(SUMaterialType type) {type_ = type;}
		//void SetTexture(SUTextureRef& texture) {texture_ = texture;}

		//Get Functions. 
	  string GetName() {return name_;}
		bool   GetIsOpacity() {return is_opacity_;}
		const double GetAlpha() {return alpha_;}
		const Color  GetKa() {return ka_;}	
		const Color  GetKd() {return kd_;}
		const Color  GetKs() {return ks_;}
		const SUMaterialType  GetType() {return type_;}
		const Texture* GetTexture() {return texture_;}

	private:
		Color ka_ = Color(0.0, 0.0, 0.0); 
		Color kd_ = Color(0.0, 0.0, 0.0);
		Color ks_ = Color(0.33,0.33,0.33);
		string name_;
		bool is_kdmap_   = false;
		bool is_opacity_ = false;
		double alpha_ = 1.0;
		SUMaterialType type_;
		Texture* texture_;

};

typedef std::unordered_map<std::string, Material*> MaterialMap;
#endif //SKP2OBJ_MATERIALS_H
