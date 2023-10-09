// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("기존 학사 정보");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContens)
{
	Contents = InNewContens;

	UE_LOG(LogTemp, Log, TEXT("[CourseInfo] 학사 정보가 변경되어 알립을 발송합니다."));
	OnChanged.Broadcast(InSchoolName, Contents);


}