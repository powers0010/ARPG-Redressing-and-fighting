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

//Ӣ��ʹ�õ��������� ö��
UENUM(BlueprintType)
enum class E_HeroWeaponType :uint8
{
	HeroWeaponType_OneHandSword = 0 ,
	HeroWeaponType_TwoHandSword = 1
};

//Ӣ����Ҫ�洢��״̬
USTRUCT(BlueprintType)
struct FHeroAttribute 
{
	GENERATED_BODY()
	//-----------------��Ӣ�۵Ļ������ԡ�--------------
	//����ֵ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurHealth;
	//������ħ��ֵ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxEnergy;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurEnergy;
	//����ֵ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxExp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurExp;
	//�ȼ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int HeroLevel;
	//��ǰӵ�еļ��ܵ�
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

//���� �������� �Ķ�����Section��Ϣ
USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_BODY()
		//��������
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SkillName;
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SkillDestribe;
	//����ͼ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D * SkillIcon;
	//ѧϰ���� ��Ҫ���ܵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SkillPointAmount;
	//���ܶ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* SkillAnim;
	//���� ��̫�涯�� ��Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CurSectionName;
	//�������� ��һ�� Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName NextSectionName;
	//�����Ƿ���Ҫ�ڿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsJump;
	//�����Ƿ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHaveCombo;
	//������ɵ�Ч�� 
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
	//--------------����WidgetComponent----------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* HeroNameWidget;

	//--------������BeginPlay��----------
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override ;

	void DoJumpIfCanJump();

	//-----��MainWidget��---------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UMyWidget* Mainwidget;

	//------������MainWdiget��---------
	UFUNCTION(BlueprintCallable)
	void CreateMainWidget(TSubclassOf<UMyWidget> NewWidget);

	//----------��Ӣ�� ��洢 ��Ϣ��----------------
	//Ӣ�� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
	FText HeroName;

	//��ǰ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
		E_HeroWeaponType CurWeaponType;
	//DamagePoint�˺�ֵ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
		float DamageAmount;

	//Ӣ�� ���� �·� SklmeshArray
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroSklmesh")
	TArray<USkeletalMeshComponent*> HeroSkeletalmeshComArray;

	//Ӣ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		FHeroAttribute HeroAttribute;

	UFUNCTION(BlueprintCallable)
		void UpdataHeroStateBar();



	//----------��Ӣ�� ״̬��----------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsDie;

	//�Ƿ���ս��״̬�����������Ƿ����ʹ����Ʒ��ʹ�÷�ս��״̬�������Ƿ���Խ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsFighting;

	//�Ƿ�װ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsEqip;

	//�Ƿ���Թ���,�����ڷ�ֹ���л����������з�������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
		bool bCanAttack;


	//�ܷ� �������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bCanGrow;

	//�ܷ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
		bool bCanJump;

	//�Ƿ����ڹ����������ж��ܷ񲥷Ź�������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bIsAttacking;

	//�Ƿ������������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
	bool bCanCombo;

	//�Ƿ��ڷ���״̬
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroState")
		bool bIsBlocking;

	//���ڡ��ж��Ƿ����˺���//��ֹ�ǹ���״̬����˺���ײ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ApplyDamage")
		bool bCanApplyDamage;

	//�ж��ܷ񹥻� ���� �ͷż��ܣ�������Թ������������ ����ֵ �����true
	UFUNCTION(BlueprintCallable)
		bool CanDoSkill();


	//���� ��ݼ� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
		TArray<FKey> SkillHotKeys;

	//��ͨ ���� ���������� montage��Դ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
	TArray<UAnimMontage*> NormalAttComboAnim;

	//���� Montage��Դ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
	TArray<FSkillInfo> SkillInfo;

	//��������Ӧ  ��̫����Դ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
		TArray<UAnimMontage*> BeAttackNomal;

	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MontageAsset")
		TArray<UAnimMontage*> DieAnim;

	//�����Ƿ��Ѿ�get
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
	TArray<bool> IsSkillEnable;
	//���ܵ�Ч��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
	E_SkillEffect SkillEffect;


	//----------������ ��ײBox��----------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ApplyDamage")
	UBoxComponent* WeaponCollisionBox;

	//�������� ���ߵ� �����ڵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ApplyDamage")
	UStaticMeshComponent* TraceStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ApplyDamage")
	UStaticMeshComponent* TraceEnd;

	//��SkeletalMeshͬʱ������̫��
//	UFUNCTION(BlueprintCallable)
//	void PlayAnimMontageAtSameTime(class UAnimMontage* AnimMontage);

	//���ö�����ͼ
//	UFUNCTION(BlueprintCallable)
//	void RsetAnimInstance(class UClass* AnimBP);


	//--------------���������㺯����-----------
	//Widget�����ת����
	
public:
	//��ת Ӣ������ ʼ����������ͷ
	void FaceToScreen();

	//��ʾ ���� ���� ϸ�ڿ�
	void ShowSkillWidget();

	//��Ϸ��ʼʱ ��ȡ������ײ�����ָ��
	void FindWeaponCollisionArea();

	//��ͨ����
	void OnAttack();

	//����
	void OnDie();

	//���� ��ͼ����/�¼� PlayMontageAtSanmeTime
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
		void PlayMontageAtSameTime(UAnimMontage* NewMontage);
	//��ͼ������������
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void PlayDieAnim();


	//����������ײ��Ӧ����
	UFUNCTION(Category = Collision)
	void OnOverlapBeginForWeaponCollisionBox(
		UPrimitiveComponent* OverlappedComp,	//��ײ���
		AActor* OtherActor,						//��ײ����
		UPrimitiveComponent* OtherComp,			//
		int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult& SweepResult);

	//�������� �����ײ��
	FVector SpawnWeaponTrace();


	//�ӿں��� 
	void ApplyDamage_Implementation(FVector HitLocation = FVector(0.f,0.f,0.f), E_SkillEffect Skilleffect = E_SkillEffect::SkillEffect_NoEffect);

	void DecreateHP_Implementation(float DeHp);


};

