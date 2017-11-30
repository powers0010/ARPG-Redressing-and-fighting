// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Runtime/Engine/Public/SkeletalMeshMerge.h"	//将一个骨骼网格列表合并成一个单一网格的实用工具。

bool UMyGameInstance::MergeMyCharactorSkl
(	AActor* PlayerPawn, 			//Player
	TArray<USkeletalMesh*> SrcMeshList, 	//
	USkeletalMeshComponent* SkeletalComp
)
{
	if (!PlayerPawn || !SkeletalComp || SrcMeshList.Num() == 0) return false;

	TArray<USkeletalMesh*>& SourceMeshList = SrcMeshList;
	auto CompositeMesh = NewObject<USkeletalMesh>(NULL, USkeletalMesh::StaticClass());
	TArray<FSkelMeshMergeSectionMapping> InForceSectionMapping;
	FSkeletalMeshMerge MeshMergeUtil(CompositeMesh, SourceMeshList, InForceSectionMapping, 0);
	if (!MeshMergeUtil.DoMerge())
	{
		return false;
	}
	CompositeMesh->Skeleton = SkeletalComp->SkeletalMesh->Skeleton;					//设置新的 *SkeletalMesh* 的骨架
	SkeletalComp->SetSkeletalMesh(CompositeMesh);									//用新组合成的 SkeletalMesh 替换旧的
	return true;
}

