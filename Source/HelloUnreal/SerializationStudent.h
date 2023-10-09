// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SerializationStudent.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API USerializationStudent : public UObject
{
	GENERATED_BODY()
	
public:
	USerializationStudent();

	int32 GetOrder() const { return Order; }
	void SetOrder(int32 InOrder) { Order = InOrder; }

	const FString& GetName() const { return Name; }
	void SetName(const FString& InName) { Name = InName; }

	virtual void Serialize(FArchive& Ar) override;

private:

	UPROPERTY()
	int32 Order;

	UPROPERTY()
	FString Name;
	
};
