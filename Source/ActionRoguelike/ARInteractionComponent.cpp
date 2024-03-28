// Fill out your copyright notice in the Description page of Project Settings.


#include "ARInteractionComponent.h"

#include "ARGameplayInterface.h"

// Sets default values for this component's properties
UARInteractionComponent::UARInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UARInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UARInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UARInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 250);
	
	FHitResult Hit;
	
	bool bRayHitSomething = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	FColor DebugRayColor = (bRayHitSomething) ? FColor::Yellow : FColor::Red;
	DrawDebugLine(GetWorld(), EyeLocation, End, DebugRayColor, false, 2.0f, 0, 2.0f);

	AActor* HitActor = Hit.GetActor();
	if (bRayHitSomething && HitActor)
	{
		if (HitActor->Implements<UARGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			IARGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}

}

