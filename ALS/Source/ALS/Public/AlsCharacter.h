#pragma once

#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Settings/AlsInAirRotationMode.h"
#include "Settings/AlsMantlingSettings.h"
#include "Settings/AlsMovementCharacterSettings.h"
#include "Settings/AlsRagdollingSettings.h"
#include "Settings/AlsRollingSettings.h"
#include "State/Enumerations/AlsGait.h"
#include "State/Enumerations/AlsLocomotionAction.h"
#include "State/Enumerations/AlsLocomotionMode.h"
#include "State/Enumerations/AlsRotationMode.h"
#include "State/Enumerations/AlsStance.h"
#include "State/Enumerations/AlsViewMode.h"
#include "State/Structures/AlsLocomotionCharacterState.h"
#include "State/Structures/AlsMantlingState.h"
#include "State/Structures/AlsRagdollingCharacterState.h"
#include "State/Structures/AlsViewCharacterState.h"

#include "AlsCharacter.generated.h"

enum class EAlsMantlingType : uint8;
class UAlsCharacterMovementComponent;
class UTimelineComponent;

UCLASS()
class ALS_API AAlsCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TWeakObjectPtr<UAlsCharacterMovementComponent> AlsCharacterMovement;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	UTimelineComponent* MantlingTimeline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess, ClampMin = 0))
	float MovingSpeedThreshold{150.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess))
	bool bSprintHasPriorityOverAiming;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess))
	bool bRotateToVelocityWhenSprinting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess))
	EAlsInAirRotationMode InAirRotationMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess))
	bool bAllowAimingWhenInAir{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated,
		Meta = (AllowPrivateAccess))
	EAlsStance DesiredStance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated,
		Meta = (AllowPrivateAccess))
	EAlsGait DesiredGait{EAlsGait::Running};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State",
		ReplicatedUsing = "OnReplicate_DesiredAiming", Meta = (AllowPrivateAccess))
	bool bDesiredAiming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated,
		Meta = (AllowPrivateAccess))
	EAlsRotationMode DesiredRotationMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State", Replicated,
		Meta = (AllowPrivateAccess))
	EAlsViewMode ViewMode{EAlsViewMode::ThirdPerson};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character|Desired State",
		ReplicatedUsing = "OnReplicate_OverlayMode", Meta = (AllowPrivateAccess))
	FGameplayTag OverlayMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character",
		Meta = (AllowPrivateAccess, DisplayName = "Mantling Settings"))
	FAlsGeneralMantlingSettings GeneralMantlingSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess))
	FAlsRagdollingSettings RagdollingSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess))
	FAlsRollingSettings RollingSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Als Character", Meta = (AllowPrivateAccess))
	UAlsMovementCharacterSettings* MovementSettings;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	EAlsStance Stance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	EAlsGait Gait;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	EAlsRotationMode RotationMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	EAlsLocomotionMode LocomotionMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	EAlsLocomotionAction LocomotionAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Replicated, Meta = (AllowPrivateAccess))
	FVector_NetQuantizeNormal InputDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	FAlsLocomotionCharacterState LocomotionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Replicated, Meta = (AllowPrivateAccess))
	FRotator ViewRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	FAlsViewCharacterState ViewState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	FAlsMantlingState MantlingState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Replicated, Meta = (AllowPrivateAccess))
	FVector_NetQuantize RagdollTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	FAlsRagdollingCharacterState RagdollingState;

	FTimerHandle LandedGroundFrictionResetTimer;

	static const FCollisionObjectQueryParams MantlingAndRagdollObjectQueryParameters;

public:
	AAlsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Restart() override;

	virtual void Tick(float DeltaTime) override;

	virtual void AddMovementInput(FVector Direction, float Scale = 1.0f, bool bForce = false) override;

	virtual void Jump() override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMode, uint8 PreviousCustomMode = 0) override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual void OnJumped_Implementation() override;

	virtual void Landed(const FHitResult& Hit) override;

	// Desired Stance

public:
	EAlsStance GetDesiredStance() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void SetDesiredStance(EAlsStance NewStance);

private:
	UFUNCTION(Server, Reliable)
	void ServerSetDesiredStance(EAlsStance NewStance);

	void ApplyDesiredStance();

	// Stance

public:
	EAlsStance GetStance() const;

private:
	void SetStance(EAlsStance NewStance);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnStanceChanged(EAlsStance PreviousStance);

	// Desired Gait

public:
	EAlsGait GetDesiredGait() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void SetDesiredGait(EAlsGait NewGait);

private:
	UFUNCTION(Server, Reliable)
	void ServerSetDesiredGait(EAlsGait NewGait);

	// Gait

public:
	EAlsGait GetGait() const;

private:
	void SetGait(EAlsGait NewGait);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnGaitChanged(EAlsGait PreviousGait);

