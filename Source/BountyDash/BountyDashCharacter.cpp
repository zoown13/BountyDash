// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDashCharacter.h"
#include "BountyDash.h"
#include "Animation/AnimInstance.h" 
#include "Animation/AnimBlueprint.h" 
#include "Engine/TargetPoint.h"
#include "BountyDashGameMode.h"
#include "Obstacle.h"
#include "Coin.h"
#include "Floor.h"

#include "GenericPlatform/GenericPlatformMath.h"
#include "ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABountyDashCharacter::ABountyDashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ĸ�� ũ�� ����
	GetCapsuleComponent()->InitCapsuleSize(42.f,96.0f);
	
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> myAnimBP(TEXT("/Game/Barrel_Hopper/Character/BH_Character_AnimBP.BH_Character_AnimBP"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> myMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));

	if (myMesh.Succeeded() && myAnimBP.Succeeded()) {
		GetMesh()->SetSkeletalMesh(myMesh.Object);
		GetMesh()->SetAnimInstanceClass(myAnimBP.Object->GeneratedClass);
	}

	//�޽ø� ȸ���ϰ� �������� ĸ�� ������Ʈ�� �˸°� �����
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight())); //GetUnscaledCapsuleHalfHeight�� ���� ĸ�� ������ ���� ��ȯ

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//ĳ���� �̵� ����
	GetCharacterMovement()->JumpZVelocity = 1450.0f;
	GetCharacterMovement()->GravityScale = 4.5f;

	//ī�޶� �� �����(�ݸ����� �ִٸ� �÷��̾� ������ �������)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	check(CameraBoom);

	CameraBoom->AttachTo(RootComponent);

	//ī�޶� ĳ���� ���� ���� ���ݸ�ŭ ����´�
	CameraBoom->TargetArmLength = 500.0f;

	//�÷��̾���� ������
	CameraBoom->AddRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

	//Follow ī�޶� ����
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	check(FollowCamera);

	//�� ���� ī�޶� �����ϰ� ���� ��Ʈ�ѷ� ����� ��ġ�ϵ��� �����Ѵ�
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName);

	//ī�޶� �ణ �����ٺ����� �ϱ� ���� ȸ������
	FollowCamera->AddRelativeRotation(FQuat(FRotator(-10.0f, 0.0f, 0.0f)));

	//���� �Ӽ�
	CharSpeed = 10.0f;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyDashCharacter::MyOnComponentOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ABountyDashCharacter::MyOnComponentEndOverlap);

	//ID 0(�⺻ ��Ʈ�ѷ�)�� �Է� ��������
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//���� �����ϱ�
	hitObstacleSound = CreateDefaultSubobject<UAudioComponent>(TEXT("HitSound"));
	hitObstacleSound->bAutoActivate = false;
	hitObstacleSound->AttachTo(RootComponent);

	ConstructorHelpers::FObjectFinder<USoundCue>mySoundCue(TEXT("/Game/Sound/Grunt_Cue.Grunt_Cue"));

	if (mySoundCue.Succeeded()) {
		hitObstacleSound->SetSound(mySoundCue.Object);
	}

	dingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Ding"));
	dingSound->bAutoActivate = false;
	dingSound->AttachTo(RootComponent);

	ConstructorHelpers::FObjectFinder<USoundCue>myCue(TEXT("/Game/Sound/Ding_Cue.Ding_Cue"));

	if (myCue.Succeeded()) {
		dingSound->SetSound(myCue.Object);
	}

}

// Called when the game starts or when spawned
void ABountyDashCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATargetPoint> TargetIter(GetWorld()); TargetIter; ++TargetIter) {
		TargetArray.Add(*TargetIter);
	}

	auto SortPred = [](const AActor& A, const AActor& B)->bool
	{
		return(A.GetActorLocation().Y < B.GetActorLocation().Y);
	};
	TargetArray.Sort(SortPred);

	CurrentLocation = ((TargetArray.Num() / 2) + (TargetArray.Num() % 2) - 1);

	for (TActorIterator<AFloor>TargetIter(GetWorld()); TargetIter; ++TargetIter) {
		Killpoint = TargetIter->GetKillPoint();
	}
}

