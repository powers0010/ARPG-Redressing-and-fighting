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
	


	//------------【保存Hero数据以便切换关卡时读取】---------------------------
	//HeroName
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "HeroInit")
	FText HeroName;

	//HeroSklMeshArray 英雄的外形
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInit")
	TArray<USkeletalMesh*> HeroSklMeshArray;

	//英雄的武器类型
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInfo")
	E_HeroWeaponType CurWeaponType;
	//英雄武器模型
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInit")
	USkeletalMesh* HeroCurWeapon;

	//记录当前的动画蓝图（不同武器）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HeroInit")
	TSubclassOf<UMyAnimInstance> CurAnimBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillInfo")
		TArray<FSkillInfo> OnHandSwordSkillInfo;


	//加载 绑定英雄外形骨骼 到源骨骼
	UFUNCTION(BlueprintCallable)
	bool MergeMyCharactorSkl
	(		
		AActor* PlayerPawn, 			//Player
		TArray<USkeletalMesh*> SrcMeshList, 	//
		USkeletalMeshComponent* SkeletalComp
	);



	//-------------【关卡切换UMG动画 时间分配】--------
	//旧关卡显示 时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenLevel")
	float OldLevelTime;
	//新关卡显示时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenLevel")
	float NewLevelTime;
};