private:
	void RefreshGait();

	EAlsGait CalculateMaxAllowedGait() const;

	EAlsGait CalculateActualGait(EAlsGait MaxAllowedGait) const;

	bool CanSprint() const;

	// Desired Aiming

public:
	bool IsDesiredAiming() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void SetDesiredAiming(bool bNewDesiredAiming);

private:
	UFUNCTION(Server, Reliable)
	void ServerSetDesiredAiming(bool bNewDesiredAiming);

	UFUNCTION()
	void OnReplicate_DesiredAiming(bool bPreviousDesiredAiming);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnDesiredAimingChanged(bool bPreviousDesiredAiming);

	// Desired Rotation Mode

public:
	EAlsRotationMode GetDesiredRotationMode() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void SetDesiredRotationMode(EAlsRotationMode NewMode);

private:
	UFUNCTION(Server, Reliable)
	void ServerSetDesiredRotationMode(EAlsRotationMode NewMode);

	// Rotation Mode

public:
	EAlsRotationMode GetRotationMode() const;

private:
	void SetRotationMode(EAlsRotationMode NewMode);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnRotationModeChanged(EAlsRotationMode PreviousMode);

	void RefreshRotationMode();

	// View Mode

public:
	EAlsViewMode GetViewMode() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void SetViewMode(EAlsViewMode NewMode);

private:
	UFUNCTION(Server, Reliable)
	void ServerSetViewMode(EAlsViewMode NewMode);

	// Overlay Mode

public:
	const FGameplayTag& GetOverlayMode() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void SetOverlayMode(const FGameplayTag& NewMode);

private:
	UFUNCTION(Server, Reliable)
	void ServerSetOverlayMode(const FGameplayTag& NewMode);

	UFUNCTION()
	void OnReplicate_OverlayMode(const FGameplayTag& PreviousMode);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnOverlayModeChanged(const FGameplayTag& PreviousMode);

	// Locomotion Mode

public:
	EAlsLocomotionMode GetLocomotionMode() const;

private:
	void SetLocomotionMode(EAlsLocomotionMode NewMode);

	void NotifyLocomotionModeChanged(EAlsLocomotionMode PreviousMode);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnLocomotionModeChanged(EAlsLocomotionMode PreviousMode);

	// Locomotion Action

public:
	EAlsLocomotionAction GetLocomotionAction() const;

	void SetLocomotionAction(EAlsLocomotionAction NewAction);

	void NotifyLocomotionActionChanged(EAlsLocomotionAction PreviousAction);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnLocomotionActionChanged(EAlsLocomotionAction PreviousAction);

	// Locomotion

public:
	const FVector& GetInputDirection() const;

	const FAlsLocomotionCharacterState& GetLocomotionState() const;

private:
	void SetInputDirection(FVector NewInputDirection);

	FTransform CalculateNetworkSmoothedTransform() const;

	void RefreshLocomotionLocationAndRotation();

	void RefreshLocomotion(float DeltaTime);

	// View

public:
	virtual FRotator GetViewRotation() const override;

private:
	void SetViewRotation(const FRotator& NewViewRotation);

public:
	const FAlsViewCharacterState& GetViewState() const;

private:
	void RefreshView(float DeltaTime);

	// Rotation

private:
	void RefreshGroundedActorRotation(float DeltaTime);

protected:
	virtual bool TryRefreshCustomGroundedMovingActorRotation(float DeltaTime);

	virtual bool TryRefreshCustomGroundedNotMovingActorRotation(float DeltaTime);

	void RefreshGroundedMovingAimingActorRotation(float DeltaTime);

	void RefreshGroundedNotMovingAimingActorRotation(float DeltaTime);

	float CalculateActorRotationSpeed() const;

private:
	void RefreshInAirActorRotation(float DeltaTime);

protected:
	virtual bool TryRefreshCustomInAirActorRotation(float DeltaTime);

	void RefreshInAirAimingActorRotation(float DeltaTime);

	void RefreshActorRotation(const float TargetYawAngle, const float DeltaTime,
	                          const float RotationSpeed, bool bRefreshTargetYawAngle = true);

	void RefreshActorRotationExtraSmooth(const float TargetYawAngle, const float DeltaTime, const float TargetRotationSpeed,
	                                     const float ActorRotationSpeed, bool bRefreshTargetYawAngle = true);

	// Jumping

private:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnJumpedNetworked();

	void OnJumpedNetworked();

	// Landing

private:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnLandedNetworked();

	void OnLandedNetworked();

	void OnLandedGroundFrictionReset() const;

	// Mantling

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	bool TryStartMantlingGrounded();

