// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyFirstGameWorldCharacter.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "BaseMonsterClass.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AMyFirstGameWorldCharacter

AMyFirstGameWorldCharacter::AMyFirstGameWorldCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//--------------创建WidgetComponent--HeroName---
	HeroNameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeroTextName"));
	HeroNameWidget->SetupAttachment(GetMesh(),FName("head"));

	Mainwidget = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyFirstGameWorldCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyFirstGameWorldCharacter::DoJumpIfCanJump); //&ACharacter::Jump
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyFirstGameWorldCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyFirstGameWorldCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyFirstGameWorldCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyFirstGameWorldCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyFirstGameWorldCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyFirstGameWorldCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyFirstGameWorldCharacter::OnResetVR);

	//绑定 显示技能栏
	PlayerInputComponent->BindAction("SkillDetail", IE_Released, this, &AMyFirstGameWorldCharacter::ShowSkillWidget);

	//绑定普通攻击
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMyFirstGameWorldCharacter::OnAttack);
}

void AMyFirstGameWorldCharacter::DoJumpIfCanJump()
{
	if (bCanJump)
	{
		ACharacter::Jump();
	}
}

void AMyFirstGameWorldCharacter::OnAttack()
{
	if (bCanAttack && !GetMovementComponent()->IsFalling())
	{
		bCanCombo = true;
		SkillEffect = E_SkillEffect::SkillEffect_NoEffect;
		switch (CurWeaponType)
		{
		case E_HeroWeaponType::HeroWeaponType_OneHandSword:
			if (!bIsAttacking)
			{
				DamageAmount = 5.f;
				bIsAttacking = true;
				bCanGrow = false;
				bCanJump = false;
				PlayMontageAtSameTime(NormalAttComboAnim[0]);
			}
			break;
		case E_HeroWeaponType::HeroWeaponType_TwoHandSword:
			break;
		default:
			break;
		}
	}
}
void AMyFirstGameWorldCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMyFirstGameWorldCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AMyFirstGameWorldCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AMyFirstGameWorldCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyFirstGameWorldCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyFirstGameWorldCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyFirstGameWorldCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//-------------【BeginPlay】--------------
void AMyFirstGameWorldCharacter::BeginPlay()
{
	Super::BeginPlay();

	bCanJump = true;

	//获取武器 碰撞区域的指针 如果获取指针成功，绑定 碰撞响应函数
	FindWeaponCollisionArea();

	if (WeaponCollisionBox)
	{
		WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyFirstGameWorldCharacter::OnOverlapBeginForWeaponCollisionBox);
	}
}

void AMyFirstGameWorldCharacter::Tick(float DeltaSeconds)
{
	FaceToScreen();

}

//-------------【CreateMainWidget】--------------
void AMyFirstGameWorldCharacter::CreateMainWidget(TSubclassOf<UMyWidget> NewWidget)
{
	if (Mainwidget)
	{
		Mainwidget->RemoveFromViewport();
		Mainwidget = nullptr;
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	AMyPlayerController * MyController = Cast<AMyPlayerController>(PlayerController);
	if (MyController)
	{
		Mainwidget = CreateWidget<UMyWidget>(MyController, NewWidget);
	}
}

//-------------【UpdataHeroStateBar】--------------
void AMyFirstGameWorldCharacter::UpdataHeroStateBar()
{
	if (Mainwidget)
	{
		if (Mainwidget->HealthBar)
		{
			Mainwidget->HealthBar->SetPercent(HeroAttribute.CurHealth / HeroAttribute.MaxHealth);
		}
		if (Mainwidget->EnergyBar)
		{
			Mainwidget->EnergyBar->SetPercent(HeroAttribute.CurEnergy / HeroAttribute.MaxEnergy);
		}
		if (Mainwidget->EnergyBar)
		{
			Mainwidget->ExpBar->SetPercent(HeroAttribute.CurExp / HeroAttribute.MaxExp);
		}
	}
}

//------------【更新Widget，使其面向屏幕】--------------------
void AMyFirstGameWorldCharacter::FaceToScreen()
{
	if (Controller)
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = - Rotation.Pitch ;
		Rotation.Yaw = Rotation.Yaw - 180.f;
		if (HeroNameWidget)
		{
			HeroNameWidget->SetWorldRotation(Rotation);
		}
	}
}

//判断能否攻击 或者 释放技能，如果可以攻击，设置相关 变量值 并输出true
bool AMyFirstGameWorldCharacter::CanDoSkill()
{
	if (GetMovementComponent()->IsFalling() || (!bCanAttack) || bIsAttacking)
	{
		return false;
	}

	bCanJump = false;
	bIsAttacking = true;
	return true;
}

//显示/隐藏 技能 Detail栏
void AMyFirstGameWorldCharacter::ShowSkillWidget()
{
	if (Mainwidget)
	{
		if (Mainwidget->SkillSystemWidget)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
			AMyPlayerController * MyController = Cast<AMyPlayerController>(PlayerController);
			
			if (Mainwidget->SkillSystemWidget->IsVisible())
			{
				Mainwidget->SkillSystemWidget->SetVisibility(ESlateVisibility::Hidden);
				MyController->SetInputMode(FInputModeGameOnly());
				MyController->bShowMouseCursor = false;
			}
			else
			{
				Mainwidget->SkillSystemWidget->SetVisibility(ESlateVisibility::Visible);
				MyController->SetInputMode(FInputModeGameAndUI());
				MyController->bShowMouseCursor = true;
			}
		}
	}
}

