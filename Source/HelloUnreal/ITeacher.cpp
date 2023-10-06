// Fill out your copyright notice in the Description page of Project Settings.


#include "ITeacher.h"
#include "Card.h"

UITeacher::UITeacher()
{
	Name = TEXT("김선생");
	Card->SetCardType(ECardType::Teacher);
}

void UITeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s님은 가르칩니다."), *Name);
}
