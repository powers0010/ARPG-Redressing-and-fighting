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
	//�޲ι��캯��
	UMyWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual bool Initialize()override;


	//----------������ ��ʾ��------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkillSystemWidget* SkillSystemWidget;


	//----------��Hero���Ͻ� ״̬����----
	//Ѫ��
	UProgressBar * HealthBar;
	//������
	UProgressBar * EnergyBar;
	//������
	UProgressBar * ExpBar;
	


	//��ȡ��ҽ�ɫ
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class ACharacter* MyPlayerREF;

	//��ȡ��ҽ�ɫ����
	void FindPlayerCharactor();


};
