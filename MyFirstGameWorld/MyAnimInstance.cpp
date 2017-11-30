// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"


void UMyAnimInstance::CaculateOwnerparameter()
{
	//¼ÆËãËÙ¶È
	FVector SpeedVec = AnimOwner->GetVelocity();
	SpeedVec.Z = 0.f;
	speed = SpeedVec.Size();

	bIsInAir = AnimOwner->GetMovementComponent()->IsFalling();

	bIsEqip = AnimOwner->bIsEqip;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AnimOwner = Cast<AMyFirstGameWorldCharacter>(TryGetPawnOwner());
	if (AnimOwner)
	{
		CaculateOwnerparameter();
	}
}
