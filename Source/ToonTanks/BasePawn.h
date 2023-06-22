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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool AutoAim=false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USceneComponent* SpawnPoint;
	
private:

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* EsplosionParticles;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProyectil> ProyectilClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* DeathSound;

	FRotator CleanRotation(FRotator ActualRotation);

	UPROPERTY()
	float TurretAngleThreshhold=45;
	UPROPERTY()
	float RotateDirection=1;

public:
	UPROPERTY(VisibleAnywhere)
	bool bAlive;
	
	UFUNCTION(BlueprintCallable)
	void RotateTurret(FVector LookAtTarget);	

	UFUNCTION(BlueprintCallable)
	void PivotTurret();

	UFUNCTION(BlueprintCallable)
	FVector Fire(bool Rebote=false);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float CalculateSpeed(float Direction, float NavigationSpeed=800, float Slow=1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats");
	float MovementSpeed=800;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats");
	float RotationSpeed=360;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats");
	int AILevel=1;

};
