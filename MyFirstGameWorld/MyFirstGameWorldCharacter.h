// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IApplyDamage.h"
#include "MyWidget.h"
#include "MyPlayerController.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "MyFirstGameWorldCharacter.generated.h"

//英雄使用的武器类型 枚举
UENUM(BlueprintType)
enum class E_HeroWeaponType :uint8
{
	HeroWeaponType_OneHandSword = 0 ,
	HeroWeaponType_TwoHandSword = 1
};

//英雄需要存储的状态
USTRUCT(BlueprintType)
struct FHeroAttribute 
{
	GENERATED_BODY()
	//-----------------【英雄的基础属性】--------------
	//生命值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurHealth;
	//能量？魔法值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxEnergy;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurEnergy;
	//经验值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxExp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurExp;
	//等级
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int HeroLevel;
	//当前拥有的技能点
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurSkillPoint;

	FHeroAttribute()
	{
		MaxHealth = 100.f;
		CurHealth = 100.f;
		MaxEnergy = 100.f;
		CurEnergy = 100.f;
		MaxExp = 100.f;
		CurExp = 0.f;
		HeroLevel = 1;
		CurSkillPoint = 7;
	}

};

//保存 技能连击 的动画和Section信息
USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_BODY()
		//技能名称
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SkillName;
	//技能描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SkillDestribe;
	//技能图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D * SkillIcon;
	//学习技能 需要技能点
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SkillPointAmount;
	//技能动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* SkillAnim;
	//技能 蒙太奇动画 的Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CurSectionName;
	//技能连击 下一个 Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName NextSectionName;
	//技能是否需要腾空
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsJump;
	//技能是否存在连击
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHaveCombo;
	//技能造成的效果 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_SkillEffect SkillEffect;

	FSkillInfo()
	{
		SkillName = FText();
		SkillDestribe = FText();
		SkillIcon = nullptr;
		SkillPointAmount = 0;
		SkillAnim = nullptr;
		CurSectionName = NAME_None;
		NextSectionName = NAME_None;
		bIsJump = false;
		bHaveCombo = false;
		SkillEffect = E_SkillEffect::SkillEffect_NoEffect;
	}
};


UCLASS(config=Game)
class AMyFirstGameWorldCharacter : public ACharacter , public IIApplyDamage
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMyFirstGameWorldCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



	
public:
	//--------------创建WidgetComponent----------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* HeroNameWidget;

	//--------【重载BeginPlay】----------
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override ;

	void DoJumpIfCanJump();

	//-----【MainWidget】---------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UMyWidget* Mainwidget;

	//------【创建MainWdiget】---------
	UFUNCTION(BlueprintCallable)
	void CreateMainWidget(TSubclassOf<UMyWidget> NewWidget);

	//----------【英雄 需存储 信息】----------------
	//英雄 名字
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
	FText HeroName;

	//当前武器
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
		E_HeroWeaponType CurWeaponType;
	//DamagePoint伤害值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
		float DamageAmount;

	//英雄 外形 衣服 SklmeshArray
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroSklmesh")
	TArray<USkeletalMeshComponent*> HeroSkeletalmeshComArray;

	//英雄属性
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		FHeroAttribute HeroAttribute;

	UFUNCTION(BlueprintCallable)
		void UpdataHeroStateBar();



	//----------【英雄 状态】----------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsDie;

	//是否处于战斗状态，用来控制是否可以使用物品，使用非战斗状态动作，是否可以交互等
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsFighting;

	//是否装备武器
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsEqip;

	//是否可以攻击,仅用于防止在切换武器过程中发生攻击
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
		bool bCanAttack;


	//能否 滚动躲避
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bCanGrow;

	//能否起跳
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
		bool bCanJump;

	//是否正在攻击，用于判断能否播放攻击动作
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsAttacking;

	//是否进行连击动作
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bCanCombo;

	//是否处于防御状态
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
		bool bIsBlocking;

	//用于【判断是否检测伤害】//防止非攻击状态检测伤害碰撞
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ApplyDamage")
		bool bCanApplyDamage;

	//判断能否攻击 或者 释放技能，如果可以攻击，设置相关 变量值 并输出true
	UFUNCTION(BlueprintCallable)
		bool CanDoSkill();


	//技能 快捷键 组合
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
		TArray<FKey> SkillHotKeys;

	//普通 攻击 的连击动作 montage资源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
	TArray<UAnimMontage*> NormalAttComboAnim;

	//技能 Montage资源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
	TArray<FSkillInfo> SkillInfo;

	//被攻击反应  蒙太奇资源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
		TArray<UAnimMontage*> BeAttackNomal;

	//死亡动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
		TArray<UAnimMontage*> DieAnim;

	//技能是否已经get
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
	TArray<bool> IsSkillEnable;
	//技能的效果
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
	E_SkillEffect SkillEffect;


	//----------【武器 碰撞Box】----------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ApplyDamage")
	UBoxComponent* WeaponCollisionBox;

	//用于生成 射线的 辅助节点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ApplyDamage")
	UStaticMeshComponent* TraceStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ApplyDamage")
	UStaticMeshComponent* TraceEnd;

	//各SkeletalMesh同时播放蒙太奇
//	UFUNCTION(BlueprintCallable)
//	void PlayAnimMontageAtSameTime(class UAnimMontage* AnimMontage);

	//重置动画蓝图
//	UFUNCTION(BlueprintCallable)
//	void RsetAnimInstance(class UClass* AnimBP);


	//--------------【辅助计算函数】-----------
	//Widget组件旋转函数
	
public:
	//旋转 英雄名字 始终面向摄像头
	void FaceToScreen();

	//显示 隐藏 技能 细节框
	void ShowSkillWidget();

	//游戏开始时 获取武器碰撞区域的指针
	void FindWeaponCollisionArea();

	//普通攻击
	void OnAttack();

	//死亡
	void OnDie();

	//创建 蓝图函数/事件 PlayMontageAtSanmeTime
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
		void PlayMontageAtSameTime(UAnimMontage* NewMontage);
	//蓝图播放死亡动画
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void PlayDieAnim();


	//武器区域碰撞响应函数
	UFUNCTION(Category = Collision)
	void OnOverlapBeginForWeaponCollisionBox(
		UPrimitiveComponent* OverlappedComp,	//碰撞组件
		AActor* OtherActor,						//碰撞对象
		UPrimitiveComponent* OtherComp,			//
		int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult& SweepResult);

	//生成射线 检测碰撞点
	FVector SpawnWeaponTrace();


	//接口函数 
	void ApplyDamage_Implementation(FVector HitLocation = FVector(0.f,0.f,0.f), E_SkillEffect Skilleffect = E_SkillEffect::SkillEffect_NoEffect);

	void DecreateHP_Implementation(float DeHp);


};

