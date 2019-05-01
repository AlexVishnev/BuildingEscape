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

void UOpenDoor::ChangeDoorState(bool is_open)
{
	if (Owner)
		Owner->SetActorRotation(is_open ? OpenState : CloseState);


}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner			= GetOwner();
	ActorThatOpen	= GetWorld()->GetFirstPlayerController()->GetPawn();

	OpenState		= FRotator(0.0f, 90.0f, 0.0f);
	CloseState		= FRotator(0.0f, 0.0f, 0.0f);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen)){
		PRINT("COLLISION");
		ChangeDoorState(true);
		LastOpenTimeDoor =  GetWorld()->GetTimeSeconds();
	
	}

	if (GetWorld()->GetTimeSeconds() - LastOpenTimeDoor > DoorCloseDelay)
		ChangeDoorState(false);

	// ...
}

