// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBarrel.h"

#include "WorldPartition/ContentBundle/ContentBundleLog.h"

// Sets default values
AARBarrel::AARBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Barrel");
	BarrelMeshComp->SetSimulatePhysics(true);
	BarrelMeshComp->OnComponentHit.AddDynamic(this, &AARBarrel::OnHit);

	RootComponent = BarrelMeshComp;

	RadForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadForceComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AARBarrel::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("start"));
}

// Called every frame
void AARBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARBarrel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// only run if the other thing is a projectile
	if (OtherComp->GetCollisionObjectType()==ECC_GameTraceChannel1)
	{
		const FVector OtherLocation = OtherActor->GetActorLocation();
		RadForceComp->SetWorldLocation(OtherLocation);
		RadForceComp->FireImpulse();
		RadForceComp->SetRelativeLocation(FVector::ZeroVector); // thanks ethan :)
	}
}


