// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraExt.h"
#include "NiagaraComponent.h"
#include "NiagaraRenderer.h"
#include "DatasToUpdate.h"

// Sets default values
ANiagaraExt::ANiagaraExt()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	NiagComp = CreateDefaultSubobject<UNiagaraComponent>("Niagara Comp.");
	NiagComp->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
}

// Called when the game starts or when spawned
void ANiagaraExt::BeginPlay()
{
	Super::BeginPlay();

	UpdateParameters();
}

// Called every frame
void ANiagaraExt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANiagaraExt::UpdateParameters()
{
	if (!ParamsToSet)
		return;

	CreateMaterials();

	for (int32 i = 0; i < ParamsToSet->TexValues.Num(); i++)
		UpdateTextureParam(ParamsToSet->TexValues[i].Name, ParamsToSet->TexValues[i].Val);

	for (int32 i = 0; i < ParamsToSet->VectorValues.Num(); i++)
		UpdateVectorParam(ParamsToSet->VectorValues[i].Name, ParamsToSet->VectorValues[i].Val);

	for (int32 i = 0; i < ParamsToSet->ScalarValues.Num(); i++)
		UpdateScalarParam(ParamsToSet->ScalarValues[i].Name, ParamsToSet->ScalarValues[i].Val);
}

void ANiagaraExt::CreateMaterials()
{
	if (NiagComp->SceneProxy)
	{
		FNiagaraSceneProxy* NiagaraProxy = static_cast<FNiagaraSceneProxy*>(NiagComp->SceneProxy);
		
		for (NiagaraRenderer* Renderer : NiagaraProxy->GetEmitterRenderers())
		{
			UMaterialInterface* Mat = Renderer->GetMaterial();
			UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(Mat);
			if (!MID)
				MID = UMaterialInstanceDynamic::Create(Mat, this, NAME_None);

			Materials.Add(MID);
			Renderer->SetMaterial(MID, ERHIFeatureLevel::Type::SM5);
		}
	}
}

void ANiagaraExt::UpdateScalarParam(FName Name, float Val)
{
	for (UMaterialInstanceDynamic* Mat : Materials)
		Mat->SetScalarParameterValue(Name, Val);
}

void ANiagaraExt::UpdateTextureParam(FName Name, UTexture* Val)
{
	for (UMaterialInstanceDynamic* Mat : Materials)
		Mat->SetTextureParameterValue(Name, Val);
}

void ANiagaraExt::UpdateVectorParam(FName Name, FLinearColor Val)
{
	for (UMaterialInstanceDynamic* Mat : Materials)
		Mat->SetVectorParameterValue(Name, Val);
}
