// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/SpringArmComponent.h"
#include "NetAvatar.generated.h"

/**
 * 
 */
UCLASS()
class ANetAvatar : public ANetBaseCharacter
{
	GENERATED_BODY()

	ANetAvatar();
public:

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_PlayerSpeedChanged)
	float Speed;

	UPROPERTY(BlueprintReadWrite)
	float WalkSpeed;

	UPROPERTY(BlueprintReadWrite)
	float RunSpeed;

	UFUNCTION()
	void OnRep_PlayerSpeedChanged();

	UFUNCTION(Server, Reliable)
	void ChangingSpeed(float Amount);



	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void RunPressed();
	void RunReleased();
	
};
