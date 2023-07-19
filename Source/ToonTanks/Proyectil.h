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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	UStaticMeshComponent* ProjectilMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	class UParticleSystemComponent* TrailParticles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	class USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	class USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StandardPawnTag="Pawn";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName TeamTag="Enemy";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StandardProjectilTag="Projectil";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DestroyTime=0.7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxRebotes=2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:

	int Rebotes=0;

	UFUNCTION()
	void Movement(float DeltaTime);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	FTimerHandle DestroyTimerHandle;
	FTimerHandle LockOffTimerHandle;
	bool Destroyed;
	void Explode(){Destroy();}
	bool EnabledBullet;
	void EnableBullet(){EnabledBullet=true;}


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed=1300;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Dmg=50;

	UPROPERTY(EditAnywhere, Category="Combat")
	bool Rebote;
	void SetRebote(bool Reicochet, int RebotesMax){Rebote=Reicochet; MaxRebotes=RebotesMax;}


	UFUNCTION(BlueprintImplementableEvent)
	void BounceV2(FVector HitWall);
	UFUNCTION(BlueprintImplementableEvent)
	void AutoDestroy();

};
