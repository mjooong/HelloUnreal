// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializationStudent.h"

USerializationStudent::USerializationStudent()
{
	Order = -1;
	Name = TEXT("홍길동");
}

void USerializationStudent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar << Order;
	Ar << Name;

}
