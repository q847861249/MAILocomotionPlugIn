// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/UM_AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"





void FM_AnimInstanceProxy::InitializeObjects(UAnimInstance* InAnimInstance)
{
	Super::InitializeObjects(InAnimInstance);
	
	APawn* Owner = Cast<APawn>(InAnimInstance->TryGetPawnOwner());

	if (IsValid(Owner)) {
		MovementComponent = Cast<UCharacterMovementComponent>(Owner->GetMovementComponent());
	}
}

void FM_AnimInstanceProxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	Super::PreUpdate(InAnimInstance, DeltaSeconds);
}

void FM_AnimInstanceProxy::Update(float DeltaSeconds)
{
	Super::Update(DeltaSeconds);

}

FLcomotion FM_AnimInstanceProxy::getTaggedAnimationDataSet(UUM_ActorComponent* LocomotionComponent)
{
	FLcomotion AnimationDataAsset_Return;

	if (LocomotionComponent->CurrentAnimationTag.IsValid()) {

		//同步标签和最近动作状态
		CurrentAnimationTag = LocomotionComponent->CurrentAnimationTag;
	}
	for (FLcomotion locomotion : LocomotionComponent->AnimationDataAsset->AnimationSet) {

		if (locomotion.AnimationTag == LocomotionComponent->CurrentAnimationTag) {
			AnimationDataAsset_Return = locomotion;
		}
	}
	LocomotionAnimSet = AnimationDataAsset_Return;

	return AnimationDataAsset_Return;
}

UUM_ActorComponent* FM_AnimInstanceProxy::getPlugInActorComponent(UAnimInstance* InAnimInstance)
{
	APawn* Owner = InAnimInstance->TryGetPawnOwner();
	check(Owner);

	if (Owner->FindComponentByClass<UUM_ActorComponent>()) {
		return Owner->FindComponentByClass<UUM_ActorComponent>();
	}
	else {
		return nullptr;
	}
}

void UUM_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if (Proxy.getPlugInActorComponent(this)) {
		Proxy.LocomotionAnimSet = Proxy.getTaggedAnimationDataSet(Proxy.getPlugInActorComponent(this));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	}

}

void UUM_AnimInstance::printAnimation(ECharacterLcomotionState currentstate)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
 	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *Proxy.LocomotionAnimSet.AnimSet_Idle.IdleADS->GetName()));
}

FLcomotion UUM_AnimInstance::getCurrentLocomotionSet()
{
	//check(Proxy.LocomotionAnimSet);
	return Proxy.LocomotionAnimSet;
}






