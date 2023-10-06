// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SchoolGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API USchoolGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	USchoolGameInstance();

	virtual void Init() override;

private:

	UPROPERTY()
	FString SchoolName;

	
};
