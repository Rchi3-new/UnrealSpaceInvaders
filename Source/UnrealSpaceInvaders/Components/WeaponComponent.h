#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFire);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALSPACEINVADERS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
        UWeaponComponent();

        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void StartFiring();

        UFUNCTION(BlueprintCallable, Category = "Weapon")
        void StopFiring();

       UFUNCTION(BlueprintCallable, Category = "Weapon")
       void FireOnce();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "0.1"))
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector SpawnOffset;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float ProjectileSpeed;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float ProjectileMaxSpeed;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        bool bRotationFollowsVelocity;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
        float ProjectileGravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bFireUpwards;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnFire OnFire;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle FiringTimerHandle;
	void Fire();
};
