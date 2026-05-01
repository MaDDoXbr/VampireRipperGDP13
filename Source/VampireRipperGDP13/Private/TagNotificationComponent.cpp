
#include "TagNotificationComponent.h"

// Sets default values for this component's properties
UTagNotificationComponent::UTagNotificationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTagNotificationComponent::BeginPlay()
{
	Super::BeginPlay();

	IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(GetOwner());
	
	if (!ASInterface)
		return;
	
	CachedASC = ASInterface->GetAbilitySystemComponent();
	if (!CachedASC)
		return;
	
	GenericTagEventHandle = CachedASC->RegisterGenericGameplayTagEvent().AddUObject(this, &UTagNotificationComponent::OnAnyTagUpdated);
	
}

void UTagNotificationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Lambda to handle the batching logic for both Added and Removed
	auto ProcessBatch = [&](FGameplayTagContainer& Container, FOnGameplayTagChanged& Single, FOnGameplayTagsChanged& Multi) {
		if (!Container.IsEmpty()) {
			Multi.Broadcast(Container);
			TArray<FGameplayTag> Tags;
			Container.GetGameplayTagArray(Tags);
			Single.Broadcast(Tags[0]);
			Container.Reset();
		}
	};

	ProcessBatch(PendingAdded, OnTagAdded, OnTagsAdded);
	ProcessBatch(PendingRemoved, OnTagRemoved, OnTagsRemoved);
}

void UTagNotificationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	// Clean up specific tag listeners to prevent stale pointers/crashes
	if (CachedASC) {
		CachedASC->RegisterGenericGameplayTagEvent().Remove(GenericTagEventHandle);

		for (const auto& KVP : DelegateHandles) {
			CachedASC->RegisterGameplayTagEvent(KVP.Key, EGameplayTagEventType::AnyCountChange).Remove(KVP.Value);
		}
	}
	Super::EndPlay(EndPlayReason);
}

//===== Tag Notification Events

void UTagNotificationComponent::OnAnyTagUpdated(const FGameplayTag Tag, int32 NewCount) {
	if (NewCount > 0)
		PendingAdded.AddTag(Tag);
	else PendingRemoved.AddTag(Tag);
}

void UTagNotificationComponent::OnSpecificTagUpdated(const FGameplayTag Tag, int32 NewCount) {
	OnSubscribedTagChanged.Broadcast(Tag, NewCount > 0);
}

void UTagNotificationComponent::RegisterSpecificTag(FGameplayTag Tag) {
	if (!(CachedASC && Tag.IsValid() && !DelegateHandles.Contains(Tag)))
		return;
	
	// Bind to ASC's native tag change event
	FDelegateHandle Handle = CachedASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::AnyCountChange)
		.AddUObject(this, &UTagNotificationComponent::OnSpecificTagUpdated);
    
	DelegateHandles.Add(Tag, Handle);

	// Broadcast immediate current state upon registration (optional)
	OnSpecificTagUpdated(Tag, CachedASC->GetTagCount(Tag));
}

void UTagNotificationComponent::UnregisterSpecificTag(FGameplayTag Tag) {
	if (!(CachedASC && DelegateHandles.Contains(Tag))) 
			return;
	CachedASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::AnyCountChange).Remove(DelegateHandles[Tag]);
	DelegateHandles.Remove(Tag);
}