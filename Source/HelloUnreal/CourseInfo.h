// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);


/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();

	FCourseInfoOnChangedSignature OnChanged;

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContens);

private:
	FString Contents;
	
};
