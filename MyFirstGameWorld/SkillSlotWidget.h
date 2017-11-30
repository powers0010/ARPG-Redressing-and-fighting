// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMEWORLD_API USkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//构造函数
		USkillSlotWidget(const FObjectInitializer& ObjectInitializer);

		//技能Button和Image
	UButton* SkillButton;
	UImage* SkillImage;

	//保存技能对应的索引
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACharacter* MyPlayerREF;

	//初始化 获取按钮对象
	virtual bool Initialize() override;
	
};
