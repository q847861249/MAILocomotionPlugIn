// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "./UM_ActorComponent.h"
#include "./M_DataAsset.h"

#include "Animation/AnimInstanceProxy.h"

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

	//*�û������Ķ�������* �ǳ���Ҫ
	UPROPERTY(Transient)
	FLcomotion LocomotionAnimSet;

public:

	//�������Ʒ�����׼���ǩ
	UPROPERTY(Transient)
	FGameplayTag CurrentAnimationTag;

	//����Ļ�������
	UPROPERTY(Transient)
	ECharacterState CurrentCharacterState_ANI = ECharacterState::Jog;


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
	UAnimSequence* getLocomotionAnimation(ECharacterLcomotionState currentstate);

	
};