private:
	bool TryStartMantlingInAir();

	bool IsMantlingAllowedToStart() const;

	bool TryStartMantling(const FAlsMantlingTraceSettings& TraceSettings);

	UFUNCTION(Server, Reliable)
	void ServerStartMantling(const FAlsMantlingParameters& Parameters);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartMantling(const FAlsMantlingParameters& Parameters);

	void StartMantlingImplementation(const FAlsMantlingParameters& Parameters);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	FAlsMantlingSettings SelectMantlingSettings(EAlsMantlingType MantlingType);

	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnMantlingStarted(const FAlsMantlingParameters& Parameters);

private:
	UFUNCTION()
	void OnMantlingTimelineUpdated(float BlendInTime);

	UFUNCTION()
	void OnMantlingTimelineEnded();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnMantlingEnded();

	// Ragdolling

private:
	bool IsRagdollingAllowedToStart() const;

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void StartRagdolling();

private:
	UFUNCTION(Server, Reliable)
	void ServerStartRagdolling();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartRagdolling();

	void StartRagdollingImplementation();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnRagdollingStarted();

private:
	bool IsRagdollingAllowedToStop() const;

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	bool TryStopRagdolling();

private:
	UFUNCTION(Server, Reliable)
	void ServerStopRagdolling();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStopRagdolling();

	void StopRagdollingImplementation();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	UAnimMontage* SelectGetUpMontage(bool bRagdollFacedUpward);

	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	void OnRagdollingEnded();

private:
	void SetRagdollTargetLocation(const FVector& NewLocation);

	UFUNCTION(Server, Unreliable)
	void ServerSetRagdollTargetLocation(const FVector& NewLocation);

	void RefreshRagdolling(float DeltaTime);

	void RefreshRagdollingActorTransform(float DeltaTime);

	// Rolling

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void TryStartRolling(float PlayRate = 1.0f);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	UAnimMontage* SelectRollMontage();

private:
	bool IsRollingAllowedToStart(const UAnimMontage* Montage) const;

	void StartRolling(float PlayRate, float TargetYawAngle);

	UFUNCTION(Server, Reliable)
	void ServerStartRolling(UAnimMontage* Montage, float PlayRate, float TargetYawAngle);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartRolling(UAnimMontage* Montage, float PlayRate, float TargetYawAngle);

	void StartRollingImplementation(UAnimMontage* Montage, float PlayRate, float TargetYawAngle);

	// Debug

public:
	virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& Unused, float& VerticalPosition) override;

private:
	static void DisplayDebugHeader(const UCanvas* Canvas, const FText& HeaderText, const FLinearColor& HeaderColor,
	                               float Scale, float HorizontalPosition, float& VerticalPosition);

	void DisplayDebugCurves(const UCanvas* Canvas, float Scale, float HorizontalPosition, float& VerticalPosition) const;

	void DisplayDebugState(const UCanvas* Canvas, float Scale, float HorizontalPosition, float& VerticalPosition) const;

	void DisplayDebugShapes(const UCanvas* Canvas, float Scale, float HorizontalPosition, float& VerticalPosition) const;

	void DisplayDebugTraces(const UCanvas* Canvas, float Scale, float HorizontalPosition, float& VerticalPosition) const;

	void DisplayDebugMantling(const UCanvas* Canvas, float Scale, float HorizontalPosition, float& VerticalPosition) const;
};

inline const FVector& AAlsCharacter::GetInputDirection() const
{
	return InputDirection;
}

inline const FAlsLocomotionCharacterState& AAlsCharacter::GetLocomotionState() const
{
	return LocomotionState;
}

inline const FAlsViewCharacterState& AAlsCharacter::GetViewState() const
{
	return ViewState;
}

inline EAlsStance AAlsCharacter::GetDesiredStance() const
{
	return DesiredStance;
}

inline EAlsStance AAlsCharacter::GetStance() const
{
	return Stance;
}

inline EAlsGait AAlsCharacter::GetDesiredGait() const
{
	return DesiredGait;
}

inline EAlsGait AAlsCharacter::GetGait() const
{
	return Gait;
}

inline bool AAlsCharacter::IsDesiredAiming() const
{
	return bDesiredAiming;
}

inline EAlsRotationMode AAlsCharacter::GetDesiredRotationMode() const
{
	return DesiredRotationMode;
}

inline EAlsRotationMode AAlsCharacter::GetRotationMode() const
{
	return RotationMode;
}

inline EAlsViewMode AAlsCharacter::GetViewMode() const
{
	return ViewMode;
}

inline const FGameplayTag& AAlsCharacter::GetOverlayMode() const
{
	return OverlayMode;
}

inline EAlsLocomotionMode AAlsCharacter::GetLocomotionMode() const
{
	return LocomotionMode;
}

inline EAlsLocomotionAction AAlsCharacter::GetLocomotionAction() const
{
	return LocomotionAction;
}
