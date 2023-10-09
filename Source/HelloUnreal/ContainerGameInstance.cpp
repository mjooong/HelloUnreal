// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerGameInstance.h"
#include "Algo/Accumulate.h"

FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleCharp[] = TEXT("상해지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleCharp[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandArray.GetData();
}

void UContainerGameInstance::Init()
{
	Super::Init();


	/** 
	TSet
	빈틈없는 메모리 제공
	가장 높은 접근성능
	가장 높은 순회성능
	*/
	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Array.Add(ix);
	}
		
	Int32Array.RemoveAll([](int32 Val)
		{
			return Val % 2 == 0;
		});

	Int32Array += {2, 4, 6, 8, 10};	// {1,3,5,7,9,2,4,6,8,10}

	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum);	// AddUninitialized : 초기화 되지 않는 데이터 더하기
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum); // FMemory::Memcpy 빠르게 복제

	ensure(Int32Array == Int32ArrayCompare);

	int32 Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}
	ensure(Sum == 55);

	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum == SumByAlgo);


	/** 
	TSet 
	빠른 중복 감지
	*/
	TSet<int32> Int32Set;
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Set.Add(ix);
	}

	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);

	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	/**
	Struct
	*/
	const int32 StudentNum = 300;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentData.Emplace(FStudentData(MakeRandomName(), ix));
	}

	TArray<FString> AllStudentsNames;
	Algo::Transform(StudentData, AllStudentsNames, [](const FStudentData& Val)
		{
			return Val.Name;
		});

	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수 : %d"), AllStudentsNames.Num());

	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentData, AllUniqueNames, [](const FStudentData& Val)
		{
			return Val.Name;
		});

	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수 : %d"), AllUniqueNames.Num());

	Algo::Transform(StudentData, StudentMap, [](const FStudentData& Val)
		{
			return TPair<int32, FString>(Val.Order, Val.Name);
		});

	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수 : %d"), StudentMap.Num());

	/**
	TMap
	 중복 불허
	 키 밸류 관리
	*/
	TMap<FString, int32> StudentsMapByUniqueName;

	Algo::Transform(StudentData, StudentsMapByUniqueName, [](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		});

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수 : %d"), StudentsMapByUniqueName.Num());

	/**
	TMultiMap
	 중복 허용
	 키 밸류 관리
	*/
	TMultiMap<FString, int32> StudentsMapByName;

	Algo::Transform(StudentData, StudentsMapByName, [](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		});

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티맵의 레코드 수 : %d"), StudentsMapByName.Num());

	const FString TargetName(TEXT("김상수"));
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수 : %d"), *TargetName, AllOrders.Num());


	TSet<FStudentData> StudentsSet;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), ix));
	}

}
