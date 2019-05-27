// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include <vector>

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRAAAB %s"), *GetOwner()->GetName())

	auto HitResult 			= GetFirstPhysicsBodyInReach();
	auto ComponentToGrab	= HitResult.GetComponent(); //getting mesh
	auto ActorHit 			= HitResult.GetActor();
	
	if (ActorHit != nullptr)
	{
		if (!PhysicsHandle)
			return ;
 		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, 
									 ComponentToGrab->GetOwner()->GetActorLocation(), 
									 true);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("THROW %s"), *GetOwner()->GetName())

	if (!PhysicsHandle)
		return;
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
	// ...
}


void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}

}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	FindPhysicsHandleComponent();
	SetupInputComponent();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// if (PhysicsHandle->GrabbedComponent)
	// {
	// 	PhysicsHandle->SetTargetLocation(LineTraceEnd);
	// }
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// DrawDebugLine(World, PlayerViewPointLocation, LineTraceEnd, \
	// 			 FColor::Red, false, 0.f, 0.f, 10.f);

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
	return Hit;
}