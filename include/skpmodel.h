//Pulkit Agrawal. All Rights reserved. 
//

#ifndef SKP2OBJ_SKPMODEL_H
#define SKP2OBJ_SKPMODEL_H
#include "modelUtils.h"
#include "materials.h"

class SkpModel {
	
	public:
		SkpModel(void){
			InitializeModel();
		}

		SkpModel(char* model_filename){
			InitializeModel();
			SUResult res = SUModelCreateFromFile(&model_, model_filename);
			if (res != SU_ERROR_NONE)
				std::cout <<"Error encountered in loading model \n";
			CountAllComponents();
			faces_.reserve(num_faces_);
			LoadFaces();
			LoadVertices();
		}

		virtual ~SkpModel(void){
			SUModelRelease(&model_);
		}

		void print_all_counts();


		int LoadVertices();
		//void WriteVertices();

		const std::vector<SUFaceRef>* GetFaces() { return &faces_;}

		VecStore<GeomUtils::CPoint3d>* GetVertices(){
			VecStore<GeomUtils::CPoint3d>* vertice_pointer = &vertices_;
			return vertice_pointer;
		}

		VecStore<GeomUtils::CVector3d>* GetNormals(){
			VecStore<GeomUtils::CVector3d>* normals_pointer = &normals_;
			return normals_pointer;
		}

		int Face2AttributeIndices(SUFaceRef face, std::vector<size_t>* vertIdxs, std::vector<size_t>* normalIdxs);
		//int Face2VertexIndices(SUFaceRef face);
		//int Face2NormalIndices(SUFaceRef face);

		inline size_t GetNumGroups() const    { return num_groups_; }
		inline size_t GetNumInstances() const {return num_instances_;}
		inline size_t GetNumEdges() const  {return num_edges_;}
		inline size_t GetNumFaces() const  {return num_faces_;}
		inline size_t GetNumCurves() const {return num_curves_;}
		inline size_t GetNumGuides() const {return num_guides_;}
		inline size_t GetNumImages() const {return num_images_;}
		inline size_t GetNumDefinitions() const {return num_definitions_;}

		inline void IncrementGroups(size_t incrmnt) { 
			num_groups_ = num_groups_ + incrmnt;
		}

		inline void IncrementInstances(size_t incrmnt) { 
			num_instances_ += incrmnt;
		}

		inline void IncrementEdges(size_t incrmnt) { 
			num_edges_ += incrmnt;
		}
		
		inline void IncrementFaces(size_t incrmnt) { 
			num_faces_ += incrmnt;
		}

		inline void IncrementCurves(size_t incrmnt) { 
			num_curves_ += incrmnt;
		}

		inline void IncrementGuides(size_t incrmnt) { 
			num_guides_ += incrmnt;
		}

		inline void IncrementImages(size_t incrmnt) { 
			num_images_ += incrmnt;
		}

		inline void IncrementDefinitions(size_t incrmnt) { 
			num_definitions_ += incrmnt;
		}

	private:
		size_t num_definitions_;
		size_t num_groups_, num_edges_, num_faces_, num_curves_;
		size_t num_instances_, num_guides_, num_images_;
		SUTextureWriterRef texture_writer_;
		SUModelRef model_;
		std::vector<SUEntitiesRef> entities_; 
		std::vector<SUFaceRef> faces_;
		VecStore<GeomUtils::CPoint3d> vertices_;
		VecStore<GeomUtils::CVector3d> normals_;

		void InitializeModel(){
			num_instances_ = 0;
			num_groups_    = 0;
			num_edges_     = 0;
			num_faces_     = 0;
			num_curves_    = 0;
			num_guides_    = 0;
			num_images_    = 0;
			num_definitions_ = 0;
			model_.ptr = 0;
			SUResult res = SUTextureWriterCreate(&texture_writer_);
			if (res!= SU_ERROR_NONE){
				std::cout << "Error in intializing texture writer";
			}
		}

		int LoadEntitiesRecursive(SUEntitiesRef entities);
		int LoadFaces();
		int LoadEntities();
		
		//Counting the different components
		int CountAllComponents();
		int Entities2AllComponentCount(SUEntitiesRef entitites);
};




#endif //SKP2OBJ_SKPMODEL_H
