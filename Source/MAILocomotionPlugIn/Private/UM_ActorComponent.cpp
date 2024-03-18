// Fill out your copyright notice in the Description page of Project Settings.


#include "UM_ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "Anim/UM_AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"





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
	ACharacter* character;
	CurrentAnimationTag = tag;




	character = Cast<ACharacter>(GetOwner());
	check(character);


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *character->GetName()));
	characterMesh = character->GetMesh();

	characterMesh->GetDefaultAnimatingRigOverride();


	UUM_AnimInstance* aimInstance = Cast<UUM_AnimInstance>(characterMesh->GetAnimInstance());



	if (IsValid(aimInstance)) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

		aimInstance->Proxy.getTaggedAnimationDataSet(this);
	}
}

void UUM_ActorComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUM_ActorComponent, AnimationDataAsset);

	DOREPLIFETIME(UUM_ActorComponent, CurrentAnimationTag);

	DOREPLIFETIME(UUM_ActorComponent, characterMesh);

}

