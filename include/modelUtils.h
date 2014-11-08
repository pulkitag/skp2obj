// Copyright Pulkit Agrawal. All Rights Reserved.

#ifndef SKP2OBJ_MODELUTILS_H
#define SKP2OBJ_MODELUTILS_H

#include <slapi/model/defs.h>
#include <slapi/model/component_definition.h>
#include <slapi/model/component_instance.h>
#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/initialize.h>
#include <slapi/unicodestring.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/face.h>
#include <slapi/model/edge.h>
#include <slapi/model/vertex.h>
#include <iostream>
#include <vector>

int getModelInfo(SUEntitiesRef entities);
int Instances2Entities(std::vector<SUComponentInstanceRef>* instances, std::vector<SUEntitiesRef>* entities);
//int Groups2Entities(std::vector<SUGroupRef> groups, std::vector<SUEntitiesRef> entities);


#endif //SKP2OBJ_MODEL_UTILS_H
