// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define OUT

ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void ARifle::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return;
	}
	AController *OwnerController = OwnerPawn->GetController();
	if (!OwnerController)
	{
		return;
	}

	FVector PlayerLocation;
	FRotator PlayerRotation;
	OwnerController->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	FVector End = PlayerLocation + PlayerRotation.Vector() * MaxRange;
	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerLocation, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess)
	{
		FVector ShotDirection = PlayerRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, Hit.Location, ShotDirection.Rotation());
		AActor *HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

