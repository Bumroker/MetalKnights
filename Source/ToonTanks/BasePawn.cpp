// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction(){
	if(EsplosionParticles){UGameplayStatics::SpawnEmitterAtLocation(this, EsplosionParticles, this->GetActorLocation(), this->GetActorRotation());}
	if(DeathSound){UGameplayStatics::SpawnSoundAtLocation(this,DeathSound,this->GetActorLocation());}
	if(DeathCameraShakeClass){GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);}
}

void ABasePawn::RotateTurret(FVector LookAtTarget){
	FVector ToTarget=LookAtTarget-TurretMesh->GetComponentLocation();
	FRotator LookAtRotation(0,ToTarget.Rotation().Yaw,0);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 25));

}

void ABasePawn::Fire(){
	FVector Location = SpawnPoint->GetComponentLocation();
	FRotator Rotation = SpawnPoint->GetComponentRotation();
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location, Rotation);
	Projectile->SetOwner(this);
	

}