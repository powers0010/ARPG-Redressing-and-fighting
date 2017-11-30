// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IApplyDamage.generated.h"

//技能效果 击退、眩晕、击倒等等
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

	//传递被攻击信息 //被攻击的位置 及 被攻击的效果（如果需要）
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AplayDamage")
	void ApplyDamage(FVector HitLocation = FVector(0.f, 0.f, 0.f), E_SkillEffect Skilleffect = E_SkillEffect::SkillEffect_NoEffect);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AplayDamage")
		void DecreateHP(float DeHp);

};

