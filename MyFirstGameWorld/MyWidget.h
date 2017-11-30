// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "SkillSystemWidget.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMEWORLD_API UMyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//无参构造函数
	UMyWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual bool Initialize()override;


	//----------【技能 显示框】------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkillSystemWidget* SkillSystemWidget;


	//----------【Hero左上角 状态栏】----
	//血条
	UProgressBar * HealthBar;
	//能量条
	UProgressBar * EnergyBar;
	//经验条
	UProgressBar * ExpBar;
	


	//获取玩家角色
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class ACharacter* MyPlayerREF;

	//获取玩家角色函数
	void FindPlayerCharactor();


};
