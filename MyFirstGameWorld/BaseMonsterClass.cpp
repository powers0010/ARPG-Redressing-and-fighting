// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMonsterClass.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "MyFirstGameWorldCharacter.h"


// Sets default values
ABaseMonsterClass::ABaseMonsterClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponBox = nullptr;
	LeftHandBox = nullptr;
	AttackRange = nullptr;
	TargetCharactor = nullptr;
	Montage_BeAttack = nullptr;
	Montage_BeAttack_back = nullptr;
	Montage_BeAttack_back_heavy = nullptr;
	Montage_BeAttack_FallDown = nullptr;
	Montage_BeAttack_ToAir = nullptr;
	Montage_BeAttack_Dizziness = nullptr;
	Montage_Death = nullptr;

}

// Called when the game starts or when spawned
void ABaseMonsterClass::BeginPlay()
{
	Super::BeginPlay();
	
	//获取碰撞区域指针
	FindWeaponCollisionArea();

	if (WeaponBox)
	{
		WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonsterClass::OnOverlapBeginForWeaponCollisionBox);
	}
	if (LeftHandBox)
	{
		LeftHandBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonsterClass::OnOverlapBeginForWeaponCollisionBox);
	}
//	if (AttackRange)
//	{
//		AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonsterClass::OnOverlapBeginForAtackRange);
//		AttackRange->OnComponentEndOverlap.AddDynamic(this, &ABaseMonsterClass::OnOverlapEndForAttackRange);
//	}
// 	if (SensingComp)
// 	{
// 		SensingComp->OnSeePawn.AddDynamic(this, &ABaseMonsterClass::OnSeeingPawn);
// 	}

}

// Called every frame
void ABaseMonsterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonsterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABaseMonsterClass::DecreateHP_Implementation(float DeHp)
{
	if (!bIsDied)
	{
		CurHealth -= DeHp;
		if (CurHealth<=0.f)
		{
			bIsDied = true;
			GetMesh()->PlayAnimation(Montage_Death,false);
			
		}
	}
}

//实现IApplyDamage 接口函数
void ABaseMonsterClass::ApplyDamage_Implementation(FVector HitLocation , E_SkillEffect Skilleffect)
{
	NPCActionState = E_NPCActionState::NPCActionState_Attack;
	FString HitSt = HitLocation.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("I am hit At")+HitSt);

	//逻辑是 普通攻击效果 被其他效果打断
	if (bIsDied)
	{
		return;
	}
	if (GetCurrentMontage() == nullptr || GetCurrentMontage() == Montage_BeAttack)
	{
		switch (Skilleffect)
		{
		case E_SkillEffect::SkillEffect_NoEffect:
			if (Montage_BeAttack && GetCurrentMontage() == nullptr)
			{
				PlayAnimMontage(Montage_BeAttack);
			}
			break;
		case E_SkillEffect::SkillEffect_Hitback:
			if (Montage_BeAttack_back)
			{
				PlayAnimMontage(Montage_BeAttack_back);
			}
			else if (Montage_BeAttack && GetCurrentMontage() == nullptr)
			{
				PlayAnimMontage(Montage_BeAttack);
			}
			break;
		case E_SkillEffect::SkillEffect_HitbackHeavy:
			if (Montage_BeAttack_back_heavy)
			{
				PlayAnimMontage(Montage_BeAttack_back_heavy);
			}
			else
				if (Montage_BeAttack && GetCurrentMontage() == nullptr)
				{
					PlayAnimMontage(Montage_BeAttack);
				}
			break;
		case E_SkillEffect::SkillEffect_HitToAir:
			if (Montage_BeAttack_ToAir)
			{
				PlayAnimMontage(Montage_BeAttack_ToAir);
			}
			else
				if (Montage_BeAttack && GetCurrentMontage() == nullptr)
				{
					PlayAnimMontage(Montage_BeAttack);
				}
			break;
		case E_SkillEffect::SkillEffect_HitFallDown:
			if (Montage_BeAttack_FallDown)
			{
				PlayAnimMontage(Montage_BeAttack_FallDown);
			}
			else
				if (Montage_BeAttack && GetCurrentMontage() == nullptr)
				{
					PlayAnimMontage(Montage_BeAttack);
				}
			break;
		case E_SkillEffect::SkillEffect_HitDizziness:
			if (Montage_BeAttack_Dizziness)
			{
				PlayAnimMontage(Montage_BeAttack_Dizziness);
			}
			else
				if (Montage_BeAttack && GetCurrentMontage() == nullptr)
				{
					PlayAnimMontage(Montage_BeAttack);
				}
			break;
		default:
			break;
		}
	}

}

