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
#ifdef DEBUG
	
	 UE_LOG(LogTemp, Warning, TEXT("GRAAAB %s"), *GetOwner()->GetName())
#endif // DEBUG

	auto HitResult 			= GetFirstPhysicsBodyInReach();
	auto ComponentToGrab	= HitResult.GetComponent(); //getting mesh
	auto ActorHit 			= HitResult.GetActor();
	
	if (ActorHit != nullptr)
	{
		if (!PhysicsHandle)
			return ;
 		PhysicsHandle->GrabComponentAtLocationWithRotation(
						ComponentToGrab, 
						NAME_None, 
						ComponentToGrab->GetOwner()->GetActorLocation(), 
						ComponentToGrab->GetOwner()->GetActorRotation()
						);
	}
}

void UGrabber::Release()
{
#ifdef DEBUG
	UE_LOG(LogTemp, Warning, TEXT("THROW %s"), *GetOwner()->GetName())
#endif // DEBUG

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
		UE_LOG(LogTemp, Error, TEXT("%s missing UPhysicsHandleComponent"), *GetOwner()->GetName())
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

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

FVector UGrabber::GetReachLineStart() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
#ifdef DEBUG
 DrawDebugLine(World, PlayerViewPointLocation, GetReachLineEnd(), \
	 			 FColor::Red, false, 0.f, 0.f, 10.f);
#endif // DEBUG
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner()); 

	FVector Start = GetReachLineStart(); 
	FVector End   = GetReachLineEnd();
	GetWorld()->LineTraceSingleByObjectType( Hit, Start, End,
					FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
					TraceParams
					);
#ifdef DEBUG

	AActor *ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit : %s"), *(ActorHit->GetName()));
	}
#endif // DEBUG	
	return Hit;
}
