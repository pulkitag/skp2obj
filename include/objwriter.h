#ifndef SKP2OBJ_OBJWRITER_H
#define SKP2OBJ_OBJWRITER_H

#include "modelUtils.h"
#include "skpmodel.h"
#include "materials.h"
#include<fstream>

class ObjWriter {
	public:
		ObjWriter(){}
		virtual ~ObjWriter(){
			fid_.close();
			fid_mtl_.close();
		}

		ObjWriter(const char* fileName){
			fid_.open (fileName, std::ofstream::out);
		}

		ObjWriter(const char* fileName, const char* fileNameMtl){
			fid_.open (fileName, std::ofstream::out);
			fid_mtl_.open(fileNameMtl, std::ofstream::out);
		 	fid_mtl_.setf(std::ios::fixed, std::ios::floatfield);
		}

		void WriteHeader();
		void WriteModel(SkpModel* model);
		void WriteFaces(SkpModel* model);
		void WriteVertices(VecStore<GeomUtils::CPoint3d>* verts);
		void WriteNormals (VecStore<GeomUtils::CVector3d>* normals);
		void WriteAllMaterials (SkpModel* model);
		void WriteMaterial (Material* mat);

	private:
		std::ofstream fid_;
		std::ofstream fid_mtl_;
		VecStore<int> a_;

};


#endif //SKP2OBJ_OBJWRITER_H
