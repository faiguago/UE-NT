// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DatasToUpdate.generated.h"

USTRUCT()
struct FTexInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	UTexture* Val;
};

USTRUCT()
struct FVectorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	FLinearColor Val;
};

USTRUCT()
struct FScalarInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	float Val;
};


UCLASS()
class NIAGARAMAT_API UItemsDatabase : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TArray<FTexInfo> TexValues;

	UPROPERTY(EditAnywhere)
	TArray<FVectorInfo> VectorValues;

	UPROPERTY(EditAnywhere)
	TArray<FScalarInfo> ScalarValues;

};