void ABaseMonsterClass::FindWeaponCollisionArea()
{
	TArray<UBoxComponent*> OutBoxComponent;
	ABaseMonsterClass::GetComponents(OutBoxComponent);
	if (OutBoxComponent.Num() > 1)
	{
		LeftHandBox = OutBoxComponent[0];
		WeaponBox = OutBoxComponent[1];
	}
	TArray<USphereComponent*> OutSphereComponent;
	ABaseMonsterClass::GetComponents(OutSphereComponent);
	if (OutSphereComponent.Num() > 0)
	{
		AttackRange = OutSphereComponent[0];
	}
	TArray<UPawnSensingComponent*> OutPawnSensing;
	ABaseMonsterClass::GetComponents(OutPawnSensing);
	if (OutPawnSensing.Num()>0)
	{
		SensingComp = OutPawnSensing[0];
	}
	
}

void ABaseMonsterClass::OnOverlapBeginForWeaponCollisionBox(
	UPrimitiveComponent* OverlappedComp,	//碰撞组件
	AActor* OtherActor,						//碰撞对象
	UPrimitiveComponent* OtherComp,			//
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor!=nullptr && OtherActor!=this && OtherComp!=nullptr)
	{
		AMyFirstGameWorldCharacter* MyPlayer = Cast<AMyFirstGameWorldCharacter>(OtherActor);
		if (MyPlayer)
		{
			if (MyPlayer->GetClass()->ImplementsInterface(UIApplyDamage::StaticClass()))
			{
				if (CanApplyDamage)
				{
					IIApplyDamage::Execute_ApplyDamage(MyPlayer, FVector(0.f, 0.f, 0.f), E_SkillEffect::SkillEffect_NoEffect);
					IIApplyDamage::Execute_DecreateHP(MyPlayer,10.f);
				}				
			}
		}
	}
}
void ABaseMonsterClass::OnOverlapBeginForAtackRange(
	UPrimitiveComponent* OverlappedComp,	//碰撞组件
	AActor* OtherActor,						//碰撞对象
	UPrimitiveComponent* OtherComp,			//
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		AMyFirstGameWorldCharacter* MyPlayer = Cast<AMyFirstGameWorldCharacter>(OtherActor);
		if (MyPlayer)
		{
			if (!TargetCharactor)
			{
				TargetCharactor = MyPlayer;
			}
			if (NPCActionState == E_NPCActionState::NPCActionState_Chase)
			{
				NPCActionState = E_NPCActionState::NPCActionState_Attack;
			}
		}
	}
}
void ABaseMonsterClass::OnOverlapEndForAttackRange(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (NPCActionState == E_NPCActionState::NPCActionState_Attack)
	{
		NPCActionState = E_NPCActionState::NPCActionState_Chase;
	}
}
void ABaseMonsterClass::OnSeeingPawn(APawn* TargetPawn)
{
	if (TargetPawn)
	{
		AMyFirstGameWorldCharacter* MyPlayer = Cast<AMyFirstGameWorldCharacter>(TargetPawn);
		if (MyPlayer)
		{
			if (NPCActionState == E_NPCActionState::NPCActionState_Patrol)
			{
				TargetCharactor = MyPlayer;
				NPCActionState = E_NPCActionState::NPCActionState_Chase;
			}
		}
	}
}
