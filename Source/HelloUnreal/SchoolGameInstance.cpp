// Fill out your copyright notice in the Description page of Project Settings.


#include "SchoolGameInstance.h"
#include "IStudent.h"
#include "ITeacher.h"
#include "IStaff.h"
#include "Card.h"
#include "CourseInfo.h"

USchoolGameInstance::USchoolGameInstance()
{
	SchoolName = TEXT("학교");

}

void USchoolGameInstance::Init()
{
	Super::Init();

	//UE_LOG(LogTemp, Log, TEXT("=============================="));
	//UClass* ClassRunTime = GetClass();
	//UClass* ClassCompile = USchoolGameInstance::StaticClass();
	////check(ClassRunTime == ClassCompile);
	////ensure(ClassRunTime != ClassCompile);
	////ensureMsgf(ClassRunTime != ClassCompile, TEXT("일부러 에러를 발생시킴"));

	//UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s"), *ClassRunTime->GetName());

	//SchoolName = TEXT("동서울대학교");

	//UE_LOG(LogTemp, Log, TEXT("학교 이름 : %s"), *SchoolName);
	//UE_LOG(LogTemp, Log, TEXT("학교 이름 기본 값 : %s"), *GetClass()->GetDefaultObject<USchoolGameInstance>()->SchoolName);

	//UE_LOG(LogTemp, Log, TEXT("=============================="));

	//UStudent* Student = NewObject<UStudent>();
	//UTeacher* Teacher = NewObject<UTeacher>();

	//Student->SetName(TEXT("학생1"));
	//UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 %s"), *Student->GetName());

	//FString CurrentTeacherName;
	//FString NewTeacherName(TEXT("바선생"));
	//FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	//if (NameProp)
	//{
	//	NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
	//	UE_LOG(LogTemp, Log, TEXT("현재 선생 이름 %s"), *CurrentTeacherName);

	//	NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
	//	UE_LOG(LogTemp, Log, TEXT("새로운 선생 이름 %s"), *Teacher->GetName());


	//}
	//UE_LOG(LogTemp, Log, TEXT("=============================="));

	//Student->DoLesson();
	//UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson")); // == Teacher->DoLesson();
	//if (DoLessonFunc)
	//{
	//	Teacher->ProcessEvent(DoLessonFunc, nullptr);
	//}


	/** Design - Interface*/
	/*UE_LOG(LogTemp, Log, TEXT("=============================="));
	TArray<UIPerson*> Persons = { NewObject<UIStudent>(), NewObject<UITeacher>(), NewObject<UIStaff>() };
	for (const auto IPerson : Persons)
	{

		UE_LOG(LogTemp, Log, TEXT("구성원 이름 : %s"), *IPerson->GetName());
	}
	UE_LOG(LogTemp, Log, TEXT("=============================="));

	for (const auto IPerson : Persons)
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(IPerson);
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."), *IPerson->GetName());
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."), *IPerson->GetName());
		}
	}
	UE_LOG(LogTemp, Log, TEXT("=============================="));*/

	/**Composition*/
	/*UE_LOG(LogTemp, Log, TEXT("============================"));
	TArray<UIPerson*> Persons = { NewObject<UIStudent>(), NewObject<UITeacher>(), NewObject<UIStaff>() };
	for (const auto Person : Persons)
	{
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);
		ECardType CardType = OwnCard->GetCardType();
		UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %d"), *Person->GetName(), CardType);

		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/HelloUnreal.ECardType"));
		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();
			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %s"), *Person->GetName(), *CardMetaData);

		}
	}*/
	//UE_LOG(LogTemp, Log, TEXT("============================"));

	/** Delegate*/
	CourseInfo = NewObject<UCourseInfo>(this);
	UE_LOG(LogTemp, Log, TEXT("============================"));

	UIStudent* Student1 = NewObject<UIStudent>();
	Student1->SetName(TEXT("학생1"));
	UIStudent* Student2 = NewObject<UIStudent>();
	Student2->SetName(TEXT("학생2"));
	UIStudent* Student3 = NewObject<UIStudent>();
	Student3->SetName(TEXT("학생3"));

	CourseInfo->OnChanged.AddUObject(Student1, &UIStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UIStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UIStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경되 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("============================"));


}
