// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);


private:
	float CurrentYaw;
	UPROPERTY(EditAnywhere)
	float InitialYaw;
	UPROPERTY(EditAnywhere)
	float TargetYaw=115.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float DoorOpenTime=1.5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseTime = 3.f;

	UPROPERTY(EditAnywhere)
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorClosedDelay = 2.f;



		
};
