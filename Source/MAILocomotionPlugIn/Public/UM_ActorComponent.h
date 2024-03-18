// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "./M_DataAsset.h"
#include <AnimNode_ControlRig.h>

#include "UM_ActorComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAILOCOMOTIONPLUGIN_API UUM_ActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUM_ActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

public:
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "M_DataAsset")
	UM_DataAsset* AnimationDataAsset;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "M_DataAsset")
	FGameplayTag CurrentAnimationTag;

	UPROPERTY(BlueprintReadOnly, Replicated)
	USkeletalMeshComponent* characterMesh;

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_ControlRig Node;


	UFUNCTION(BlueprintCallable)
	void checkAuthority();

		
	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void setCurrentAnimationTag(FGameplayTag tag);


};
