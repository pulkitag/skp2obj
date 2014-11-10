#include "objwriter.h"
#include "modelUtils.h"

void ObjWriter::WriteHeader(){

	fid_ << "# OBJ Model File \n";
	fid_ << "# Exported using skp2obj (c) Pulkit Agrawal 2014 \n";
	fid_ << "# File Units Inches \n";

}

void ObjWriter::WriteModel(SkpModel* model){
	WriteVertices(model->GetVertices());
	WriteNormals(model->GetNormals());
	WriteFaces(model);
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
		GetFaceFrontMaterial((*faces)[f]);
	}
}

void ObjWriter::WriteMaterial(Material mat){

	fid_ << "newmtl \t" << mat.GetName() << "\n";
	const Color Ka = mat.GetKa();
	const Color Kd = mat.GetKd();
	const Color Ks = mat.GetKs();
	fid_ << "Ka \t" << Ka.r() << "\t" << Ka.g() << "\t" << Ka.b() << "\n";
	fid_ << "Kd \t" << Kd.r() << "\t" << Kd.g() << "\t" << Kd.b() << "\n";
	fid_ << "Ks \t" << Ks.r() << "\t" << Ks.g() << "\t" << Ks.b() << "\n";

	const SUMaterialType type = mat.GetType();
	if (type == SUMaterialType_Textured || type == SUMaterialType_ColorizedTexture){
		
	}
}
