// Fill out your copyright notice in the Description page of Project Settings.


#include "IStudent.h"
#include "Card.h"

UIStudent::UIStudent()
{
	Name = TEXT("김학생");
	Card->SetCardType(ECardType::Student);
}

void UIStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s님은 공부합니다."), *Name);
}
