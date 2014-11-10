// Copyright Pulkit Agrawal. All Rights Reserved.

#ifndef SKP2OBJ_MODELUTILS_H
#define SKP2OBJ_MODELUTILS_H

#include <slapi/model/defs.h>
#include <slapi/model/component_definition.h>
#include <slapi/model/component_instance.h>
#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/model/group.h>
#include <slapi/initialize.h>
#include <slapi/unicodestring.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/face.h>
#include <slapi/model/edge.h>
#include <slapi/model/vertex.h>
#include <slapi/model/texture.h>
#include <slapi/model/material.h>
#include <slapi/model/mesh_helper.h>
#include <slapi/model/texture_writer.h>
#include <iostream>
#include <vector>
#include <cassert>
#include "geomutils.h"

int getModelInfo(SUEntitiesRef entities);
int Instances2Entities(std::vector<SUComponentInstanceRef>* instances, std::vector<SUEntitiesRef>* entities);
int Groups2Entities(std::vector<SUGroupRef>* groups, std::vector<SUEntitiesRef>* entities);
void ErrorHandler(SUResult res);
size_t Face2NumVertices(SUFaceRef face);
bool IsFaceFrontTexture(SUFaceRef face);
bool IsFaceBackTexture(SUFaceRef face);
void GetFaceFrontMaterial(SUFaceRef face);
std::string GetMaterialName(SUMaterialRef material);

template <typename Dtype> class VecStore {
	public:
		VecStore(){
			idx_ = 0;
			maxSz_ = 0;
		}

		VecStore(size_t maxElms){
			idx_ = 0;
			maxSz_ = maxElms;
			x_.reserve(maxElms);
		}

		virtual ~VecStore(){};

		void add(Dtype elm);
		void add(SUVertexRef vertex);
		void add(SUVector3D vec);
		void add(SUPoint3D pt);

		size_t length() const {return x_.size();}

		void add(std::vector<Dtype> elm){
			for (int i=0; i<elm.size(); i++)
				add(elm[i]);
		}
		void add(std::vector<SUVertexRef> vertex){
			for (int i=0; i<vertex.size(); i++)
				add(vertex[i]);
		}
		void add(std::vector<SUVector3D> vec){
			for (int i=0; i<vec.size(); i++)
				add(vec[i]);
		}
		void add(std::vector<SUPoint3D> pt){
			for (int i=0; i<pt.size(); i++)
				add(pt[i]);
		}

		Dtype get(size_t idx) const{
			assert(idx < idx_);
			return x_[idx];
		}

		size_t get_index(Dtype elm) const{
			for (size_t i=0; i<idx_; i++){
				if (elm == x_[i])
					return i;
			}
			std::cout <<"Element Not Found \n";
		}

	private:
		std::vector<Dtype> x_;
		size_t maxSz_;
	  size_t idx_;	
};

#endif //SKP2OBJ_MODEL_UTILS_H
