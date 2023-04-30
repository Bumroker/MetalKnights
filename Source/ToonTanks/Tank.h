// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }
	
	UPROPERTY(VisibleAnywhere)
	bool bAlive;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool AutoAim=false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess="true"));
	float Speed=800;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats", meta=(AllowPrivateAccess="true"));
	//float RotationSpeed=200;
	//void Move(float Value);
	//void Rotate(float Value);

	APlayerController* TankPlayerController;

};