//游戏开始时 获取武器碰撞区域的指针
void AMyFirstGameWorldCharacter::FindWeaponCollisionArea()
{
	//获取 武器碰撞区域 
	TArray < UBoxComponent*> OutComponents;
	AMyFirstGameWorldCharacter::GetComponents(OutComponents, true);
	if (OutComponents.Num() > 0)
	{
		WeaponCollisionBox = OutComponents[0];
	}

	//获取 武器 射线计算的辅助接点
	TArray < UStaticMeshComponent*> OutShere;
	AMyFirstGameWorldCharacter::GetComponents(OutShere, true);
	if (OutShere.Num()>1)
	{
		TraceStart = OutShere[0];
		TraceEnd = OutShere[1];
	}
}

//武器碰撞 响应事件
void AMyFirstGameWorldCharacter::OnOverlapBeginForWeaponCollisionBox(
	UPrimitiveComponent* OverlappedComp,	
	AActor* OtherActor,						
	UPrimitiveComponent* OtherComp,			
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor!=nullptr && OtherActor!=this && OtherComp!=nullptr && bCanApplyDamage)
	{
		ABaseMonsterClass* TargetActor = Cast<ABaseMonsterClass>(OtherActor);
		if (TargetActor)
		{
			if (TargetActor->GetClass()->ImplementsInterface(UIApplyDamage::StaticClass()))
			{
				FVector HitLocation = SpawnWeaponTrace();
				IIApplyDamage::Execute_ApplyDamage(TargetActor, HitLocation , SkillEffect); // This is the Execute_* function. The asterisk means your function name. :)				
				IIApplyDamage::Execute_DecreateHP(TargetActor, 10.f);
			}		
		}
	}
}

//生成武器射线，检测碰撞点，返回碰撞位置
FVector AMyFirstGameWorldCharacter::SpawnWeaponTrace()
{
	FVector HitLocation(0, 0, 0);
	if (TraceStart && TraceEnd)
	{
		//计算 坐标 并生成射线
		FVector StartLocation, EndLocation;
		StartLocation = TraceStart->GetComponentLocation();
		EndLocation = TraceEnd->GetComponentLocation();
		//存放生成的射线 的碰撞结果
		TArray < struct FHitResult > OutHits;
		FVector Dir = WeaponCollisionBox->GetComponentLocation();
		
		//设置显示 射线
		FCollisionQueryParams TraceParams;
		const FName TraceTag("SightTrace");
		TraceParams.TraceTag = TraceTag;
		TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = true;
		GetWorld()->DebugDrawTraceTag = TraceTag;
		//进行 球形 射线 碰撞
		bool Succeed = GetWorld()->SweepMultiByChannel
		(
			OutHits,
			StartLocation,
			EndLocation,
			Dir.ToOrientationQuat(),
			ECollisionChannel::ECC_Visibility,
			FCollisionShape::MakeSphere(10.f),
			TraceParams
			);

// 		GetWorld()->LineTraceSingleByChannel(
// 			OutHit,
// 			StartLocation,
// 			EndLocation,
// 			ECC_Visibility
// 		);
		//获取碰撞结果，发送碰撞信息
		if (Succeed)
		{
			HitLocation = OutHits[0].Location;
		}
	}
	return HitLocation;
}


void AMyFirstGameWorldCharacter::ApplyDamage_Implementation(FVector HitLocation, E_SkillEffect Skilleffect)
{
	if (!bIsDie &&GetCurrentMontage() == nullptr && BeAttackNomal.Num()>0)
	{
		PlayMontageAtSameTime(BeAttackNomal[0]);
	}
}
void AMyFirstGameWorldCharacter::DecreateHP_Implementation(float DeHp)
{
	if (!bIsDie)
	{
		HeroAttribute.CurHealth -= DeHp;
		if (HeroAttribute.CurHealth > 0)
		{
			UpdataHeroStateBar();
		}
		else
		{
			HeroAttribute.CurHealth = 0.f;
			UpdataHeroStateBar();
			OnDie();
		}
	}
}

void AMyFirstGameWorldCharacter::OnDie()
{
	if (!bIsDie)
	{
		if (DieAnim.Num() > 0)
		{
			//播放s死亡动画
			PlayDieAnim();
			DisableInput(Cast<APlayerController>(GetController()));
		}
		bIsDie = true;
	}
}


// void AMyFirstGameWorldCharacter::PlayAnimMontageAtSameTime(class UAnimMontage* AnimMontage )
// {
// 	//播放动画
// 	PlayAnimMontage(AnimMontage);
// 
// 	if (HeroSkeletalmeshComArray.Num() > 0)
// 	{
// 		for (int i=0;i<HeroSkeletalmeshComArray.Num();i++)
// 		{
// 			if (HeroSkeletalmeshComArray[i])
// 			{
// 				HeroSkeletalmeshComArray[i]->PlayAnimation(AnimMontage,false);
// 			}
// 		}
// 	}
// }
// 
// void AMyFirstGameWorldCharacter::RsetAnimInstance(class UClass* AnimBP)
// {
// 	GetMesh()->SetAnimInstanceClass(AnimBP);
// 	if (HeroSkeletalmeshComArray.Num() > 0)
// 	{
// 		for (int i = 0; i < HeroSkeletalmeshComArray.Num(); i++)
// 		{
// 			HeroSkeletalmeshComArray[i]->SetAnimInstanceClass(AnimBP);
// 		}
// 	}
// }

