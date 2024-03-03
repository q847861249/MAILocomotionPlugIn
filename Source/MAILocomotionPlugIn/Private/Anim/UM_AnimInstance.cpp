// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/UM_AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void FM_AnimInstanceProxy::InitializeObjects(UAnimInstance* InAnimInstance)
{
	Super::InitializeObjects(InAnimInstance);


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
	return FLcomotion();
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
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	}

}

void UUM_AnimInstance::printAnimation(ECharacterLcomotionState currentstate)
{
}

FLcomotion UUM_AnimInstance::getCurrentLocomotionSet()
{
	//check(Proxy.LocomotionAnimSet);
	return Proxy.LocomotionAnimSet;
}

UAnimSequence* UUM_AnimInstance::getLocomotionAnimation(ECharacterLcomotionState currentstate)
{
	return nullptr;
}