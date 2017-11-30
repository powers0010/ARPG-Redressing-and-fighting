// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IApplyDamage.h"
#include "GameFramework/Character.h"
#include "BaseMonsterClass.generated.h"

//ǰ������
class AMyFirstGameWorldCharacter;
//NPC״̬ ����-Ѳ��-
UENUM(BlueprintType)
enum class E_NPCActionState :uint8
{
	NPCActionState_Patrol = 0,	//Ѳ��
	NPCActionState_Chase = 1,	//׷��
	NPCActionState_Attack = 2,	//����
	NPCActionState_Death = 3	//����
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

	//����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float CurHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		bool bIsDied;


	//��Ұ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UPawnSensingComponent* SensingComp;

	//��ײ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* WeaponBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* LeftHandBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USphereComponent* AttackRange;

	//�Ƿ���й������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool CanApplyDamage;

	//Ŀ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category ="AI")
		AMyFirstGameWorldCharacter* TargetCharactor;

	//��Ϊ�� - NPC��Ϊ״̬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	E_NPCActionState NPCActionState;

	//��Ŷ�����̫����Դ������������������
	//������������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		TArray<UAnimMontage*> Montage_MagicAttack;

	//����Ӧ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<UAnimMontage*> Montage_Attack;
	
	//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack;
	//������ С
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_back;
	//������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_back_heavy;
	//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_FallDown;
	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_ToAir;
	//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimMontage* Montage_BeAttack_Dizziness;

	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeHit")
		UAnimationAsset* Montage_Death;

	//ʵ��IApplyDamage �ӿں���
	//�������ķ���
	void ApplyDamage_Implementation(FVector HitLocation = FVector(0.f, 0.f, 0.f), E_SkillEffect Skilleffect = E_SkillEffect::SkillEffect_NoEffect);

	void DecreateHP_Implementation(float DeHp);

	//��ȡ��ײ���� ָ��
	void FindWeaponCollisionArea();

	//�������
	void OnSeeingPawn(APawn* TargetPawn);

	//��ײ���� ��Ӧ�¼� �������
	UFUNCTION(Category = Collision)
		void OnOverlapBeginForWeaponCollisionBox(
			UPrimitiveComponent* OverlappedComp,	//��ײ���
			AActor* OtherActor,						//��ײ����
			UPrimitiveComponent* OtherComp,			//
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	//���빥������ ��Ӧ�¼�
	UFUNCTION(Category = Collision)
		void OnOverlapBeginForAtackRange(
			UPrimitiveComponent* OverlappedComp,	//��ײ���
			AActor* OtherActor,						//��ײ����
			UPrimitiveComponent* OtherComp,			//
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	//�뿪�������� ��Ӧ�¼�
	void OnOverlapEndForAttackRange(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	

};
