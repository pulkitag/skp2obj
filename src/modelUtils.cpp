#include "modelUtils.h"

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
	

