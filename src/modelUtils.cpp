#include "modelUtils.h"
#include "materials.h"
#include <codecvt>
#include <stdlib.h>

int getModelInfo(SUEntitiesRef entities){


	size_t instanceCount = 0;
  SUResult res =  SUEntitiesGetNumInstances(entities, &instanceCount);
  if (res != SU_ERROR_NONE)
    return 1;
	std::cout << "Num Instances are: " << instanceCount << "\n";


	size_t groupCount = 0;
	res =  SUEntitiesGetNumGroups(entities, &groupCount);
  if (res != SU_ERROR_NONE)
    return 1;
	std::cout << "Num Groups are: " << groupCount << "\n";
 

	size_t edgeCount = 0;
	res = SUEntitiesGetNumEdges(entities, true,	&edgeCount);
  if (res != SU_ERROR_NONE)
    return 1;
	std::cout << "Num Edges are: " << edgeCount << "\n";
	
	size_t guideCount = 0;
	res =  SUEntitiesGetNumGuidePoints(entities, &guideCount);
  if (res != SU_ERROR_NONE)
    return 1;
	std::cout << "Num guides are: " << guideCount << "\n";

	size_t curveCount = 0;
	res =  SUEntitiesGetNumCurves(entities, &curveCount);
  if (res != SU_ERROR_NONE)
    return 1;
	std::cout << "Num curves are: " << curveCount << "\n";
	
	size_t imCount = 0;
	res =  SUEntitiesGetNumImages(entities, &imCount);
  if (res != SU_ERROR_NONE)
    return 1;
	std::cout << "Num Images are: " << imCount << "\n";
	
	// Get all the faces from the entities object
  size_t faceCount = 0;
  res = SUEntitiesGetNumFaces(entities, &faceCount);
  if (res != SU_ERROR_NONE)
    return 1;
	std::cout << "Num Faces are: " << faceCount << "\n";

	return 0;	

}

string ws2s(const std::wstring& wstr)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

std::string CleanString(std::string s){
	string allow = "_|.-";
	bool keepFlag = false;
	if (s[0] == '[')
		s = s.substr(1,s.length()-1);

	for (int i=0; i<s.length(); i++){
		if (s[i] >= 'a' && s[i] <= 'z')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
			continue;
		if (s[i] >='0' && s[i] <= '9')
			continue;

		keepFlag = false;
		for (int j=0; j< allow.length(); j++){
			keepFlag = keepFlag || allow[j]==s[i];
		}
		if (!keepFlag)
			s[i] = '_';
	}
	return s;

}

std::string SUString2String(SUStringRef s){
	SUResult res;
	size_t len, wlen;
	std::string sss;
	res = SUStringGetUTF8Length(s, &len);
	ErrorHandler(res);
	res = SUStringGetUTF16Length(s, &wlen);
	ErrorHandler(res);

	if (len > 0){
		//unichar ss[len];
		//char    ch[500];
		char ss[len];
		unichar wss[wlen];
		SUStringGetUTF8(s, len, &ss[0], &len);
		SUStringGetUTF16(s, wlen, &wss[0], &wlen);

		//const wchar_t* wch = &ss[0];
		//wcstombs (ch, wch, sizeof(ch))	
		sss.assign(ss);
		sss = CleanString(sss);
	 	//std::cout << sss.c_str() << "\n";	
	}else{
		sss = "";
	}

		return sss;
}


int Instances2Entities(std::vector<SUComponentInstanceRef>* instances, std::vector<SUEntitiesRef>* entities){

	size_t instanceCount = instances->size();
	for (size_t i = 0; i < instanceCount; i++) {
		SUComponentInstanceRef instance = (*instances)[i];
		if (!SUIsInvalid(instance)) {
			 SUComponentDefinitionRef component_definition;
			 SUComponentInstanceGetDefinition((*instances)[i], &component_definition);
			 //entities[i] = SU_INVALID;
			 SUComponentDefinitionGetEntities(component_definition, &((*entities)[i]));
		}
	}
	return 0;
}


int Groups2Entities(std::vector<SUGroupRef>* groups, std::vector<SUEntitiesRef>* entities){
	
	size_t groupCount = groups->size();
	for (size_t i=0; i < groupCount; i++){
		SUGroupRef group = (*groups)[i];
		SUGroupGetEntities(group, &((*entities)[i]));
	}

	return 0;
}

template <typename Dtype>
void VecStore<Dtype>::add(Dtype elm){
	bool existFlag = false;
	for (int i=0; i<idx_; i++){
		if (x_[i] == elm)
			existFlag = true;	
	}

	if (!existFlag){
		x_.push_back(elm);
		idx_ += 1;
	}
	//assert(idx_ < maxSz_);
}

template <>
void VecStore<GeomUtils::CPoint3d>::add(SUVertexRef vertex){

	SUPoint3D position;
	SUVertexGetPosition(vertex, &position);

	GeomUtils::CPoint3d point(position);
	add(point);
}

template <>
void VecStore<GeomUtils::CVector3d>::add(SUVector3D vec){
	GeomUtils::CVector3d vect(vec);
	add(vect);
}

template <>
void VecStore<GeomUtils::CPoint3d>::add(SUPoint3D pt){
	GeomUtils::CPoint3d point(pt);
	add(point);
}


