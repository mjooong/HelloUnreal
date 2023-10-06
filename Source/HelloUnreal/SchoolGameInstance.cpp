// Fill out your copyright notice in the Description page of Project Settings.


#include "SchoolGameInstance.h"
#include "Student.h"
#include "Teacher.h"

USchoolGameInstance::USchoolGameInstance()
{
	SchoolName = TEXT("기본학교");

}

void USchoolGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("=============================="));
	UClass* ClassRunTime = GetClass();
	UClass* ClassCompile = USchoolGameInstance::StaticClass();
	//check(ClassRunTime == ClassCompile);
	//ensure(ClassRunTime != ClassCompile);
	//ensureMsgf(ClassRunTime != ClassCompile, TEXT("일부러 에러를 발생시킴"));

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s"), *ClassRunTime->GetName());

	SchoolName = TEXT("동서울대학교");

	UE_LOG(LogTemp, Log, TEXT("학교 이름 : %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본 값 : %s"), *GetClass()->GetDefaultObject<USchoolGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("=============================="));

	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 %s"), *Student->GetName());

	FString CurrentTeacherName;
	FString NewTeacherName(TEXT("바선생"));
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생 이름 %s"), *CurrentTeacherName);

		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생 이름 %s"), *Teacher->GetName());


	}
	UE_LOG(LogTemp, Log, TEXT("=============================="));

	Student->DoLesson();
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson")); // == Teacher->DoLesson();
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}
}
