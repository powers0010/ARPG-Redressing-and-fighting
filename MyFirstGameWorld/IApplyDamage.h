// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IApplyDamage.generated.h"

//����Ч�� ���ˡ�ѣ�Ρ������ȵ�
UENUM(BlueprintType)
enum class E_SkillEffect :uint8
{
	SkillEffect_NoEffect = 0,
	SkillEffect_Hitback = 1,
	SkillEffect_HitbackHeavy = 2,
	SkillEffect_HitToAir = 3,
	SkillEffect_HitFallDown = 4 ,
	SkillEffect_HitDizziness = 5
};
/**
 * 
 */
UINTERFACE(Blueprintable)
class MYFIRSTGAMEWORLD_API UIApplyDamage : public UInterface
{
	GENERATED_UINTERFACE_BODY()

		UIApplyDamage();
	
};

class MYFIRSTGAMEWORLD_API IIApplyDamage
{
	GENERATED_IINTERFACE_BODY()

public:

	//���ݱ�������Ϣ //��������λ�� �� ��������Ч���������Ҫ��
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AplayDamage")
	void ApplyDamage(FVector HitLocation = FVector(0.f, 0.f, 0.f), E_SkillEffect Skilleffect = E_SkillEffect::SkillEffect_NoEffect);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AplayDamage")
		void DecreateHP(float DeHp);

};

