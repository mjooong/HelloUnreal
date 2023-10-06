// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPerson.h"
#include "LessonInterface.h"
#include "IStudent.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UIStudent : public UIPerson, public ILessonInterface
{
	GENERATED_BODY()
	
public:
	UIStudent();

	virtual void DoLesson() override;

};
