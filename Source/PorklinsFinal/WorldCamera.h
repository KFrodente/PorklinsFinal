// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldCamera.generated.h"

UCLASS()
class PORKLINSFINAL_API AWorldCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* PlayerRef = nullptr;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentWantedPosition{ 0,0,0 };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentWantedRotation = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentWantedZoom = 2500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalLerpTime = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalLerpTime = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FollowPlayer = true;

	FVector ShakeWantedPosition{ 0,0,0 };
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GiveWantedValues(FVector playerLocation, FVector enemyLocation, float wantedZoom);


private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

};
