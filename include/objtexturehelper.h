// Copyright Pulkit Agrawal. All Rights Reserved.

#ifndef SKP2OBJ_COMMON_OBJTEXTUREHELPER_H
#define SKP2OBJ_COMMON_OBJTEXTUREHELPER_H

#include <slapi/model/defs.h>

class CObjTextureHelper {
 public:
  CObjTextureHelper();
  virtual ~CObjTextureHelper() {}

  // Load all textures, return number of textures
  // Input: model to load textures from
  // Input: texture writer
  // Input: layers or entities
  size_t LoadAllTextures(SUModelRef model, SUTextureWriterRef texture_writer,
                         bool textures_from_layers);

 private:
  // Load textures from all of the entities that have textures
  void LoadComponent(SUTextureWriterRef texture_writer,
                     SUComponentDefinitionRef component);
  void LoadEntities(SUTextureWriterRef texture_writer,
                    SUEntitiesRef entities);
  void LoadComponentInstances(SUTextureWriterRef texture_writer,
                              SUEntitiesRef entities);
  void LoadGroups(SUTextureWriterRef texture_writer,
                  SUEntitiesRef entities);
  void LoadFaces(SUTextureWriterRef texture_writer,
                 SUEntitiesRef entities);
  void LoadImages(SUTextureWriterRef texture_writer,
                  SUEntitiesRef entities);
};

#endif // SKP2OBJ_COMMON_OBJTEXTUREHELPER_H
