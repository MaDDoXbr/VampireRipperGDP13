// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VertexTools.generated.h"

UENUM(BlueprintType)
enum class ESearchResult: uint8 { Found, NotFound };

UCLASS()
class VAMPIRERIPPERGDP13_API UVertexTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
					UFUNCTION(BlueprintCallable, Category = "VertexTools", Meta = (ExpandEnumAsExecs = "Result", DeterminesOutputType = "Interface"))
	static void GetComponentByInterface(
			AActor* TargetActor,
			TSubclassOf<UInterface> Interface,
			ESearchResult& Result,	//use & for output pins
			UActorComponent*& OutComponent
	);
	
};
