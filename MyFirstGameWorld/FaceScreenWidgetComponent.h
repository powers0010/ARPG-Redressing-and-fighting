// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"
#include "Components/WidgetComponent.h"
#include "FaceScreenWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTGAMEWORLD_API UFaceScreenWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

		AMyPlayerController * MyPlayerControl;
		
		void FacwToScreen();
	
	
};
