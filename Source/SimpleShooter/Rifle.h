// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

class UParticleSystem;

UCLASS()
class SIMPLESHOOTER_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent *Root;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent *Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Particle Effects")
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditDefaultsOnly, Category = "Particle Effects")
	UParticleSystem *ImpactFlash;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;
};
