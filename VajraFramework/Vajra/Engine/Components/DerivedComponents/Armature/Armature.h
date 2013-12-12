#ifndef ARMATURE_H
#define ARMATURE_H

#include "Vajra/Common/Components/Component.h"
#include "Vajra/Engine/Components/DerivedComponents/Armature/Declarations.h"

#include "Libraries/glm/glm.hpp"

#include <map>
#include <string>
#include <vector>


// Forward Declarations:
class Bone;
class FinalBoneTransformsSet;
class Object;

class Armature : public Component {
public:
	Armature();
	Armature(Object* object_);
	~Armature();

	static inline unsigned int GetTypeId() { return componentTypeId; }

	void InitArmature(std::string armatureFilePath);

	// Writes the final bone transform matrices to the shader:
	// TODO [Cleanup] Rename this to Draw(), maybe
	void Bind();

	// @Override
	virtual void HandleMessage(Message* message);

	void AddBone(Bone* newBone);
	Bone* GetBoneById(unsigned int boneId);
	Bone* GetBoneByName(std::string boneName);

	void SetRootBoneByName(std::string rootBoneName);

	void DumpBoneKeyframes();
	void ReadOtherFinalBoneTransformsFromFile(std::string filePath);

private:
	void init();
	void destroy();

	void updateBoneMatrices();
	void resetFinalBoneTransforms();

	static unsigned int componentTypeId;

	std::map<unsigned int /* bone id */, Bone*> bones;
	Bone* rootBone;

	glm::mat4 finalBoneTransforms[MAX_BONES];
	std::vector<FinalBoneTransformsSet*> otherFinalBoneTransformsSet;

	friend class Bone;
};

class FinalBoneTransformsSet {
public:
	glm::mat4 finalBoneTransforms[MAX_BONES];
};

#endif // ARMATURE_H
