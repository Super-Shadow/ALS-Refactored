#include "Notify/AlsAnimNotifyState_SetLocomotionAction.h"

#include "AlsCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "State/Enumerations/AlsLocomotionAction.h"
#include "Utility/AlsEnumerationUtility.h"

UAlsAnimNotifyState_SetLocomotionAction::UAlsAnimNotifyState_SetLocomotionAction()
{
	bIsNativeBranchingPoint = true;
}

FString UAlsAnimNotifyState_SetLocomotionAction::GetNotifyName_Implementation() const
{
	return FString::Format(TEXT("Als Set Locomotion Action: {0}"), {GetEnumValueString(Action)});
}

void UAlsAnimNotifyState_SetLocomotionAction::NotifyBegin(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation,
                                                          const float TotalDuration)
{
	Super::NotifyBegin(MeshComponent, Animation, TotalDuration);

	auto* Character{Cast<AAlsCharacter>(MeshComponent->GetOwner())};
	if (IsValid(Character))
	{
		Character->SetLocomotionAction(Action);
	}
}

void UAlsAnimNotifyState_SetLocomotionAction::NotifyEnd(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComponent, Animation);

	auto* Character{Cast<AAlsCharacter>(MeshComponent->GetOwner())};
	if (IsValid(Character) && Character->GetLocomotionAction() == Action)
	{
		Character->SetLocomotionAction(EAlsLocomotionAction::None);
	}
}
