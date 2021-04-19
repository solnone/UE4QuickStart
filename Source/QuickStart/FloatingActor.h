// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FloatingActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class QUICKSTART_API AFloatingActor : public AActor
{
	GENERATED_BODY()

private:
	float TickTime = 0.0f;

public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	/** Scale our height by a factor of FloatSpeed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
	float FloatSpeed = 20.0f;

	/**  Rotate by RotationSpeed degrees per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
	float RotationSpeed = 20.0f;

	/** Array of vector, Please add points. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Category|Sub", meta=(DisplayName="Points (Vector)"))
	TArray<FVector> Points;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Move(FVector Offset);
};
