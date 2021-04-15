// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// StaticMesh
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Engine/MapTemplates/Sky/Desert_Outer_HDR_Mat.Desert_Outer_HDR_Mat"));
		if (FoundMaterial.Succeeded())
		{
			VisualMesh->SetMaterial(0, FoundMaterial.Object);
		}
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	if (Points.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No points data"));
		Points.Add(FVector(1.0f, 2.0f, 3.0f));
	}

	UE_LOG(LogTemp, Display, TEXT("Points Length = %d"), Points.Num());
	for (FVector vector : Points)
	{
		UE_LOG(LogTemp, Display, TEXT("Point (%f, %f, %f)"), vector.X, vector.Y, vector.Z);
	}

	// Show Float Speed and Rotation Speed
	UE_LOG(LogTemp, Display, TEXT("Float Speed = %f, Rotation Speed = %f"), FloatSpeed, RotationSpeed);
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;		 // Scale our height by a factor of FloatSpeed
	float DeltaRotation = DeltaTime * RotationSpeed; // Rotate by RotationSpeed degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%f: Location(%f, %f, %f)"), GetWorld()->TimeSeconds, NewLocation.X, NewLocation.Y, NewLocation.Z));
	}
}
