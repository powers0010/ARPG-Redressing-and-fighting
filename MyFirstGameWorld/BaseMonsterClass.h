// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IApplyDamage.h"
#include "GameFramework/Character.h"
#include "BaseMonsterClass.generated.h"

//前置声明
class AMyFirstGameWorldCharacter;
//NPC状态 待机-巡逻-
UENUM(BlueprintType)
enum class E_NPCActionState :uint8
{
	NPCActionState_Patrol = 0,	//巡逻
	NPCActionState_Chase = 1,	//追赶
	NPCActionState_Attack = 2,	//攻击
	NPCActionState_Death = 3	//死亡
};


UCLASS()
class MYFIRSTGAMEWORLD_API ABaseMonsterClass : public ACharacter , public IIApplyDamage
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonsterClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float CurHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		bool bIsDied;


	//视野
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UPawnSensingComponent* SensingComp;

	//碰撞区域
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* WeaponBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* LeftHandBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USphereComponent* AttackRange;

	//是否进行攻击检测
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool CanApplyDamage;

	//目标
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category ="AI")
		AMyFirstGameWorldCharacter* TargetCharactor;

	//行为树 - NPC行为状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	E_NPCActionState NPCActionState;

	//存放动画蒙太奇资源，攻击、被攻击、等
	//法术攻击动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		TArray<UAnimMontage*> Montage_MagicAttack;

	//攻击应动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<UAnimMontage*> Montage_Attack;
	
	//被攻击
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack;
	//被击退 小
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_back;
	//被击退 大
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_back_heavy;
	//被击倒
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_FallDown;
	//被击 浮空
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_ToAir;
	//被击 浮空
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_Dizziness;

	//正常死亡
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimationAsset* Montage_Death;

	//实现IApplyDamage 接口函数
	//被攻击的反馈
	void ApplyDamage_Implementation(FVector HitLocation = FVector(0.f, 0.f, 0.f), E_SkillEffect Skilleffect = E_SkillEffect::SkillEffect_NoEffect);

	void DecreateHP_Implementation(float DeHp);

	//获取碰撞区域 指针
	void FindWeaponCollisionArea();

	//发现玩家
	void OnSeeingPawn(APawn* TargetPawn);

	//碰撞区域 响应事件 攻击检测
	UFUNCTION(Category = Collision)
		void OnOverlapBeginForWeaponCollisionBox(
			UPrimitiveComponent* OverlappedComp,	//碰撞组件
			AActor* OtherActor,						//碰撞对象
			UPrimitiveComponent* OtherComp,			//
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	//进入攻击区域 响应事件
	UFUNCTION(Category = Collision)
		void OnOverlapBeginForAtackRange(
			UPrimitiveComponent* OverlappedComp,	//碰撞组件
			AActor* OtherActor,						//碰撞对象
			UPrimitiveComponent* OtherComp,			//
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	//离开攻击区域 响应事件
	void OnOverlapEndForAttackRange(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	

};
