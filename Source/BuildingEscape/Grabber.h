// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	//Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	// Ray-cast and grab /release object in reach
	void Grab();
	void Release();

	// Return current end for reach line
	FVector GetReachLineEnd() const ;

	// Return current start for reach line
	FVector GetReachLineStart() const ;

	// Find attached Physics Handle
	void FindPhysicsHandleComponent();

	// Find atteched input component
	void SetupInputComponent();

	// Hit for first physics body in reach

	FHitResult GetFirstPhysicsBodyInReach() const;

private:
	// lentgh of ray castS
	float Reach = 100.f;
	
	UWorld const *World;


	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;
	
};
