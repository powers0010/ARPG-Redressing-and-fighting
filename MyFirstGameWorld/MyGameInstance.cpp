// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Runtime/Engine/Public/SkeletalMeshMerge.h"	//��һ�����������б�ϲ���һ����һ�����ʵ�ù��ߡ�

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
	CompositeMesh->Skeleton = SkeletalComp->SkeletalMesh->Skeleton;					//�����µ� *SkeletalMesh* �ĹǼ�
	SkeletalComp->SetSkeletalMesh(CompositeMesh);									//������ϳɵ� SkeletalMesh �滻�ɵ�
	return true;
}

