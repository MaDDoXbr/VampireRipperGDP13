// Fill out your copyright notice in the Description page of Project Settings.


#include "VertexTools.h"

void UVertexTools::GetComponentByInterface(AActor* TargetActor, TSubclassOf<UInterface> Interface,
	ESearchResult& Result, UActorComponent*& OutComponent) {
	
	if (!TargetActor || !Interface) 
		return;
	
	//default "not found" result
	OutComponent = nullptr;
	Result = ESearchResult::NotFound;
	
	TArray<UActorComponent*> AllComponents;
	TargetActor->GetComponents(AllComponents);
	
	for (UActorComponent* Comp: AllComponents) {
		if (Comp && Comp->GetClass()->ImplementsInterface(Interface) ) {
			OutComponent = Comp;
			Result = ESearchResult::Found;
			return;
		}
	}
	
}
