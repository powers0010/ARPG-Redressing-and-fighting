// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillSystemWidget.h"
#include "SkillSlotWidget.h"
#include "MyFirstGameWorldCharacter.h"

//FText 将全局 LOCTEXT_NAMESPACE 宏设为字符串文字，以指定该本地化键的命名空间。
#define LOCTEXT_NAMESPACE "Your Namespace" 

bool USkillSystemWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (UButton * LocalButton = Cast<UButton>(GetWidgetFromName("GetSkillButton")))
	{
		GetSkillButton = LocalButton;
	}
	if (UTextBlock * LocalSkillName = Cast<UTextBlock>(GetWidgetFromName("SkillName")))
	{
		SkillName = LocalSkillName;
	}
	if (UTextBlock * LocalSkillEnable = Cast<UTextBlock>(GetWidgetFromName("SkillEnable")))
	{
		SkillEnable = LocalSkillEnable;
	}
	if (UTextBlock * LocalSkillDescribe = Cast<UTextBlock>(GetWidgetFromName("SkillDescribe")))
	{
		SkillDescribe = LocalSkillDescribe;
	}
	if (UTextBlock * LocalSkillPointAmount = Cast<UTextBlock>(GetWidgetFromName("SkillPointAmount")))
	{
		SkillPointAmount = LocalSkillPointAmount;
	}
	if (UVerticalBox * LocalSkillDetailBox = Cast<UVerticalBox>(GetWidgetFromName("SkillDetailBox")))
	{
		SkillDetailBox = LocalSkillDetailBox;
	}
	if (UTextBlock * LocalCurSkillPoint = Cast<UTextBlock>(GetWidgetFromName("CurSkillPoint")))
	{
		CurSkillPoint = LocalCurSkillPoint;
	}

	return true;
}

void USkillSystemWidget::UpdataSkillDetail(int index)
{
	if (MyPlayerREF)
	{
		
		//保存技能索引
		SkillIndex = index;

		//更新显示详细信息
		AMyFirstGameWorldCharacter* MyPlayer = Cast<AMyFirstGameWorldCharacter>(MyPlayerREF);
		FSkillInfo LocalSkillInfo = MyPlayer->SkillInfo[index];

		if (CanLeranSkill())
		{
			GetSkillButton->SetIsEnabled(true);
		}
		else
		{
			GetSkillButton->SetIsEnabled(false);
		}
		if (SkillName)
		{
			SkillName->SetText(LocalSkillInfo.SkillName);
		}
		if (SkillEnable)
		{
			if (SkillState.Num() > 1)
			{
				if (MyPlayer->IsSkillEnable[index])
				{
					SkillEnable->SetText(SkillState[0]);
				}
				else
				{
					SkillEnable->SetText(SkillState[1]);
				}
			}
		}
		if (SkillDescribe)
		{
			SkillDescribe->SetText(LocalSkillInfo.SkillDestribe);
		}
		if (SkillPointAmount)
		{
			SkillPointAmount->SetText(FText::FromString(FString::FromInt(LocalSkillInfo.SkillPointAmount)));	
		}
		if (CurSkillPoint)
		{
			CurSkillPoint->SetText(FText::FromString(FString::FromInt(MyPlayer->HeroAttribute.CurSkillPoint)));
		}
		if (SkillDetailBox)
		{
			if (!SkillDetailBox->IsVisible())
			{
				SkillDetailBox->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

bool USkillSystemWidget::CanLeranSkill()
{
	if (!MyPlayerREF)
	{
		return false;
	}
	AMyFirstGameWorldCharacter* MyPlayer = Cast<AMyFirstGameWorldCharacter>(MyPlayerREF);
	if (MyPlayer->SkillInfo[SkillIndex].SkillPointAmount > MyPlayer->HeroAttribute.CurSkillPoint || MyPlayer->IsSkillEnable[SkillIndex])
	{
		return false;
	}
	return true;
}

void USkillSystemWidget::CaculateSkillPoint()
{
	AMyFirstGameWorldCharacter* MyPlayer = Cast<AMyFirstGameWorldCharacter>(MyPlayerREF);
	MyPlayer->HeroAttribute.CurSkillPoint = MyPlayer->HeroAttribute.CurSkillPoint - MyPlayer->SkillInfo[SkillIndex].SkillPointAmount;
}
//更新技能点
