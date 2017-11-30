// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyAnimInstance.h"
#include "MyFirstGameWorldCharacter.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMEWORLD_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	


	//------------������Hero�����Ա��л��ؿ�ʱ��ȡ��---------------------------
	//HeroName
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "HeroInit")
	FText HeroName;

	//HeroSklMeshArray Ӣ�۵�����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInit")
	TArray<USkeletalMesh*> HeroSklMeshArray;

	//Ӣ�۵���������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
	E_HeroWeaponType CurWeaponType;
	//Ӣ������ģ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInit")
	USkeletalMesh* HeroCurWeapon;

	//��¼��ǰ�Ķ�����ͼ����ͬ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInit")
	TSubclassOf<UMyAnimInstance> CurAnimBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
		TArray<FSkillInfo> OnHandSwordSkillInfo;


	//���� ��Ӣ�����ι��� ��Դ����
	UFUNCTION(BlueprintCallable)
	bool MergeMyCharactorSkl
	(		
		AActor* PlayerPawn, 			//Player
		TArray<USkeletalMesh*> SrcMeshList, 	//
		USkeletalMeshComponent* SkeletalComp
	);



	//-------------���ؿ��л�UMG���� ʱ����䡿--------
	//�ɹؿ���ʾ ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenLevel")
	float OldLevelTime;
	//�¹ؿ���ʾʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenLevel")
	float NewLevelTime;
};
