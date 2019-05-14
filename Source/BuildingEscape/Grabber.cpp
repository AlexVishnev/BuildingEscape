// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab(){
	UE_LOG(LogTemp, Warning, TEXT("Input component found %s"), *GetOwner()->GetName() )
}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

			/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)	
	{
		// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{

		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(World, PlayerViewPointLocation, LineTraceEnd, \
				 FColor::Red, false, 0.f, 0.f, 10.f);

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner()); 


	FHitResult Hit;
	World->LineTraceSingleByObjectType(Hit, PlayerViewPointLocation, 
			LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
			);
			
	AActor *ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit : %s"), *(ActorHit->GetName()));
	}
}

