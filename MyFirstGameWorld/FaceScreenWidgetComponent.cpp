// Fill out your copyright notice in the Description page of Project Settings.

#include "FaceScreenWidgetComponent.h"




void UFaceScreenWidgetComponent::FacwToScreen()
{
	if (MyPlayerControl)
	{
		SetWorldRotation(MyPlayerControl->GetControlRotation());
	}
}