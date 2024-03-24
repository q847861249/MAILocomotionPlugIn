// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "./M_DataAsset.h"
#include <AnimNode_ControlRig.h>

#include "UM_ActorComponent.generated.h"

class UM_MovementComponent;
class UAnimMontage;
class UAnimInstance;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAILOCOMOTIONPLUGIN_API UUM_ActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUM_ActorComponent();

	UPROPERTY(EditDefaultsOnly, Replicated, Category = CharacterInformation)
	UM_DataAsset* AnimationDataAsset;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = CharacterInformation)
	FGameplayTag CurrentAnimationTag;

protected:


	UPROPERTY(EditAnywhere, Category = AnimationSettings)
	FAnimNode_ControlRig Node;

	UM_MovementComponent* CharacterMovmentComponent;
	USkeletalMeshComponent* CharacterMeshComponent;


	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void checkAuthority();

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void setCurrentAnimationTag(FGameplayTag tag);

	friend class UM_MovementComponent;


};
