// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraExt.generated.h"

class UNiagaraComponent;

UCLASS()
class NIAGARAMAT_API ANiagaraExt : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANiagaraExt();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NiagComp;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	   	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	class UItemsDatabase* ParamsToSet;

private:

	void UpdateParameters();

	void CreateMaterials();

	void UpdateScalarParam(FName Name, float Val);

	void UpdateTextureParam(FName Name, UTexture* Val);

	void UpdateVectorParam(FName Name, FLinearColor Val);

protected:

	UPROPERTY(VisibleAnywhere, Transient)
	TArray<UMaterialInstanceDynamic*> Materials;

};
