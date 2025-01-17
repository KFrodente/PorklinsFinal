// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWorldCamera::AWorldCamera()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2500;
	Camera->bAutoCalculateOrthoPlanes = true;
	Camera->bUpdateOrthoPlanes = true;
}

// Called when the game starts or when spawned
void AWorldCamera::BeginPlay()
{
	Super::BeginPlay();
	FollowPlayer = true;
	Camera->SetOrthoWidth(CurrentWantedZoom);
	PlayerRef = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AWorldCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DT = GetWorld()->GetDeltaSeconds();

	if (FollowPlayer)
	{
		SetActorLocation(FVector
			( FMath::FInterpTo(GetActorLocation().X, PlayerRef->GetActorLocation().X, DT, HorizontalLerpTime)  //set camera x position
			, 100.0f
			, FMath::FInterpTo(GetActorLocation().Z, PlayerRef->GetActorLocation().Z, DT, VerticalLerpTime))); //set camera z position
		
		SetActorRotation(FRotator(0.0f, -90 - FMath::FInterpTo(GetActorRotation().Pitch, 0.0f, DT, 15.0f), 0.0f));

		Camera->SetOrthoWidth(FMath::FInterpTo(Camera->OrthoWidth, 2500, DT, 15));
	}
	else
	{
		SetActorLocation(FVector
			( FMath::FInterpTo(GetActorLocation().X, CurrentWantedPosition.X, DT, HorizontalLerpTime)  //set camera x position
			, 100.0f
			, FMath::FInterpTo(GetActorLocation().Z, CurrentWantedPosition.Z, DT, VerticalLerpTime))); //set camera z position
		
		SetActorRotation(FRotator(0.0f, -90 - FMath::FInterpTo(GetActorRotation().Pitch, CurrentWantedRotation, DT, 3), 0.0f));

		Camera->SetOrthoWidth(FMath::FInterpTo(Camera->OrthoWidth, CurrentWantedZoom, DT, 15));
	}

}

void AWorldCamera::GiveWantedValues(FVector playerLocation, FVector enemyLocation, float wantedZoom)
{
	CurrentWantedPosition = (playerLocation + enemyLocation) * 0.5f;

	CurrentWantedRotation = UKismetMathLibrary::FindLookAtRotation(playerLocation, enemyLocation).Yaw;

	if (playerLocation.X - enemyLocation.X < 0) CurrentWantedRotation *= -1;

	CurrentWantedZoom = wantedZoom;
}


