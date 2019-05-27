// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Defines.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void	UOpenDoor::CreateAnimationForDoorStates()
{
	for (size_t i = 0; i < 90; i+= 2.5f)
	{
		OpenStates.push_back(FRotator(0.f, i, 0.f));
		CloseStates.push_back(FRotator(0.f, 90.f - i, 0.f));
	}
}

bool UOpenDoor::DoorIsOpen(FString name)
{
	return true;
}

void UOpenDoor::ChangeDoorState(FString name, bool bDoorIsOpen, float AnimationDelay)
{
//	if (Owner)
//		Owner->SetActorRotation(bDoorIsOpen ? OpenState : CloseState); //

	if (bDoorIsOpen)
	{
		for (auto State: OpenStates)
		{
			if (Owner)
			{
				Owner->SetActorRotation(State);
			}
		}
	}
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner			= GetOwner();
	ActorThatOpen	= GetWorld()->GetFirstPlayerController()->GetPawn();

	OpenState		= FRotator(0.0f, 90.0f, 0.0f);
	CloseState		= FRotator(0.0f, 0.0f, 0.0f);

	CreateAnimationForDoorStates();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		PRINT("COLLISION DOOR IS OPEN");
		ChangeDoorState("", OPENDOOR, GetWorld()->GetTimeSeconds() - LastOpenTimeDoor);
		LastOpenTimeDoor = GetWorld()->GetTimeSeconds();
	}

	//close door after delay
	if (GetWorld()->GetTimeSeconds() - LastOpenTimeDoor > DoorCloseDelay) 
	{
		ChangeDoorState("",CLOSEDOOR, GetWorld()->GetTimeSeconds() - LastOpenTimeDoor);
		//PRINT("TIMES OUT door is closed");
	}
}

