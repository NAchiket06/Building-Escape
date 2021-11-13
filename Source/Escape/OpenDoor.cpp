// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include <GameFramework/Actor.h>

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/*
		START	
*/
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	GetAudioComponent();

	if(!PressurePlate)
	{
		UE_LOG(LogTemp,Error,TEXT("%s has no pressure plate set"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

	if (TotalMassOfActors() > MassToOpenDoors)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		DoorAudio->Play();
	}

	if(DoorLastOpened + DoorClosedDelay < GetWorld()->GetTimeSeconds()) 
	{
		CloseDoor(DeltaTime);
		DoorAudio->Play();

	}
	
}

void UOpenDoor::GetAudioComponent()
{
	DoorAudio = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!DoorAudio)
	{
		UE_LOG(LogTemp, Error, TEXT("No audio component on %s."), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw,TargetYaw, DeltaTime* DoorOpenTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw,InitialYaw, DeltaTime* DoorCloseTime);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	if (!PressurePlate)
	{
		return 0.f;
	}
	float TotalMass = 0.f;

	// Find all overlapping actors in the collider volume
	TArray<AActor*> OverlappingActors;
	
	PressurePlate->GetOverlappingActors(OverlappingActors);
	// Add up the masses 
	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}


