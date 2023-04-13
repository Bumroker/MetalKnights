// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Calculatriz.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UCalculatriz : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static float GetBounceAngle(FVector Alpha,FVector Beta);
	UFUNCTION(BlueprintCallable)
	static float GetVectorsAngle(FVector Alpha,FVector Beta);
	UFUNCTION(BlueprintCallable)
	static double DotProduct(FVector A,FVector B);
	UFUNCTION(BlueprintCallable)
	static double GetVectorMagnitude(FVector Vector3D);
};
