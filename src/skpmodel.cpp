#include "skpmodel.h"
#include "modelUtils.h"

int SkpModel::count_all_components(){
	int out = 0;

	//Get the entitites
	SUEntitiesRef entities = SU_INVALID;
  SUModelGetEntities(model_, &entities);
	
	//Count the number of all components in entitites
	out += count_all_components_entities(entities);


	//Count components in ComponentDefinitions
	size_t num_definitions = 0;
	SUModelGetNumComponentDefinitions(model_, &num_definitions);
	IncrementDefinitions(num_definitions);
	
	/*
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

int SkpModel::count_all_components_entities(SUEntitiesRef entities){

	int out = 0;	
	if (SUIsInvalid(entities))
		return 1;
	
	size_t instanceCount = 0;
  SUResult res =  SUEntitiesGetNumInstances(entities, &instanceCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementInstances(instanceCount);

	
	if (instanceCount > 0) {
      std::vector<SUComponentInstanceRef> instances(instanceCount);
      std::vector<SUEntitiesRef> entities2(instanceCount);
			SUEntitiesGetInstances(entities, instanceCount,
                             &instances[0], &instanceCount);
			out += Instances2Entities(&instances, &entities2);

      for (size_t i = 0; i < instanceCount; i++) {
        /*
				SUComponentInstanceRef instance = instances[i];
        if (!SUIsInvalid(instance)) {
					 SUComponentDefinitionRef component_definition;
					 SUComponentInstanceGetDefinition(instances[i], &component_definition);
					 SUEntitiesRef entities2 = SU_INVALID;
					 SUComponentDefinitionGetEntities(component_definition, &entities2);
           out = count_all_components_entities(entities2);
				}
				*/
				out += count_all_components_entities(entities2[i]);
		}
	}
	

	size_t groupCount = 0;
	res =  SUEntitiesGetNumGroups(entities, &groupCount);
  if (res != SU_ERROR_NONE)
    return 1;
	IncrementGroups(groupCount); 

	if (groupCount > 0){
		std::vector<SUGroupRef> groups(groupCount);
		SUEntitiesGetGroups(entities, groupCount, &groups[0], &groupCount);
		for (size_t i=0; i < groupCount; i++){
			SUGroupRef group = groups[i];
			SUEntitiesRef entities2 = SU_INVALID;
			SUGroupGetEntities(group, &entities2);
			out = count_all_components_entities(entities2);
		}
	}

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

