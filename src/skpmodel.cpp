#include "skpmodel.h"
#include "modelUtils.h"

int SkpModel::CountAllComponents(){
	int out = 0;

	LoadEntities();
	std::cout <<"NumEntities: " << entities_.size() << "\n";
	for (int i=0; i<entities_.size(); i++){
		out += Entities2AllComponentCount(entities_[i]);
	}

	/*
	//Get the entitites
	SUEntitiesRef entities = SU_INVALID;
  SUModelGetEntities(model_, &entities);
	
	//Count the number of all components in entitites
	out += count_all_components_entities(entities);
	*/

	/*
	//Count components in ComponentDefinitions
	size_t num_definitions = 0;
	SUModelGetNumComponentDefinitions(model_, &num_definitions);
	IncrementDefinitions(num_definitions);
	
	
	if (num_definitions > 0) {
			std::vector<SUComponentDefinitionRef> component_definitions(num_definitions);
			SUModelGetComponentDefinitions(model_, num_definitions, 
													 &component_definitions[0],
													 &num_definitions);

			for (size_t i = 0; i < num_definitions; i++) {
				SUComponentDefinitionRef component_definition =
						component_definitions[i];
				SUEntitiesRef entities2 = SU_INVALID;
				SUComponentDefinitionGetEntities(component_definitions[i], &entities2);
				out += count_all_components_entities(entities2);
			}
	}
	*/
	return out;
}

int SkpModel::Entities2AllComponentCount(SUEntitiesRef entities){

	int out = 0;	
	if (SUIsInvalid(entities))
		return 1;
	
	size_t instanceCount = 0;
  SUResult res =  SUEntitiesGetNumInstances(entities, &instanceCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementInstances(instanceCount);

  /*	
	if (instanceCount > 0) {
		std::vector<SUComponentInstanceRef> instances(instanceCount);
		std::vector<SUEntitiesRef> entities2(instanceCount);
		SUEntitiesGetInstances(entities, instanceCount,
													 &instances[0], &instanceCount);
		out += Instances2Entities(&instances, &entities2);

		for (size_t i = 0; i < instanceCount; i++) {
			out += count_all_components_entities(entities2[i]);
		}
	}
	*/

	size_t groupCount = 0;
	res =  SUEntitiesGetNumGroups(entities, &groupCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementGroups(groupCount); 

	/*
	if (groupCount > 0){
		std::vector<SUGroupRef> groups(groupCount);
		std::vector<SUEntitiesRef> entities2(groupCount);
		SUEntitiesGetGroups(entities, groupCount, &groups[0], &groupCount);
		out += Groups2Entities(&groups, &entities2);
		for (size_t i=0; i < groupCount; i++){
			out += count_all_components_entities(entities2[i]);
		}
	}
	*/

	size_t edgeCount = 0;
	res = SUEntitiesGetNumEdges(entities, true,	&edgeCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementEdges(edgeCount);

	size_t guideCount = 0;
	res =  SUEntitiesGetNumGuidePoints(entities, &guideCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementGuides(guideCount);

	size_t curveCount = 0;
	res =  SUEntitiesGetNumCurves(entities, &curveCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementCurves(curveCount);

	size_t imCount = 0;
	res =  SUEntitiesGetNumImages(entities, &imCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementImages(imCount);

  size_t faceCount = 0;
  res = SUEntitiesGetNumFaces(entities, &faceCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementFaces(faceCount);

	return out;	
	
}

void SkpModel::print_all_counts(){
	
	std::cout << "Definitions: " << GetNumDefinitions() << "\n";
	std::cout << "Instances: "   << GetNumInstances()   << "\n";
	std::cout << "Groups: "      << GetNumGroups()      << "\n";
	std::cout << "Faces: "       << GetNumFaces()       << "\n";
	std::cout << "Images: "      << GetNumImages()      << "\n";
	std::cout << "Edges: "       << GetNumEdges()       << "\n";
	std::cout << "Guides: "      << GetNumGuides()      << "\n";
	std::cout << "Curves: "      << GetNumCurves()      << "\n";

}

int SkpModel::LoadEntities(){
	int out = 0;
	if (entities_.size() > 0)
		return 0;
	
	SUEntitiesRef entities = SU_INVALID;
  SUModelGetEntities(model_, &entities);
	entities_.push_back(entities);
	
	out = LoadEntitiesRecursive(entities);

	return out;
}


int SkpModel::LoadEntitiesRecursive(SUEntitiesRef entities){

	int out = 0;

	//Get Entities from Instances
	size_t instanceCount;
  SUResult res =  SUEntitiesGetNumInstances(entities, &instanceCount);
  if (res != SU_ERROR_NONE)
    return 1;

	if (instanceCount > 0) {
		std::vector<SUComponentInstanceRef> instances(instanceCount);
		std::vector<SUEntitiesRef> entities2(instanceCount);
		SUEntitiesGetInstances(entities, instanceCount,
													 &instances[0], &instanceCount);
		out += Instances2Entities(&instances, &entities2);

		for (size_t i = 0; i < instanceCount; i++) {
			entities_.push_back(entities2[i]);
			LoadEntitiesRecursive(entities2[i]);	
		}
	}

	//Get Entities from groups
	size_t groupCount = 0;
	res =  SUEntitiesGetNumGroups(entities, &groupCount);
  if (res != SU_ERROR_NONE)
    return 1;

	if (groupCount > 0){
		std::vector<SUGroupRef> groups(groupCount);
		std::vector<SUEntitiesRef> entities2(groupCount);
		SUEntitiesGetGroups(entities, groupCount, &groups[0], &groupCount);
		out += Groups2Entities(&groups, &entities2);
		for (size_t i=0; i < groupCount; i++){
			entities_.push_back(entities2[i]);
			LoadEntitiesRecursive(entities2[i]);	
		}
	}

	return out;
}

int SkpModel::LoadFaces(){
	int out = 0;
	for (int i=0; i<entities_.size(); i++){
		
	}

	return out;
}
