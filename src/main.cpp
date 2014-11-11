#include <vector>
#include <iostream>
#include "objtexturehelper.h"
#include "modelUtils.h"
#include "skpmodel.h"
#include "objwriter.h"

int main(int argc, char* argv[]) {
  //Get Model Name
	if (argc < 2){
		std::cout << "argc is " << argc << "\n";
		std::cout<< "Usage: skp2obj input_file_name \n";
		return 1;
	}
	char* model_name = argv[1];
	//std::cout << "Reading from file " << model_name <<"\n";

	// Always initialize the API before using it
  SUInitialize();
	
	SkpModel myModel = SkpModel(model_name);
	//myModel.print_all_counts();

	std::string outFile = "tmp/myobj.obj";
	std::string mtlFile = "tmp/mymtl.mtl";
	ObjWriter writer(outFile.c_str(), mtlFile.c_str());
	writer.WriteHeader();
	writer.WriteModel(&myModel);
			


	/*
  // Load the model from a file
  SUModelRef model = SU_INVALID;
  SUResult res = SUModelCreateFromFile(&model, model_name);
  if (res != SU_ERROR_NONE)
    return 1;
  
	// Get the entity container of the model.
  SUEntitiesRef entities = SU_INVALID;
  SUModelGetEntities(model, &entities);

	size_t num_definitions = 0;
	SUModelGetNumComponentDefinitions(model, &num_definitions);
	std::cout << "Num Defintions: " << num_definitions << "\n";

	if (num_definitions > 0) {
			std::vector<SUComponentDefinitionRef> component_definitions(num_definitions);
			SUModelGetComponentDefinitions(model, num_definitions, 
													 &component_definitions[0],
													 &num_definitions);

			for (size_t i = 0; i < num_definitions; i++) {
				SUComponentDefinitionRef component_definition =
						component_definitions[i];
				SUEntitiesRef entities2 = SU_INVALID;
				SUComponentDefinitionGetEntities(component_definitions[i], &entities2);
				int a = getModelInfo(entities2);
				//LoadComponent(texture_writer, component_definition);
			}
	}


	//Get Model Info
	int info_res = getModelInfo(entities);	
  
  // Get model name
  SUStringRef name = SU_INVALID;
  SUStringCreate(&name);
  SUModelGetName(model, &name);
  size_t name_length = 0;
  SUStringGetUTF8Length(name, &name_length);
  char* name_utf8 = new char[name_length + 1];
  SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
  // Now we have the name in a form we can use
  SUStringRelease(&name);
	std::cout << "Model Name is " << name_utf8 << "\n";
  delete []name_utf8;
 
 	// Must release the model or there will be memory leaks
  SUModelRelease(&model);
 
	*/
 	// Terminate the API.
  SUTerminate();
  return 0;
}
