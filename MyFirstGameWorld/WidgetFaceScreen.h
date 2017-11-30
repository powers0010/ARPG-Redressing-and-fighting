// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetFaceScreen.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMEWORLD_API UWidgetFaceScreen : public UUserWidget
{
	GENERATED_BODY()

		//旋转角度 面向屏幕
		void FaceToScreen();
	
};
