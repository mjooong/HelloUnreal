// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MemoryGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UMemoryGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	virtual void Shutdown() override;

private:

	TObjectPtr<class UStudent> NonPropStudent;

	UPROPERTY()
	TObjectPtr<class UStudent> PropStudent;

	TArray<TObjectPtr<class UStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> PropStudents;

	class FStudentManager* StudentManager = nullptr;

};
