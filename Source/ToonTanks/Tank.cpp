// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank(){



}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	bAlive=true;
    TankPlayerController=Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController){
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }

}
void ATank::HandleDestruction(){
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive=false;
}


