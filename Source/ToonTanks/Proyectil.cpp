// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Calculatriz.h"

// Sets default values
AProyectil::AProyectil()
{
 	// dont need a tick
	PrimaryActorTick.bCanEverTick = false;

	ProjectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectilMesh;
	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(ProjectilMesh);
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticlesComponent"));
	TrailParticles->SetupAttachment(ProjectilMesh);
	
	

}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();
	ProjectilMesh->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);
	if(ShootSound){UGameplayStatics::SpawnSoundAtLocation(this,ShootSound,this->GetActorLocation());}
	if(HitParticles){UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, SpawnPoint->GetComponentLocation(), this->GetActorRotation());}	
	GetWorldTimerManager().SetTimer(LockOffTimerHandle, this, &AProyectil::EnableBullet, 0.2f, false);
}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!Destroyed) Movement(DeltaTime);
}
void AProyectil::Movement(float DeltaTime)
{
	FVector DeltaLocation(0);
    DeltaLocation.X=Speed*DeltaTime;
    AddActorLocalOffset(DeltaLocation, true);
}



void AProyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	auto MyOwner= GetOwner();
	if(Destroyed)return;
	if (MyOwner==nullptr){
		Destroy();
		return;
	}
	

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DmgTypeClass = UDamageType::StaticClass();
	if(OtherActor && OtherActor!=this && OtherActor!=MyOwner){
		//Gestion de rebote
		if(!OtherActor->ActorHasTag(StandardPawnTag) && !OtherActor->ActorHasTag(StandardProjectilTag) && Rebotes!=MaxRebotes && Rebote){
			Rebotes++;
			BounceV2(Hit.ImpactNormal);
			return;
		}
		//Efectos
		if(HitParticles){UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, this->GetActorLocation(), this->GetActorRotation());}	
		if(HitSound){UGameplayStatics::SpawnSoundAtLocation(this,HitSound,this->GetActorLocation());}
		if(HitCameraShakeClass){GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);}
		//Damages
		if(!OtherActor->ActorHasTag(TeamTag)){UGameplayStatics::ApplyDamage(OtherActor, Dmg, MyOwnerInstigator, this, DmgTypeClass);}

	}else if(EnabledBullet){Destroy();}
	ProjectilMesh->SetHiddenInGame(true);
	ProjectilMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	Destroyed=true;
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AProyectil::Explode, DestroyTime, false);
}


