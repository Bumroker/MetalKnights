// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "Calculatriz.h"

// Sets default values
AProyectil::AProyectil()
{
 	// dont need a tick
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticlesComponent"));
	TrailParticles->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);
	if(ShootSound){UGameplayStatics::SpawnSoundAtLocation(this,ShootSound,this->GetActorLocation());}
	if(HitParticles){UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, this->GetActorLocation(), this->GetActorRotation());}	
}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Movement(DeltaTime);
}
void AProyectil::Movement(float DeltaTime)
{
	FVector DeltaLocation(0);
    DeltaLocation.X=Speed*DeltaTime;
    AddActorLocalOffset(DeltaLocation, true);
}



void AProyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	auto MyOwner= GetOwner();

	if (MyOwner==nullptr){
		Destroy();
		return;
	}
	

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DmgTypeClass = UDamageType::StaticClass();
	if(Rebote){
		if(OtherActor && OtherActor!=this && OtherActor!=MyOwner){
			if(!OtherActor->ActorHasTag(StandardPawnTag)){
				BounceV2(Hit.ImpactNormal);
				return;
			}
			UGameplayStatics::ApplyDamage(OtherActor, Dmg, MyOwnerInstigator, this, DmgTypeClass);
			if(HitParticles){UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, this->GetActorLocation(), this->GetActorRotation());}	
			if(HitSound){UGameplayStatics::SpawnSoundAtLocation(this,HitSound,this->GetActorLocation());}
			if(HitCameraShakeClass){GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);}
		}
	}
	
	Destroy();
}

