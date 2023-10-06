// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPerson.h"
#include "LessonInterface.h"
#include "ITeacher.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UITeacher : public UIPerson, public ILessonInterface
{
	GENERATED_BODY()
	
public:
	UITeacher();

	virtual void DoLesson() override;
};
