#include "objwriter.h"
#include "modelUtils.h"
#include <iomanip>

void ObjWriter::WriteHeader(){

	fid_ << "# OBJ Model File \n";
	fid_ << "# Exported using skp2obj (c) Pulkit Agrawal 2014 \n";
	fid_ << "# File Units Inches \n";

}

void ObjWriter::WriteModel(SkpModel* model){
	WriteVertices(model->GetVertices());
	WriteNormals(model->GetNormals());
	WriteFaces(model);
	WriteAllMaterials(model);
}

void ObjWriter::WriteVertices(VecStore<GeomUtils::CPoint3d>* verts){
	size_t len = verts->length();
	for (size_t i=0; i<len; i++){
		const GeomUtils::CPoint3d pt = verts->get(i);
		fid_ << "v\t" << pt.x() << "\t" << pt.y() << "\t" << pt.z() << "\n";
	}	

}

void ObjWriter::WriteNormals(VecStore<GeomUtils::CVector3d>* normals){
	size_t len = normals->length();
	for (size_t i=0; i<len; i++){
		const GeomUtils::CVector3d pt = normals->get(i);
		fid_ << "vn\t" << pt.x() << "\t" << pt.y() << "\t" << pt.z() << "\n";
	}	
}

void ObjWriter::WriteFaces(SkpModel* model){
	const std::vector<SUFaceRef>* faces = model->GetFaces();	
	for (size_t f=0; f < faces->size(); f ++){
		size_t num_vertices = Face2NumVertices((*faces)[f]);
		std::vector<size_t> vIdx(num_vertices);
		std::vector<size_t> nIdx(num_vertices);
		model->Face2AttributeIndices((*faces)[f], &vIdx, &nIdx);
		assert(vIdx.size() == num_vertices);
		fid_ << "f\t";
		for (size_t i=0; i<num_vertices; i++){
			assert(vIdx[i]>=0);
			assert(nIdx[i]>=0);
			fid_ << vIdx[i] + 1 << "//" << nIdx[i] + 1 << "\t";
		}
		fid_ <<"\n";
		//GetFaceFrontMaterial((*faces)[f]);
		model->AddFaceMaterial((*faces)[f]);
	}
}

void ObjWriter::WriteAllMaterials(SkpModel* model){
	const MaterialMap mmap = *(model->GetMaterialMap());
	for (auto& x: mmap)
		WriteMaterial(x.second);
}

void ObjWriter::WriteMaterial(Material mat){
	SUResult res;
	//fid_mtl_.precision(6);
	fid_mtl_ << "newmtl \t" << mat.GetName() << "\n";
	const Color Ka = mat.GetKa();
	const Color Kd = mat.GetKd();
	const Color Ks = mat.GetKs();
	fid_mtl_ << "Ka \t" << Ka.r() << "\t" << Ka.g() << "\t" << Ka.b() << "\n";
	fid_mtl_ << "Kd \t" << Kd.r() << "\t" << Kd.g() << "\t" << Kd.b() << "\n";
	fid_mtl_ << "Ks \t" << Ks.r() << "\t" << Ks.g() << "\t" << Ks.b() << "\n";

	const bool is_opacity = mat.GetIsOpacity();
	if (is_opacity){
		fid_mtl_ << "d \t" << mat.GetAlpha();
	}

	/*
	const SUMaterialType type = mat.GetType();
	if (type == SUMaterialType_Textured || type == SUMaterialType_ColorizedTexture){
		SUStringRef name = SU_INVALID;
		res = SUStringCreate(&name);
		ErrorHandler(res);
		
		SUTextureRef texture = mat.GetTexture();
		res = SUTextureGetFileName(texture, &name);
		ErrorHandler(res);
		string fileName =  SUString2String(name);	
		SUStringRelease(&name);
		assert(fileName != "");

		SUTextureWriteToFile(texture, fileName.c_str());
	}
	*/
	fid_mtl_ << "\n";
}
