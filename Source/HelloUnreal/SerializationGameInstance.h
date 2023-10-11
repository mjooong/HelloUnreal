// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "SerializationGameInstance.generated.h"

struct FStudentData
{
	FStudentData() {}
	FStudentData(int32 InOrder, const FString& InName) : Order(InOrder), Name(InName) {}

	friend FArchive& operator<<(FArchive& Ar, FStudentData& InStudentData)
	{
		Ar << InStudentData.Order;
		Ar << InStudentData.Name;
		return Ar;
	}

	int32 Order = -1;
	FString Name = TEXT("홍길동");

};

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API USerializationGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:
	USerializationGameInstance();

	virtual void Init() override;

	void SaveStudentPackage() const;
	void LoadStudentPackage() const;
	void LoadStudentObject() const;

private:

	static const FString PackageName;
	static const FString AssetName;

	UPROPERTY()
	TObjectPtr<class USerializationStudent> StudentSrc;

	FStreamableManager StreamableManaget;
	TSharedPtr<FStreamableHandle> Handle;

};
