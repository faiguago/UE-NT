// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyNiagaraFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class NIAGARAMAT_API UMyNiagaraFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Niagara")
	static void UpdateVectorParam(UNiagaraComponent* NiagComp, FName Name, FLinearColor NewVal);

	UFUNCTION(BlueprintCallable, Category = "Niagara")
	static void UpdateTextureParam(UNiagaraComponent* NiagComp, FName Name, UTexture* NewVal);

	UFUNCTION(BlueprintCallable, Category = "Niagara")
	static void UpdateScalarParam(UNiagaraComponent* NiagComp, FName Name, float NewVal);
};
