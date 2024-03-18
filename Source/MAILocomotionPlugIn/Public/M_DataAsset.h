// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Animation/AnimSequence.h"
#include "GameplayTagContainer.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "ControlRig.h"
#include "Animation/BlendSpace1D.h"

#include "Animation/AnimData/BoneMaskFilter.h"

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
struct FAnimLean {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool EnbaleLean;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Lean_Left;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Lean_Middle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Lean_Right;

};



USTRUCT(Blueprintable)
struct FStartAngleDirection {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Forward_180L;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Forward_180R;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Forward_90L;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequence* Forward_90R;
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
	bool EnablePivot;

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
	FStartAngleDirection JogStartOrient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction ADSStartCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FStartAngleDirection ADSS_StartOrient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FAnim4Direction CrouchStartCardinals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Animation"))
	FStartAngleDirection Crouch_StartOrient;
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
struct FAimSet_Jump {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* JumpStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* JumpApex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* JumpFallLand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* JumpRecoveryAdditive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* JumpStartLoop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* JumpFallLoop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName GroundDistanceCruveName = "GroundDistance";
};

USTRUCT(Blueprintable)
struct FSetting {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float strideWarpingStartAlpha = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float strideWarpingPivottAlpha = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float strideWarpingCycletAlpha = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "FootIk"))
	FName LeftFoot = "foot_l";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "FootIk"))
	FName RightFoot = "foot_r";


};


USTRUCT(Blueprintable)
struct FTrun_In_Place {
	
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool EnableTurnInPlace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* TurnInPlaceLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* TurnInPlaceRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* CrouchTurnInPlaceLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* CrouchTurnInPlaceRight;

};

USTRUCT(Blueprintable)
struct FIdle_Break {

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool WnatsIdleBreak;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeUntilNextIdleBreak;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentIdleBreakIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float IdleBreakDelayTime;

};



USTRUCT(Blueprintable)
struct FAnimSet_Aiming {

	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UpperBody")
	bool bBlendUppterBody;

	UPROPERTY(EditDefaultsOnly, Category = "UpperBody")
	TArray<FInputBlendPose> BoneBlendForAnimFirePose;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animing")
	bool AvctiveAiming;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animing")
	UAnimSequence* AimHipFirePose;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animing")
	UAnimSequence* AimHipFirePoseCrouch;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animing")
	UAimOffsetBlendSpace* IdleAimOffset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animing")
	UAimOffsetBlendSpace* RelaxedAimOffset;


};



USTRUCT(Blueprintable)
struct FLcomotion
{
	GENERATED_BODY()

public:
	//不同武器的动作需要一个tag来区分
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "AnimationItemTag"))
	FGameplayTag AnimationTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName LocomotionDistanceCurveName = "Distance";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAnimLean BlendPoseLean;




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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAimSet_Jump AimSet_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FIdle_Break IdleBreak;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTrun_In_Place TurnInPlace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAnimSet_Aiming AnimSetAiming;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FSetting Setting;

};



UCLASS()
class MAILOCOMOTIONPLUGIN_API UM_DataAsset : public UDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "AnimData"))
	TArray<FLcomotion> AnimationSet;



	
};
