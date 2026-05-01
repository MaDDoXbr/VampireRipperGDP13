// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttrSet_vRip.generated.h"

#define	ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
			GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
			GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
			GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
			GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class VAMPIRERIPPERGDP13_API UAttrSet_vRip : public UAttributeSet
{
	GENERATED_BODY()
	
public:
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "vRip Attributes")
	FGameplayAttributeData Health = 100.0f;
			ATTRIBUTE_ACCESSORS(UAttrSet_vRip, Health)
	
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "vRip Attributes")
	FGameplayAttributeData Mana = 100.0f;
			ATTRIBUTE_ACCESSORS(UAttrSet_vRip, Mana)

			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "vRip Attributes")
	FGameplayAttributeData MaxHealth = 100.0f;
			ATTRIBUTE_ACCESSORS(UAttrSet_vRip, MaxHealth)
	
			UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "vRip Attributes")
	FGameplayAttributeData MaxMana = 100.0f;
			ATTRIBUTE_ACCESSORS(UAttrSet_vRip, MaxMana)	
	
	//---- System Events
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