// Called every frame
void ABountyDashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetArray.Num() > 0) {
		FVector targetLoc = TargetArray[CurrentLocation]->GetActorLocation();
		targetLoc.Z = GetActorLocation().Z;
		targetLoc.X = GetActorLocation().X;

		if (targetLoc != GetActorLocation()) {
			SetActorLocation(FMath::Lerp(GetActorLocation(), targetLoc, CharSpeed*DeltaTime));//������������ �̿�
		}
	}

	if (bBeingPushed) {
		float moveSpeed = GetCustomGameMode<ABountyDashGameMode>(GetWorld())->GetInvGameSpeed();
		AddActorLocalOffset(FVector(moveSpeed, 0.0f, 0.0f));
	}

	if (CanMagnet) {
		CoinMagnet();
	}

	if (GetActorLocation().X < Killpoint) {
		GetCustomGameMode<ABountyDashGameMode>(GetWorld())->GameOver();
	}
}

// Called to bind functionality to input
void ABountyDashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//���� �÷��� Ű ���ε� �����ϱ�
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &ABountyDashCharacter::MoveRight);
	InputComponent->BindAction("Moveleft", IE_Pressed, this, &ABountyDashCharacter::MoveLeft);
	InputComponent->BindAction("Reset", IE_Pressed, this, &ABountyDashCharacter::Reset).bExecuteWhenPaused = true;
}

void ABountyDashCharacter::PowerUp(EPowerUp Type)
{
	switch (Type)
	{
	case EPowerUp::SPEED:
	{
		GetCustomGameMode<ABountyDashGameMode>(GetWorld())->ReduceGameSpeed();
		break;
	}

	case EPowerUp::SMASH:
	{
		CanSmash = true;
		FTimerHandle newTimer;
		GetWorld()->GetTimerManager().SetTimer(newTimer, this, &ABountyDashCharacter::StopSmash, SmashTime, false);
		break;
	}
	case EPowerUp::MAGNET:
	{
		CanMagnet = true;
		FTimerHandle newTimer;
		GetWorld()->GetTimerManager().SetTimer(newTimer, this, &ABountyDashCharacter::StopMagnet, MagnetTime, false);
		break;
	}
	default:
		break;
	}
}

void ABountyDashCharacter::MoveRight() {
	if ((Controller != nullptr)) {
		if (CurrentLocation < TargetArray.Num() - 1) {
			++CurrentLocation;
		}
		else {
			//�ƹ��͵� ���� �ʴ´�
		}
	}
}

void ABountyDashCharacter::MoveLeft() {
	if ((Controller != nullptr)) {
		if (CurrentLocation >0) {
			--CurrentLocation;
		}
		else {
			//�ƹ��͵� ���� �ʴ´�
		}
	}
}

void ABountyDashCharacter::MyOnComponentOverlap(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass())) {
		FVector vecBetween = OtherActor->GetActorLocation() - GetActorLocation();
		float AngleBetween = FMath::Acos(FVector::DotProduct(vecBetween.GetSafeNormal(), GetActorForwardVector().GetSafeNormal()));

		if (AngleBetween < 60.0f) {

			AObstacle* pObs = Cast<AObstacle>(OtherActor);

			if (!bBeingPushed) {
				hitObstacleSound->Play();
			}

			if (pObs&&CanSmash) {
				pObs->GetDestructable()->ApplyRadiusDamage(10000, GetActorLocation(), 10000, 10000, true);
			}

			else{
				bBeingPushed = true;
			}
			
		}
	}
}

void ABountyDashCharacter::MyOnComponentEndOverlap(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor->GetClass()->IsChildOf(AObstacle::StaticClass())) {
		bBeingPushed = false;
	}
	
}

void ABountyDashCharacter::StopSmash()
{
	CanSmash = false;
}

void ABountyDashCharacter::StopMagnet()
{
	CanMagnet = false;
}

void ABountyDashCharacter::CoinMagnet()
{
	for (TActorIterator<ACoin>coinIter(GetWorld()); coinIter; ++coinIter) {
		FVector between = GetActorLocation() - coinIter->GetActorLocation();
		if (FMath::Abs(between.Size()) < MagnetReach) {
			FVector CoinPos = FMath::Lerp((*coinIter)->GetActorLocation(), GetActorLocation(), 0.2f);
			(*coinIter)->SetActorLocation(CoinPos);
			(*coinIter)->BeingPulled = true;
		}
	}
}

void ABountyDashCharacter::Reset()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("BountyDashMap"));
}

void ABountyDashCharacter::ScoreUp()
{
	Score++;
	GetCustomGameMode<ABountyDashGameMode>(GetWorld())->CharScoreUp(Score);
	dingSound->Play();
}

int ABountyDashCharacter::GetScore()
{
	return Score;
}
