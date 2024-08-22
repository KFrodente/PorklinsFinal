// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrappleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORKLINSFINAL_API UGrappleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrappleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Grapple Functions")
	FHitResult ShootHook(FVector mouseLocation, FVector mouseDirection, FVector actorLocation, EObjectTypeQuery rayWallCheck, EObjectTypeQuery staticCheck, EObjectTypeQuery dynamicCheck);

	UFUNCTION(BlueprintCallable)
	FVector GetLaunchDirection(FVector head, FVector tail, float power);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	const TArray<AActor*> ActorsToIgnore;
};
