// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/AudioComponent.h"
#include "PowerUpObject.h"
#include "BountyDashCharacter.generated.h"


UCLASS()
class BOUNTYDASH_API ABountyDashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABountyDashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// �̵� ���� �迭
	UPROPERTY(EditAnywhere, Category = Logic)
		TArray<class ATargetPoint*> TargetArray;

	// ĳ���� �� �ٲ� �ӵ� 
	UPROPERTY(EditAnywhere, Category = Logic)
		float CharSpeed;

	// �浹 ���带 ���� ����� ������Ʈ
	UPROPERTY(EditAnywhere, Category = Sound)
		UAudioComponent* hitObstacleSound;

	// ���� ȹ�� ���带 ���� ����� ������Ʈ
	UPROPERTY(EditAnywhere, Category = Sound)
		UAudioComponent* dingSound;

	void PowerUp(EPowerUp Type);
protected:
	// �÷��̾�� ī�޶��� �Ÿ��� �����ϱ� ���� ī�޶� �� 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	// Ÿ�� ��� ����� ī�޶� 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;
	// �÷��̾� ���� 
	UPROPERTY(BlueprintReadOnly)
		int32 Score;

	//Smash �ð�
	UPROPERTY(EditAnywhere, Category = PowerUps)
		float SmashTime;

	//Magnet �ð�
	UPROPERTY(EditAnywhere, Category = PowerUps)
		float MagnetTime;

	UPROPERTY(EditAnywhere, Category = PowerUps)
		float MagnetReach;



	// �÷��̾� �¿��� Ÿ�� ��ġ �̵��� �����Ѵ� 
	void MoveRight();
	void MoveLeft();

	// ������Ʈ �ݸ��� ĸ���� ���Ǵ� ������ �Լ� 
	UFUNCTION()
		void MyOnComponentOverlap(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void MyOnComponentEndOverlap(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void StopSmash();
	UFUNCTION()
		void StopMagnet();

	//�Ŀ� �� �Լ�
	void CoinMagnet();

	UFUNCTION()
		void Reset();

	//ų ����Ʈ(�÷��̾ �װ� �Ǵ� ��ġ)
	float Killpoint;


private:
	// ĳ���� �� ��ġ ������ 
	short CurrentLocation;
	FVector DesiredLocation;
	bool bBeingPushed;

	//�Ŀ� �� �Ӽ�
	bool CanSmash;
	bool CanMagnet;

public:
	void ScoreUp();

	int GetScore();
};
