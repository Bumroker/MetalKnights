// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_GoRND.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Tank.h"

UBTTask_GoRND::UBTTask_GoRND()
{
    NodeName=("Go for a walk");
}
EBTNodeResult::Type UBTTask_GoRND::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);
    ATank* Enemy = Cast<ATank>(OwnerComp.GetAIOwner()->GetPawn());
    FVector EnemyLocation=Enemy->GetActorLocation();
    
    //Variable a rellenar 
    auto BBKey = OwnerComp.GetBlackboardComponent();

    if(Enemy==nullptr || BBKey==nullptr)return EBTNodeResult::Failed;
    FNavLocation NavMesh;
    UNavigationSystemV1* NavSystem=UNavigationSystemV1::GetCurrent(GetWorld());

    auto NewLocation = NavSystem->GetRandomPointInNavigableRadius( 
                        EnemyLocation, 
                        SearchLocationRadious,
                        NavMesh
                    );
    BBKey->SetValueAsVector(RndLocationKey.SelectedKeyName, NavMesh.Location);
    return EBTNodeResult::Succeeded;
}