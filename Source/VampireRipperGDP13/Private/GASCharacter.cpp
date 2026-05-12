#include "GASCharacter.h"


// Sets default values
AGASCharacter::AGASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Create the ASC automatically as soon as a GASActor blueprint is created
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	TagNotifier = CreateDefaultSubobject<UTagNotificationComponent>(TEXT("TagNotifier"));
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
