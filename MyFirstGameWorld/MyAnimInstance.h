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
	//------------【变量】----
	//角色速度
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float speed;

	//是否在空中
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInAir;

	//角色 状态（是否装备武器）
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsEqip;

	//保存 Player 引用
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMyFirstGameWorldCharacter * AnimOwner;

	//------------【方法】----
	//计算速度
	void CaculateOwnerparameter();

	//重载 UpdataAnim函数
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
