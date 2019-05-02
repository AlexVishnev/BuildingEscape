// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include <list>
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	bool DoorIsOpen(FString name);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:

	void	ChangeDoorState(FString name, bool bDoorIsOpen, float AnimationDelay);
	void	CreateAnimationForDoorStates();


	std::list <FRotator> OpenStates;
	std::list <FRotator> CloseStates;
	
	FRotator CloseState;
	FRotator OpenState;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay;

	float LastOpenTimeDoor;

	AActor *ActorThatOpen;
	AActor *Owner;
	
};
