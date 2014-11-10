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
		}

		ObjWriter(char* fileName){
			name_ = fileName;
			fid_.open (name_, std::ofstream::out);
		}

		void WriteHeader();
		void WriteModel(SkpModel* model);
		void WriteFaces(SkpModel* model);
		void WriteVertices(VecStore<GeomUtils::CPoint3d>* verts);
		void WriteNormals (VecStore<GeomUtils::CVector3d>* normals);
		void WriteMaterial (Material mat);

	private:
		char* name_;
		std::ofstream fid_;
		VecStore<int> a_;

};


#endif //SKP2OBJ_OBJWRITER_H
