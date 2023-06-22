// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GM_ToonTanks.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	ToonTanksGM = Cast<AGM_ToonTanks>(UGameplayStatics::GetGameMode(this));

	Health=MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DmgTaken);
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DmgTaken(AActor* DamagedActor, float Dmg, const UDamageType* DmgType, class AController* Instigator, AActor* DmgCauser){	
	if(Invencible)return;
	if(Dmg<=0 || Health<=0)return;
	Health-=Dmg;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	if(Health<=0 && ToonTanksGM){
		ToonTanksGM->ActorDied(DamagedActor);
	}
}
