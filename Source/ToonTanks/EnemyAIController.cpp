// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"


void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(AIBehavior!=nullptr){
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), GetPawn()->GetActorLocation());
    }

}
