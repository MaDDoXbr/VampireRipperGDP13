// Fill out your copyright notice in the Description page of Project Settings.


#include "AttrSet_vRip.h"

void UAttrSet_vRip::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute()) {
		UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
		
		const float CurrentHealthValue = Health.GetCurrentValue();	// after effects/modifiers are applied
		auto FinalValue = FMath::Clamp<float>(CurrentHealthValue, 0.f, MaxHealth.GetBaseValue());
		//Health.SetCurrentValue(FinalValue);
		if (!FMath::IsNearlyEqual(CurrentHealthValue, FinalValue)) {	//0.000001, 0.000000 => True
			AbilityComp->ApplyModToAttributeUnsafe(Attribute, EGameplayModOp::Override, FinalValue);	
		}
	}
}
