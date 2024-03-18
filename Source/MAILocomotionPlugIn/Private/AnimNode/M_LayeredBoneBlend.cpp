// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNode/M_LayeredBoneBlend.h"
#include "UObject/Class.h"

#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimTrace.h"
#include "./Anim/UM_AnimInstance.h"

#include "GameFramework/Character.h"

#include "Logging/LogMacros.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(M_LayeredBoneBlend)

#define DEFAULT_SOURCEINDEX 0xFF




void FUM_LayeredBoneBlend::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	Super::Initialize_AnyThread(Context);

	//cast to locomotion data if instance is avaliable
	ACharacter* character = Cast<ACharacter>(Context.AnimInstanceProxy->GetSkelMeshComponent()->GetOwner());
	animInstance = Cast<UUM_AnimInstance>(character->GetMesh()->GetAnimInstance());
	if (animInstance) {
		LayerSetup = animInstance->getLayerSetting();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" %s"), *animInstance->getLayerSetting()[0].BranchFilters[0].BoneName.ToString()));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	}
}

void FUM_LayeredBoneBlend::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	Super::CacheBones_AnyThread(Context);
}

void FUM_LayeredBoneBlend::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	Super::Update_AnyThread(Context);

}

void FUM_LayeredBoneBlend::Evaluate_AnyThread(FPoseContext& Output)
{
	Super::Evaluate_AnyThread(Output);
	
}

void FUM_LayeredBoneBlend::GatherDebugData(FNodeDebugData& DebugData)
{
	Super::GatherDebugData(DebugData);
}
