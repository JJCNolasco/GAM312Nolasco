// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera component
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	// Attach the camera to the "head" socket of the character's mesh
	PlayerCamComp->SetupAttachment(GetMesh(), "head");

	// Allow the camera to rotate based on the controller's rotation
	PlayerCamComp->bUsePawnControlRotation = true;

	ResourcesArray.SetNum(3); // Set the size of the resources array to 3
	ResourcesNameArray.Add(TEXT("Wood")); // Add "Wood" to the resources name array
	ResourcesNameArray.Add(TEXT("Stone")); // Add "Stone" to the resources name array
	ResourcesNameArray.Add(TEXT("Berry")); // Add "Berry" to the resources name array

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle StatsTimerHandle; // Declare a timer handle
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerChar::DecreasesStats, 2.0f, true); // Set a timer to decrease stats every 2 seconds

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
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject); // Bind the "Interact" action to the FindObject function

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

// Function to find an object
void APlayerChar::FindObject()
{
	FHitResult HitResult; // Variable to store the hit result
	FVector StartLocation = PlayerCamComp->GetComponentLocation(); // Get the camera's location
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f; // Get the camera's forward vector 800 units ahead
	FVector EndLocation = StartLocation + Direction; // Calculate the end location for the line trace

	FCollisionQueryParams QueryParams; // Parameters for the line trace
	QueryParams.AddIgnoredActor(this); // Ignore the player character in the trace
	QueryParams.bTraceComplex = true; // Allow complex collision tracing
	QueryParams.bReturnFaceIndex = true; // Return the face index in the hit result

	// Perform the line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor()); // Check if the hit actor is of type AResource_M

		// Check if the player has enough stamina to collect the resource
		if (Stamina > 5.0f)
		{
			if (HitResource)
			{
				FString hitName = HitResource->resourceName; // Get the resource name
				int resourceValue = HitResource->resourceAmount; // Get the resource amount

				HitResource->totalResource = HitResource->totalResource - resourceValue; // Decrease the total resources by the resource amount

				if (HitResource->totalResource > resourceValue) // Check if there are enough resources left
				{
					GiveResource(resourceValue, hitName); // Give the player the resource

					check(GEngine != nullptr); // Ensure GEngine is valid
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected")); // Display a message indicating the resource gained

					UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f); // Spawn a decal at the hit location

					SetStamina(-5.0f); // Decrease stamina by 5
				}
				else
				{
					HitResource->Destroy(); // Destroy the resource actor if depleted
					check(GEngine != nullptr); // Ensure GEngine is valid
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted")); // Display a message indicating the resource is depleted
				}
			}
		}

	}
}

// Player stats functions
void APlayerChar::SetHealth(float amount)
{
	if (Health + amount >= 100.0f)
	{
		Health = 100.0f;
	}
	else if (Health + amount <= 0.0f)
	{
		Health = 0.0f;
	}
	else
	{
		Health += amount;
	}
}

void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount >= 100.0f)
	{
		Hunger = 100.0f;
	}
	else if (Hunger + amount <= 0.0f)
	{
		Hunger = 0.0f;
	}
	else
	{
		Hunger += amount;
	}
}

void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount >= 100.0f)
	{
		Stamina = 100.0f;
	}
	else if (Stamina + amount <= 0.0f)
	{
		Stamina = 0.0f;
	}
	else
	{
		Stamina += amount;
	}
}

// Function that decreases stats over time
void APlayerChar::DecreasesStats()
{
	if (Hunger > 0.0f)
	{
		SetHunger(-1.0f);
	}

	SetStamina(10.0f);

	if (Hunger <= 0.0f)
	{
		SetHealth(-3.0f);
	}
}

// Function to give resources based on type
void APlayerChar::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")
	{
		ResourcesArray[0] += amount;
	}

	if (resourceType == "Stone")
	{
		ResourcesArray[1] += amount;
	}

	if (resourceType == "Berry")
	{
		ResourcesArray[2] += amount;
	}
}

