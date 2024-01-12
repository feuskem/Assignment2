#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Net/UnrealNetwork.h"
#include "NetGameInstance.h"
#include "NetBaseCharacter.generated.h"

UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	BP_Face = 0,
	BP_Hair = 1,
	BP_Chest = 2,
	BP_Hands = 3,
	BP_Legs = 4,
	BP_Beard = 5,
	BP_EyeBrows = 6,
	BP_BodyType = 7,
	BP_COUNT = 8,
};

USTRUCT(BlueprintType)
struct FSMeshAssetList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> ListSkeletal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> ListStatic;
};

UCLASS()
class ANetBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ANetBaseCharacter();

	virtual void BeginPlay();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FString GetCustomizationData();
	void ParseCustomizationData(FString Data);

	UFUNCTION(BlueprintCallable)
	void ChangeBodyPart(EBodyPart index, int value, bool DirectSet);

	UFUNCTION(BlueprintCallable)
	void ChangeGender(bool isFemale);

	UFUNCTION(Server, Reliable)
	void SubmitPlayerInfoToServer(FSPlayerInfo Info);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerInfoChanged();

	//Timer for waiting PlayerState
	UFUNCTION()
	void CheckPlayerState();

	UFUNCTION()
	void CheckPlayerInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* PartFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PartHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PartBeard;

	UPROPERTY()
	UStaticMeshComponent* PartEyebrows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PartEyes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* PartHands;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* PartLegs;

	bool PlayerInfoReceived;

private:
	int BodyPartIndices[EBodyPart::BP_COUNT];


	void UpdateBodyParts();

	static FSMeshAssetList* GetBodyPartList(EBodyPart part, bool isFemale);

	FTimerHandle ClientDataCheckTimer;

};