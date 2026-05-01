// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "TagNotificationComponent.h"
#include "GASActor.generated.h"

UCLASS()
class VAMPIRERIPPERGDP13_API AGASActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AGASActor();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<UTagNotificationComponent> TagNotifier;
	
public:	
	virtual void Tick(float DeltaTime) override;

};
