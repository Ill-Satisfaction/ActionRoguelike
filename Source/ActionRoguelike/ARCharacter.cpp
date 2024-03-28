// Fill out your copyright notice in the Description page of Project Settings.


#include "ARCharacter.h"

#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AARCharacter::AARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiate components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UARInteractionComponent>("InteractionComp");
	
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AARCharacter::MoveForward(float Value)
{
	// break if..
	if (Controller==nullptr || Value==0.0f) {return;}
	

	const FRotator ControlRot = GetControlRotation();
	const FRotator ControlYaw(0, ControlRot.Yaw, 0);
	const FVector ControlForward = FRotationMatrix(ControlYaw).GetUnitAxis(EAxis::X);

	AddMovementInput(ControlForward, Value);
}

void AARCharacter::MoveRight(float Value)
{
	// break if..
	if (Controller==nullptr || Value==0.0f) {return;}

	// do the thing lmao
	const FRotator ControlRot = GetControlRotation();
	const FRotator ControlYaw(0, ControlRot.Yaw, 0);
	const FVector ControlRight = FRotationMatrix(ControlYaw).GetUnitAxis(EAxis::Y);

	AddMovementInput(ControlRight, Value);
}

void AARCharacter::PrimaryAttack()
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	const FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void AARCharacter::Interact()
{
	if (!InteractionComp) {return;}
	InteractionComp->PrimaryInteract();
}


// Called every frame
void AARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AARCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AARCharacter::Interact);
}

