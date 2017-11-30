// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillSlotWidget.h"

USkillSlotWidget::USkillSlotWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	SkillImage = nullptr;
	SkillButton = nullptr;

}

bool USkillSlotWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (UButton * LocalButton = Cast<UButton>(GetWidgetFromName("SkillButton")))
	{
		SkillButton = LocalButton;
	}
	if (UImage * LocalImage = Cast<UImage>(GetWidgetFromName("SkillImage")))
	{
		SkillImage = LocalImage;
	}
	return true;
}

