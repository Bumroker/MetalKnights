// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"



UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();


	void HandleDestruction();
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USceneComponent* SpawnPoint;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* EsplosionParticles;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProyectil> ProyectilClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* DeathSound;

	

public:

	UFUNCTION(BlueprintCallable)
	void RotateTurret(FVector LookAtTarget);	

	UFUNCTION(BlueprintCallable)
	FVector Fire(bool Rebote=false);


	
};
