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
	WriteStqcoords(model->GetStqcoordsFront());
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

void ObjWriter::WriteStqcoords(VecStore<GeomUtils::CPoint3d>* coords){
	size_t len = coords->length();
	for (size_t i=0; i<len; i++){
		const GeomUtils::CPoint3d pt = coords->get(i);
		fid_ << "vt\t" << pt.x() << "\t" << pt.y() << "\t" << pt.z() << "\n";
	}	
}

void ObjWriter::WriteFaces(SkpModel* model){
	const std::vector<SUFaceRef>* faces = model->GetFaces();	
	for (size_t f=0; f < faces->size(); f ++){
		size_t num_vertices = Face2NumVertices((*faces)[f]);
		std::vector<size_t> vIdx(num_vertices);
		std::vector<size_t> nIdx(num_vertices);
		std::vector<size_t> fIdx(num_vertices);

		model->Face2AttributeIndices((*faces)[f], &vIdx, &nIdx, &fIdx);
		assert(vIdx.size() == num_vertices);
		fid_ << "f\t";
		for (size_t i=0; i<num_vertices; i++){
			assert(vIdx[i]>=0);
			assert(nIdx[i]>=0);
			assert(fIdx[i]>=0);
			fid_ << vIdx[i] + 1 << "/" << fIdx[i] + 1 << "/" << nIdx[i] + 1 << "\t";
		}
		fid_ <<"\n";
	}
}

void ObjWriter::WriteAllMaterials(SkpModel* model){
	const MaterialMap mmap = *(model->GetMaterialMap());
	for (auto& x: mmap)
		WriteMaterial(x.second);
}

void ObjWriter::WriteMaterial(Material* mat){
	SUResult res;
	//fid_mtl_.precision(6);
	fid_mtl_ << "newmtl \t" << mat->GetName() << "\n";
	const Color Ka = mat->GetKa();
	const Color Kd = mat->GetKd();
	const Color Ks = mat->GetKs();
	fid_mtl_ << "Ka \t" << Ka.r() << "\t" << Ka.g() << "\t" << Ka.b() << "\n";
	fid_mtl_ << "Kd \t" << Kd.r() << "\t" << Kd.g() << "\t" << Kd.b() << "\n";
	fid_mtl_ << "Ks \t" << Ks.r() << "\t" << Ks.g() << "\t" << Ks.b() << "\n";

	const bool is_opacity = mat->GetIsOpacity();
	if (is_opacity){
		fid_mtl_ << "d \t" << mat->GetAlpha();
	}

	
	const SUMaterialType type = mat->GetType();
	if (type == SUMaterialType_Textured || type == SUMaterialType_ColorizedTexture){
		SUTextureRef texture = SU_INVALID;
		const Texture* matTex = mat->GetTexture();

		std::cout << "Width: " << matTex->width() << "Height: " << matTex->height()
			<< "bits: " << matTex->bits_per_pixel() << "\n";
		res = SUTextureCreateFromImageData(&texture, matTex->width(), matTex->height(),
																			  matTex->bits_per_pixel(), matTex->data());
		ErrorHandler(res);
	
		std::string outname = "tmp/" + matTex->name(); 	
		res = SUTextureWriteToFile(texture, outname.c_str());
		res = SUTextureRelease(&texture);

		fid_mtl_ << "map_Kd \t" << matTex->name() << "\n";
		
	}
	//*/
	fid_mtl_ << "\n";
}
