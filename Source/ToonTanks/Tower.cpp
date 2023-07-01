// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
    Tank=Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

    //GetWorldTimerManager().SetTimer(CadenceTimerHandle, this, &ATower::CheckFireCondition, Cadence, true);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    /*
    if(InFireRange()){
        RotateTurret(Tank->GetActorLocation());
    }*/
}


void ATower::CheckFireCondition(){
    if (Tank==nullptr) return;
    if(InFireRange() && Tank->Alive){
        Fire();
    }
}

bool ATower::InFireRange(){
    if(Tank){
        // Distancia<=FireRange
        if(FVector::Dist(GetActorLocation(), Tank->GetActorLocation())<=FireRange){
            return true;
        }
    }
    return false;
}