#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Proyectil.generated.h"

UCLASS()
class TOONTANKS_API AProyectil : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProyectil();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:

	UPROPERTY(EditAnywhere)
	FName StandardPawnTag="Pawn";

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	
	

	UFUNCTION()
	void Movement(float DeltaTime);
	UFUNCTION()
	void Bounce(FVector HitNormal);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed=1300;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Dmg=50;

	UPROPERTY(EditAnywhere, Category="Combat")
	bool Rebote;
	void SetRebote(bool Reicochet){Rebote=Reicochet;}

	UFUNCTION(BlueprintImplementableEvent)
	void BounceV2(FVector HitWall);

};
