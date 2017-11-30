// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFirstGameWorldCharacter.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */

UCLASS()
class MYFIRSTGAMEWORLD_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//------------��������----
	//��ɫ�ٶ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float speed;

	//�Ƿ��ڿ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInAir;

	//��ɫ ״̬���Ƿ�װ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsEqip;

	//���� Player ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMyFirstGameWorldCharacter * AnimOwner;

	//------------��������----
	//�����ٶ�
	void CaculateOwnerparameter();

	//���� UpdataAnim����
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
