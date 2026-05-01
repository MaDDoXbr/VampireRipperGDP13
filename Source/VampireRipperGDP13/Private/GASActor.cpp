// Fill out your copyright notice in the Description page of Project Settings.


#include "GASActor.h"


// Sets default values
AGASActor::AGASActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	TagNotifier = CreateDefaultSubobject<UTagNotificationComponent>(TEXT("TagNotifier"));

}

UAbilitySystemComponent* AGASActor::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

void AGASActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGASActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

