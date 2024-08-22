// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrappleComponent::UGrappleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrappleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UGrappleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FHitResult UGrappleComponent::ShootHook(FVector mouseLocation, FVector mouseDirection, FVector actorLocation, EObjectTypeQuery rayWallCheck, EObjectTypeQuery staticCheck, EObjectTypeQuery dynamicCheck)
{
	FHitResult rayWallHit;
	FHitResult anythingElseHit;
	
	GetWorld()->LineTraceSingleByObjectType(rayWallHit, mouseLocation, mouseDirection, rayWallCheck);
	GetWorld()->LineTraceSingleByObjectType(anythingElseHit, actorLocation, FVector(rayWallHit.ImpactPoint.X, 0, rayWallHit.ImpactPoint.Z), staticCheck);

	if (!anythingElseHit.HasValidHitObjectHandle())
	{
		GetWorld()->LineTraceSingleByObjectType(anythingElseHit, actorLocation, FVector(rayWallHit.ImpactPoint.X, 0, rayWallHit.ImpactPoint.Z), dynamicCheck);
	}

	return rayWallHit;
	//return anythingElseHit;
}

FVector UGrappleComponent::GetLaunchDirection(FVector head, FVector tail, float power)
{
	FVector direction = head - tail;
	direction.Normalize();
	direction *= power;

	return direction;
}
