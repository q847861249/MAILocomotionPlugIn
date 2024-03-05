// Fill out your copyright notice in the Description page of Project Settings.


#include "UM_ActorComponent.h"

#include "Net/UnrealNetwork.h" 

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

	// ...
	
}

void UUM_ActorComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUM_ActorComponent, AnimationDataAsset);

	DOREPLIFETIME(UUM_ActorComponent, CurrentAnimationTag);
}

