// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Animation/AnimSequence.h"
#include "GameplayTagContainer.h"

#include "M_DataAsset.generated.h"


struct FGameplayTag;


UENUM(Blueprintable)
enum class ECharacterState : uint8 {
	Walk       UMETA(DisplayName = "Walk"),
	Jog        UMETA(DisplayName = "Jog"),
	Crouch     UMETA(DisplayName = "Crouch"),
};


USTRUCT(Blueprintable)
struct FAnim4Direction {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Forward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Backward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Left;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Right;
};



USTRUCT(Blueprintable)
struct FAimSet_Walk {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction WalkCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction CrouchWalkCardinals;

};

USTRUCT(Blueprintable)
struct FAimSet_Idle {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* IdleADS;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* IdleHipfire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UAnimSequence*> IdleBreaks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* CrouchIdle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* CrouchIdleEntry;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* CrouchIdleExit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* LeftHandPoseOverride;

};


USTRUCT(Blueprintable)
struct FAimSet_Jog {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction JogCardinals;

};


USTRUCT(Blueprintable)
struct FAimSet_Pivots {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction JogPivotCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction ADSPivotCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction CrouchPivotCardinals;
};

USTRUCT(Blueprintable)
struct FAimSet_Starts {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction JogStartCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction ADSStartCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction CrouchStartCardinals;
};


USTRUCT(Blueprintable)
struct FAimSet_Stops {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction JogStopCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction ADSStopCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction CrouchStopCardinals;
};


USTRUCT(Blueprintable)
struct FLcomotion
{
	GENERATED_BODY()

public:
	//不同武器的动作需要一个tag来区分
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "AnimationItemTag"))
	FGameplayTag AnimationTag;



public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAimSet_Walk AnimSet_Walk;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAimSet_Idle AnimSet_Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAimSet_Jog AnimSet_Jog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAimSet_Pivots AimSet_Pivot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAimSet_Starts AimSet_Starts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAimSet_Stops AimSet_Stops;


};



UCLASS()
class MAILOCOMOTIONPLUGIN_API UM_DataAsset : public UDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "AnimData"))
	TArray<FLcomotion> AnimationSet;
	
};
