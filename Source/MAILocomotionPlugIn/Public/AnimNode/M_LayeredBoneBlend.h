// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimTypes.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimData/BoneMaskFilter.h"

#include "AnimNodes/AnimNode_LayeredBoneBlend.h"

#include "M_LayeredBoneBlend.generated.h"

/**
 * 
 */
class UUM_AnimInstance;

USTRUCT()
struct MAILOCOMOTIONPLUGIN_API FUM_LayeredBoneBlend : public FAnimNode_LayeredBoneBlend
{
	GENERATED_USTRUCT_BODY()

public:

	FUM_LayeredBoneBlend() :Super(){}

	~FUM_LayeredBoneBlend() {}

	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	virtual int32 GetLODThreshold() const override { return LODThreshold; }
	// End of FAnimNode_Base interface


private:

	UUM_AnimInstance* animInstance;

	friend class UMAnimGraphNode_LayeredBoneBlend;

};