void ErrorHandler(SUResult res){
	if (res == SU_ERROR_NONE)
			return;

	std::cout << "ERROR DETECTED \n";
	switch (res){
		case SU_ERROR_NULL_POINTER_INPUT:
			std::cout << "SU_ERROR_NULL_POINTER_INPUT \n";
			break;
		case SU_ERROR_INVALID_INPUT:
			std::cout << "SU_ERROR_INVALID_INPUT \n";
			break;
		case SU_ERROR_NULL_POINTER_OUTPUT:
			std::cout << "Error: Null Pointer Output \n";
			break;
		case SU_ERROR_INVALID_OUTPUT:
			std::cout << "SU_ERROR_INVALID_OUTPUT \n";
			break;
		case SU_ERROR_OVERWRITE_VALID:
			std::cout << "SU_ERROR_OVERWRITE_VALID \n";
			break;
		case SU_ERROR_GENERIC:
			std::cout << "SU_ERROR_GENERIC \n";
			break;
		case SU_ERROR_SERIALIZATION:
			std::cout << "SU_ERROR_SERIALIZATION \n";
			break;
		case SU_ERROR_OUT_OF_RANGE:
			std::cout <<"SU_ERROR_OUT_OF_RANGE \n";
			break;
		case	SU_ERROR_NO_DATA:
		 	std::cout <<"SU_ERROR_NO_DATA \n";
			break;
		case SU_ERROR_INSUFFICIENT_SIZE:
			std::cout << "SU_ERROR_INSUFFICIENT_SIZE \n";
			break;
		case SU_ERROR_UNKNOWN_EXCEPTION:
			std::cout <<"SU_ERROR_UNKNOWN_EXCEPTION \n";		
			break;
		case SU_ERROR_MODEL_INVALID:
			std::cout <<"SU_ERROR_MODEL_INVALID \n";
			break;
		case SU_ERROR_MODEL_VERSION: 
			std::cout <<"SU_ERROR_MODEL_INVALID \n";
			break;
		default:
			std::cout << "Unlisted Error \n";
	}
	exit(EXIT_FAILURE);
}

size_t Face2NumVertices(SUFaceRef face){
	SUResult res;

	//Form the mesh
	SUMeshHelperRef mesh = SU_INVALID;
	res = SUMeshHelperCreate(&mesh, face);
	ErrorHandler(res);
	
	// Get number of vertices. 
	size_t num_vertices;
	res = SUMeshHelperGetNumVertices(mesh, &num_vertices);
	ErrorHandler(res);

	SUMeshHelperRelease(&mesh);
	
	return num_vertices;
}



bool IsFaceFrontTexture(SUFaceRef face){
	bool out;
	SUResult res;
	SUMaterialRef material = SU_INVALID;
	res = SUFaceGetFrontMaterial(face, &material);

	if (res == SU_ERROR_NONE)
		out = true;
	if (res == SU_ERROR_NULL_POINTER_OUTPUT)
		out = false;

	SUMaterialRelease(&material);
	return out;

}


bool IsFaceBackTexture(SUFaceRef face){
	bool out;
	SUResult res;
	SUMaterialRef material = SU_INVALID;
	res = SUFaceGetBackMaterial(face, &material);

	if (res == SU_ERROR_NONE)
		out = true;
	if (res == SU_ERROR_NULL_POINTER_OUTPUT)
		out = false;

	SUMaterialRelease(&material);
	return out;
}


std::string StringReplace(std::string in, std::string find, std::string replace) {
    while(true) {
        size_t pos = in.find(find);
        if(pos == -1)
            break;
        
        in = in.substr(0,pos) + replace + in.substr(pos+find.length());
    }
    return in;
}

std::string GetMaterialName(SUMaterialRef material){
	SUResult res;
	std::string sName = "";

	SUStringRef name = SU_INVALID;
	res = SUStringCreate(&name);
	ErrorHandler(res);

	res = SUMaterialGetName(material, &name);
	ErrorHandler(res);
	
	size_t len;
	res = SUStringGetUTF8Length(name, &len);
	ErrorHandler(res);

	if (len > 0){
		sName = SUString2String(name);
		sName = StringReplace(sName, "*", "_"); 
	}
	
	res = SUStringRelease(&name);
	ErrorHandler(res);

	return sName;
}

void GetFaceFrontMaterial(SUFaceRef face){
	SUResult res;
	SUMaterialRef material = SU_INVALID;
	res = SUFaceGetFrontMaterial(face, &material);
	
	if (res == SU_ERROR_NONE){
	
		Material mat = Material(material);
		/*
		std::cout << GetMaterialName(material) <<  "\n";

		bool use_opacity;
		res = SUMaterialGetUseOpacity(material, &use_opacity);
		ErrorHandler(res);

		SUMaterialType type;
		res = SUMaterialGetType(material, &type);
		ErrorHandler(res);

		SUColor color;
		res = SUMaterialGetColor(material, &color);
		ErrorHandler(res);
		std::cout << (unsigned int)color.red << "\t" << (unsigned int)color.green << "\t" << (unsigned int)color.blue << "\n"; 
		*/
	}
}

