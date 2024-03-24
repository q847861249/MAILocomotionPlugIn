// Fill out your copyright notice in the Description page of Project Settings.


#include "UM_ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "Anim/UM_AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "./MovementComponent/M_MovementComponent.h"
#include "./Debug/Debug.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"





// Sets default values for this component's properties
UUM_ActorComponent::UUM_ActorComponent()
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUM_ActorComponent::BeginPlay()
{
	Super::BeginPlay();

	//try to get character information
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (character) {
		CharacterMeshComponent = character->GetMesh();
		CharacterMovmentComponent = Cast<UM_MovementComponent>(GetOwner());
		if (!CharacterMovmentComponent) return;
	}

}

void UUM_ActorComponent::checkAuthority()
{
	if (GetOwner()->HasAuthority()) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Sever!"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Client!"));
	}
}



void UUM_ActorComponent::setCurrentAnimationTag_Implementation(FGameplayTag tag)
{
	CurrentAnimationTag = tag;

	UUM_AnimInstance* aimInstance = Cast<UUM_AnimInstance>(CharacterMeshComponent->GetAnimInstance());

	if (IsValid(aimInstance)) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

		aimInstance->Proxy.getTaggedAnimationDataSet(this);
	}
}

void UUM_ActorComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUM_ActorComponent, AnimationDataAsset);

	DOREPLIFETIME(UUM_ActorComponent, CurrentAnimationTag);

	DOREPLIFETIME(UUM_ActorComponent, CharacterMeshComponent);

	DOREPLIFETIME(UUM_ActorComponent, CharacterMovmentComponent);

}
