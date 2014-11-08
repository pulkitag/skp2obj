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
#include <iostream>
#include <vector>
#include <cassert>

int getModelInfo(SUEntitiesRef entities);
int Instances2Entities(std::vector<SUComponentInstanceRef>* instances, std::vector<SUEntitiesRef>* entities);
int Groups2Entities(std::vector<SUGroupRef>* groups, std::vector<SUEntitiesRef>* entities);

template <typename Dtype>
class VecStore {
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

		virtual ~VecStore();

		void add(Dtype elm){
			bool existFlag = false;
			for (int i=0; i<idx_; i++){
				if (x_[i] == elm)
					existFlag = true;	
			}

			if (!existFlag){
				x_.append(elm);
				idx_ += 1;
			}
			assert(idx_ < maxSz_);
		}

		void add(std::vector<Dtype> elm){
			for (int i=0; i<elm.size(); i++)
				x_.add(elm[i]);
		}

		Dtype get(size_t idx){
			assert(idx < idx_);
			return x_[idx];
		}

	private:
		std::vector<Dtype> x_;
		size_t maxSz_;
	  size_t idx_;	
};

#endif //SKP2OBJ_MODEL_UTILS_H
