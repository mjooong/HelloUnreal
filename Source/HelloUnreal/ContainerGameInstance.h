// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ContainerGameInstance.generated.h"

USTRUCT()
struct FStudentData 
{
	GENERATED_BODY()
	
	FStudentData()
	{
		Name = TEXT("홍길동");
		Order = -1;
	}

	FStudentData(FString InName, int32 InOrder) : Name(InName), Order(InOrder) {}

	bool operator==(const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UContainerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:

	virtual void Init() override;

private:
	TArray<FStudentData> StudentData;

	UPROPERTY()
	TArray<TObjectPtr<class UStruct>> Students;

	TMap<int32, FString> StudentMap;


};
