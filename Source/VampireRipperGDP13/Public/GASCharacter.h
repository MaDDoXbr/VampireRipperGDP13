#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"    // Required to get the ASC
#include "AbilitySystemComponent.h"    // Required to get the ASC
#include "TagNotificationComponent.h"
#include "GASCharacter.generated.h"


UCLASS()
class VAMPIRERIPPERGDP13_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacter();
  
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;  

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//===== System Functions
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
  
	//===== Components
	UPROPERTY(VisibleAnywhere, Category="GAS")                     
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="GAS")
	TObjectPtr<UTagNotificationComponent> TagNotifier;
};
