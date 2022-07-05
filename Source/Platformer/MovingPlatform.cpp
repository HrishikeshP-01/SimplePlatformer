// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	CurrentLocation = StartLocation;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calculate current location
	CurrentLocation += velocity * DeltaTime;
	SetActorLocation(CurrentLocation);

	// Check if distance moved hasn't exceeded target distance
	float distanceMoved = FVector::Dist(CurrentLocation, StartLocation);
	if (distanceMoved > distance) 
	{
		/* We want the platform to move back to StartLocation
			if we had omitted the next statement then the platform would have moved back and forth
			to avoid that and in order for the platform to move back to original StartLocation we set the new 
			StartLocation to the current endpoint.
			Then we change the velocity so that the platform moves to the opposite endpoint.
			Once it reaches the opposite endpoint the StartLocation is set to that endpoint. */
		StartLocation = StartLocation + velocity.GetSafeNormal() * distance;

		velocity = -velocity;

		/* Due to varied frame rate there could be an overshoot in distance moved
		so if CurrentLocation exceeds endpoint location it's set to StartLocation
		as the new StartLocation stores the current endpoint location*/
		CurrentLocation = StartLocation;
		SetActorLocation(CurrentLocation);
	}
}

