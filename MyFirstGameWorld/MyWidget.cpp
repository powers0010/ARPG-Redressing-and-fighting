// Fill out your copyright notice in the Description page of Project Settings.

#include "MyWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyFirstGameWorldCharacter.h"
#include "MyPlayerController.h"


UMyWidget::UMyWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	HealthBar = nullptr;
	EnergyBar = nullptr;
	ExpBar = nullptr;

	FindPlayerCharactor();
}

bool UMyWidget::Initialize()
{
 	if (!Super::Initialize())
 	{
 		return false;
 	}
	if (UProgressBar * LocalHealthbar = Cast<UProgressBar>(GetWidgetFromName("HealthBar")))
	{
		HealthBar = LocalHealthbar;
	}
	if (UProgressBar * LocalEnergybar = Cast<UProgressBar>(GetWidgetFromName("EnergyBar")))
	{
		EnergyBar = LocalEnergybar;
	}
	if (UProgressBar * LocalExpbar = Cast<UProgressBar>(GetWidgetFromName("ExpBar")))
	{
		ExpBar = LocalExpbar;
	}
	return true;
}

//获取玩家角色
void UMyWidget::FindPlayerCharactor()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	AMyPlayerController* MyController = Cast<AMyPlayerController>(PlayerController);
	if (MyController)
	{
		AMyFirstGameWorldCharacter* LocalPlayer = Cast<AMyFirstGameWorldCharacter>(MyController->GetPawn());
		if (LocalPlayer)
		{
			MyPlayerREF = LocalPlayer;
		}
	}
}