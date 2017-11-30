// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"

#include "SkillSystemWidget.generated.h"





/**
 * 
 */
UCLASS()
class MYFIRSTGAMEWORLD_API USkillSystemWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	//初始化 获取按钮对象
	virtual bool Initialize() override;


	//SkillSlot数组
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<UUserWidget*> SkillSlots;

	//获取玩家角色
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACharacter* MyPlayerREF;


	//------【UMG显示 可交互对象列表】----------------------
	//学习技能按键
	UButton* GetSkillButton;
	//技能名称
	UTextBlock* SkillName;
	//技能 是否可以使用
	UTextBlock* SkillEnable;
	//技能描述
	UTextBlock* SkillDescribe;
	//需要技能点
	UTextBlock* SkillPointAmount;
	//技能 详细说明框
	UVerticalBox* SkillDetailBox;
	//当前技能的点
	UTextBlock * CurSkillPoint;

	//记录当前显示的技能索引
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int SkillIndex;


	//用于显示 技能状态的辅助文字
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> SkillState;

	//更新显示 技能细节
	UFUNCTION(BlueprintCallable)
	void UpdataSkillDetail(int index);

	//判断是否能够学习技能
	UFUNCTION(BlueprintCallable)
	bool CanLeranSkill();

	//计算 更新 技能点
	UFUNCTION(BlueprintCallable)
	void CaculateSkillPoint();
};
