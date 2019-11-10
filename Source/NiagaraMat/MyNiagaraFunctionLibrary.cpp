// Fill out your copyright notice in the Description page of Project Settings.

#include "MyNiagaraFunctionLibrary.h"
#include "Materials/MaterialInstance.h"
#include "NiagaraComponent.h"
#include "Materials/MaterialInstance.h"
#include "Runtime/Engine/Private/Materials/MaterialInstanceSupport.h"

template <typename ParameterType>
void GameThread_UpdateMIParameter(const UMaterialInstance* Instance, const ParameterType& Parameter)
{
	FMaterialInstanceResource* Resource = Instance->Resource;
	const FMaterialParameterInfo& ParameterInfo = Parameter.ParameterInfo;
	typename ParameterType::ValueType Value = ParameterType::GetValue(Parameter);
	ENQUEUE_RENDER_COMMAND(SetMIParameterValue)(
		[Resource, ParameterInfo, Value](FRHICommandListImmediate& RHICmdList)
	{
		Resource->RenderThread_UpdateParameter(ParameterInfo, Value);
	});
}

void UMyNiagaraFunctionLibrary::UpdateVectorParam(UNiagaraComponent* NiagComp, FName Name, FLinearColor NewVal)
{
	TArray<UMaterialInterface*> Materials;

	NiagComp->GetUsedMaterials(Materials);

	for (int32 i = 0; i < Materials.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Materials[i]->GetName())

		UMaterialInstance* Inst = Cast<UMaterialInstance>(Materials[i]);
		if (Inst)
		{
			for (int32 j = 0; j < Inst->VectorParameterValues.Num(); j++)
			{
				if (Inst->VectorParameterValues[j].ParameterInfo.Name == Name)
				{
					FVectorParameterValue* ParameterValue = &Inst->VectorParameterValues[j];
					if (ParameterValue)
					{
						ParameterValue->ParameterValue = NewVal;

						GameThread_UpdateMIParameter(Inst, *ParameterValue);

						Inst->Resource->CacheUniformExpressions_GameThread(false);
					}
				}
			}
		}
	}
}

void UMyNiagaraFunctionLibrary::UpdateTextureParam(UNiagaraComponent* NiagComp, FName Name, UTexture* NewVal)
{
	TArray<UMaterialInterface*> Materials;

	NiagComp->GetUsedMaterials(Materials);

	for (int32 i = 0; i < Materials.Num(); i++)
	{
		UMaterialInstance* Inst = Cast<UMaterialInstance>(Materials[i]);
		if (Inst)
		{
			for (int32 j = 0; j < Inst->TextureParameterValues.Num(); j++)
			{
				if (Inst->TextureParameterValues[j].ParameterInfo.Name == Name)
				{
					FTextureParameterValue* ParameterValue = &Inst->TextureParameterValues[j];
					if (ParameterValue)
					{
						ParameterValue->ParameterValue = NewVal;

						GameThread_UpdateMIParameter(Inst, *ParameterValue);

						Inst->Resource->CacheUniformExpressions_GameThread(false);
					}
				}
			}
		}
	}
}

void UMyNiagaraFunctionLibrary::UpdateScalarParam(UNiagaraComponent* NiagComp, FName Name, float NewVal)
{
	TArray<UMaterialInterface*> Materials;

	NiagComp->GetUsedMaterials(Materials);

	for (int32 i = 0; i < Materials.Num(); i++)
	{
		UMaterialInstance* Inst = Cast<UMaterialInstance>(Materials[i]);
		if (Inst)
		{
			for (int32 j = 0; j < Inst->ScalarParameterValues.Num(); j++)
			{
				if (Inst->ScalarParameterValues[j].ParameterInfo.Name == Name)
				{
					FScalarParameterValue* ParameterValue = &Inst->ScalarParameterValues[j];
					if (ParameterValue)
					{
						ParameterValue->ParameterValue = NewVal;

						GameThread_UpdateMIParameter(Inst, *ParameterValue);

						Inst->Resource->CacheUniformExpressions_GameThread(false);
					}
				}
			}
		}
	}
}
