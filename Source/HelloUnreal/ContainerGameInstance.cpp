// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerGameInstance.h"
#include "Algo/Accumulate.h"

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


}
