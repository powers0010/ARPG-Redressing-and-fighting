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
	//���캯��
		USkillSlotWidget(const FObjectInitializer& ObjectInitializer);

		//����Button��Image
	UButton* SkillButton;
	UImage* SkillImage;

	//���漼�ܶ�Ӧ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACharacter* MyPlayerREF;

	//��ʼ�� ��ȡ��ť����
	virtual bool Initialize() override;
	
};
