// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_ToonTanks.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "BasePawn.h"
#include "TTPlayerController.h"



void AGM_ToonTanks::BeginPlay(){
	Super::BeginPlay();

    HandleGameStart();
	
}
void AGM_ToonTanks::ActorDied(AActor* DeadActor){
	UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *DeadActor->GetName());
    bool isEnemy=false;
    for(AActor* Enemy : Enemys){
        if(DeadActor==Enemy)isEnemy=true;
    }
	UE_LOG(LogTemp, Warning, TEXT("Is Enemy? %s"), ( isEnemy ? TEXT("true") : TEXT("false") ));
    if(isEnemy){
        if(ABasePawn* DestroyedEnemy=Cast<ABasePawn>(DeadActor)){
            DestroyedEnemy->HandleDestruction();
            TargetEnemys--;
        UE_LOG(LogTemp, Warning, TEXT("Left Enemies: %i"), TargetEnemys);
        }
        if(TargetEnemys==0){
            GameOver(true);
        }
    }else{
        ABasePawn* Player=Cast<ABasePawn>(DeadActor);
        Player->HandleDestruction();
        if(TankPC){
            TankPC->SetPlayerEnabledState(false);
            TankPC->SetActorHiddenInGame(true);
            TankPC->SetActorTickEnabled(false);
            Player->bAlive=false;
        }
    }
    /*if(DeadActor==Tank){
        Tank->HandleDestruction();
        if(TankPC){
            TankPC->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }else if(ATower* DestroyedTower=Cast<ATower>(DeadActor)){
        DestroyedTower->HandleDestruction();
        TargetEnemys--;
        UE_LOG(LogTemp, Warning, TEXT("Left Enemies: %i"), TargetEnemys);

        if(TargetEnemys==0){
            GameOver(true);
        }
    }*/
}

void AGM_ToonTanks::HandleGameStart(){
    TargetEnemys = GetTargetTowerCount();
    UE_LOG(LogTemp, Warning, TEXT("Left Enemies: %i"), TargetEnemys);

    //CAMBIAR PARA EL MULTIPLAYER
    //Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    //CAMBIAR PARA EL MULTIPLAYER
    //CAMBIAR PARA EL MULTIPLAYER
    TankPC= Cast<ATTPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    //CAMBIAR PARA EL MULTIPLAYER

    TankPC->SetPlayerEnabledState(true);
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
    UGameplayStatics::GetAllActorsWithTag(this, "Enemy",Enemys);
    return Enemys.Num();
}