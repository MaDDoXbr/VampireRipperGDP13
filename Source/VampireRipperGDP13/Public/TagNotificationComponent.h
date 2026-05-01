// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "TagNotificationComponent.generated.h"

UCLASS( ClassGroup=(GAS), meta=(BlueprintSpawnableComponent) )
class VAMPIRERIPPERGDP13_API UTagNotificationComponent : public UActorComponent
{
	GENERATED_BODY()

	//FGameplayTag* Tag;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagChanged, FGameplayTag, Tag);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagsChanged, FGameplayTagContainer, TagContainer);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSubscribedTagChanged, FGameplayTag, Tag, bool, bIsPreset);
	
public:	
	UTagNotificationComponent();
	
				UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	void RegisterSpecificTag(FGameplayTag Tag);
	
				UFUNCTION(BlueprintCallable, Category = "GameplayTags")	
	void UnregisterSpecificTag(FGameplayTag Tag);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

				UPROPERTY(BlueprintAssignable, Category = "GameplayTags|General")
	FOnGameplayTagChanged OnTagAdded;
				UPROPERTY(BlueprintAssignable, Category = "GameplayTags|General")	
	FOnGameplayTagChanged OnTagRemoved;	

				UPROPERTY(BlueprintAssignable, Category = "GameplayTags|General")
	FOnGameplayTagsChanged OnTagsAdded;
				UPROPERTY(BlueprintAssignable, Category = "GameplayTags|General")	
	FOnGameplayTagsChanged OnTagsRemoved;
	
	//---- Specific delegates
	FOnSubscribedTagChanged OnSubscribedTagChanged;
	
	//---- Temp variables
	FGameplayTagContainer PendingAdded;
	FGameplayTagContainer PendingRemoved;
	
private:
	void OnAnyTagUpdated(const FGameplayTag Tag, int32 NewCount);
	
	void OnSpecificTagUpdated(const FGameplayTag Tag, int32 NewCount);
	
				UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> CachedASC;
	
	FDelegateHandle GenericTagEventHandle;
	
	TMap<FGameplayTag, FDelegateHandle> DelegateHandles;
};
