// Fill out your copyright notice in the Description page of Project Settings.


#include "ARItemChest.h"

// Sets default values
AARItemChest::AARItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TargetPitch = 110;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AARItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0,0));
}