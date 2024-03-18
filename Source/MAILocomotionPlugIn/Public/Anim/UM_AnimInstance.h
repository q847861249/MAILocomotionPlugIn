// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "./UM_ActorComponent.h"
#include "./M_DataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimData/BoneMaskFilter.h"

#include "UM_AnimInstance.generated.h"


UENUM(BlueprintType)
enum class ECharacterLcomotionState : uint8 {
	Idle       UMETA(DisplayName = "Idle"),
	Start        UMETA(DisplayName = "Start"),
	Cycle     UMETA(DisplayName = "Cycle"),
	Stop     UMETA(DisplayName = "Stop")
};



USTRUCT()
struct FM_AnimInstanceProxy : public FAnimInstanceProxy

{

	GENERATED_BODY()

	virtual void InitializeObjects(UAnimInstance* InAnimInstance) override;

	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;

	virtual void Update(float DeltaSeconds) override;


public:

	FLcomotion getTaggedAnimationDataSet(UUM_ActorComponent* LocomotionComponent);

	UUM_ActorComponent* getPlugInActorComponent(UAnimInstance* InAnimInstance);



public:

	//*用户创建的动作数组* 非常重要
	UPROPERTY(Transient)
	FLcomotion LocomotionAnimSet;



public:

	//最近的物品动作套件标签
	UPROPERTY(Transient)
	FGameplayTag CurrentAnimationTag;

	//运动组件
	UPROPERTY(Transient)
	UCharacterMovementComponent* MovementComponent;

	//运动组件
	UPROPERTY(Transient)
	USkeletalMeshComponent* SkeletalMeshComponent;


};

UCLASS()
class MAILOCOMOTIONPLUGIN_API UUM_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	///////////////////////////////////////////////////
	// Thread Safe Proxy
	///////////////////////////////////////////////////

	UPROPERTY(Transient)
	FM_AnimInstanceProxy Proxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override { return &Proxy; }

	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override {}

	friend struct FM_AnimInstanceProxy;

	virtual void NativeBeginPlay() override;


public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void printAnimation(ECharacterLcomotionState currentstate);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FLcomotion getCurrentLocomotionSet();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	UCharacterMovementComponent* getCharacterMovementComponent() { return Proxy.MovementComponent; };

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FLcomotion LocomotionSet() { return Proxy.LocomotionAnimSet; };




public:
	UFUNCTION(meta = (BlueprintThreadSafe))
	TArray<FInputBlendPose> getLayerSetting() const { return Proxy.LocomotionAnimSet.AnimSetAiming.BoneBlendForAnimFirePose; } ;

//The function here is helping function

	
};
