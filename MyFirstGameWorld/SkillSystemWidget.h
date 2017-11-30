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

	//��ʼ�� ��ȡ��ť����
	virtual bool Initialize() override;


	//SkillSlot����
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<UUserWidget*> SkillSlots;

	//��ȡ��ҽ�ɫ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACharacter* MyPlayerREF;


	//------��UMG��ʾ �ɽ��������б�----------------------
	//ѧϰ���ܰ���
	UButton* GetSkillButton;
	//��������
	UTextBlock* SkillName;
	//���� �Ƿ����ʹ��
	UTextBlock* SkillEnable;
	//��������
	UTextBlock* SkillDescribe;
	//��Ҫ���ܵ�
	UTextBlock* SkillPointAmount;
	//���� ��ϸ˵����
	UVerticalBox* SkillDetailBox;
	//��ǰ���ܵĵ�
	UTextBlock * CurSkillPoint;

	//��¼��ǰ��ʾ�ļ�������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int SkillIndex;


	//������ʾ ����״̬�ĸ�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> SkillState;

	//������ʾ ����ϸ��
	UFUNCTION(BlueprintCallable)
	void UpdataSkillDetail(int index);

	//�ж��Ƿ��ܹ�ѧϰ����
	UFUNCTION(BlueprintCallable)
	bool CanLeranSkill();

	//���� ���� ���ܵ�
	UFUNCTION(BlueprintCallable)
	void CaculateSkillPoint();
};
