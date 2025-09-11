// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam")); // Create a camera component

	PlayerCamComp->SetupAttachment(GetMesh(), "head"); // Attach the camera to the "head" socket of the character's mesh

	PlayerCamComp->bUsePawnControlRotation = true; // Allow the camera to rotate based on the controller's rotation

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward); // Bind the "MoveForward" axis to the MoveForward function
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight); // Bind the "MoveRight" axis to the MoveRight function
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput); // Bind the "LookUp" axis to control pitch
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput); // Bind the "Turn" axis to control yaw
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump); // Bind the "JumpEvent" action to start jumping
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump); // Bind the "JumpEvent" action to stop jumping

}

// Movement functions
void APlayerChar::MoveForward(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X); // Get the direction based on the controller's rotation
	AddMovementInput(Direction, axisValue);
}

// Move the character right/left
void APlayerChar::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y); // Get the direction based on the controller's rotation
	AddMovementInput(Direction, axisValue);
}

// Jump functions
void APlayerChar::StartJump()
{
	bPressedJump = true;
}

// Stop jumping
void APlayerChar::StopJump()
{
	bPressedJump = false;
}

// Function to find an object (WIP)
void APlayerChar::FindObject()
{
}

