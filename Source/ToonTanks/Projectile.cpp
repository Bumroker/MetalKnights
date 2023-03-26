// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AProjectile::AProjectile()
{
 	// dont need a tick
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticlesComponent"));
	TrailParticles->SetupAttachment(RootComponent);
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MovementComponent->MaxSpeed=1300;
	MovementComponent->InitialSpeed=1300;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if(ShootSound){UGameplayStatics::SpawnSoundAtLocation(this,ShootSound,this->GetActorLocation());}
	if(HitParticles){UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, this->GetActorLocation(), this->GetActorRotation());}	


}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	auto MyOwner= GetOwner();

	if (MyOwner==nullptr){
		Destroy();
		return;
	}
	

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DmgTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor!=this && OtherActor!=MyOwner){
		UGameplayStatics::ApplyDamage(OtherActor, Dmg, MyOwnerInstigator, this, DmgTypeClass);
		if(HitParticles){UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, this->GetActorLocation(), this->GetActorRotation());}	
		if(HitSound){UGameplayStatics::SpawnSoundAtLocation(this,HitSound,this->GetActorLocation());}
		if(HitCameraShakeClass){GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);}
	}
	Destroy();
}
