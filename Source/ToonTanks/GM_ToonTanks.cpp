// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_ToonTanks.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "TTPlayerController.h"



void AGM_ToonTanks::BeginPlay(){
	Super::BeginPlay();

    HandleGameStart();
	
}
void AGM_ToonTanks::ActorDied(AActor* DeadActor){
    if(DeadActor==Tank){
        Tank->HandleDestruction();
        if(TankPC){
            TankPC->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }else if(ATower* DestroyedTower=Cast<ATower>(DeadActor)){
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        UE_LOG(LogTemp, Warning, TEXT("Left Enemies: %i"), TargetTowers);

        if(TargetTowers==0){
            GameOver(true);
        }
    }
}

void AGM_ToonTanks::HandleGameStart(){
    TargetTowers = GetTargetTowerCount();
    UE_LOG(LogTemp, Warning, TEXT("Left Enemies: %i"), TargetTowers);
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TankPC= Cast<ATTPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

//Timer antes de empezar a jugar

    /*StartGame();
    if(TankPC){
        TankPC->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTH;
        FTimerDelegate PlayerEnableTD=FTimerDelegate::CreateUObject(TankPC, &ATTPlayerController::SetPlayerEnabledState, true);
        GetWorldTimerManager().SetTimer(PlayerEnableTH,PlayerEnableTD,StartDelay,false);

    }*/
}
int32 AGM_ToonTanks::GetTargetTowerCount(){
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(),Towers);
    return Towers.Num();
}