#ifndef RIGID_ANIMATION_CLIP_H
#define RIGID_ANIMATION_CLIP_H

#include "Vajra/Engine/AssetLibrary/Assets/AnimationAssets/RigidAnimationClipDataAsset/RigidAnimationClipDataAsset.h"
#include "Vajra/Engine/Components/DerivedComponents/Animation/AnimationClip/AnimationClip.h"

#include <memory>
#include <string>

// Forward Declarations:
class AnimationKeyFrame;
class RigidAnimationKeyFrame;

class RigidAnimationClip : public AnimationClip {
public:
	RigidAnimationClip();
	virtual ~RigidAnimationClip();

	virtual void InitAnimationClip(std::string urlOfAnimationClip);

protected:
	// @Override
	virtual AnimationKeyFrame* getCurrentKeyFrame() const;
	virtual AnimationKeyFrame* getNextKeyFrame() const;
	virtual AnimationKeyFrame* getCurrentKeyFrameAtInterpolation(float interpolation);
	virtual unsigned int getCurrentKeyFrameIndex() const;
	virtual void setCurrentKeyFrameIndex(unsigned int newIndex);
	virtual unsigned int getNumKeyFrames() const;

private:
	void init();
	void destroy();

	unsigned int currentKeyFrameIndex;
	std::shared_ptr<RigidAnimationClipDataAsset> clipDataAsset;

	RigidAnimationKeyFrame* tempKeyFrame;
	RigidAnimationKeyFrame* tempDeltaKeyFrame;
};

#endif // RIGID_ANIMATION_CLIP_H
