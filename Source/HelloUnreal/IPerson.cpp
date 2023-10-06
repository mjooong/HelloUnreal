// Fill out your copyright notice in the Description page of Project Settings.


#include "IPerson.h"
#include "Card.h"

UIPerson::UIPerson()
{
	Name = TEXT("홍길동");
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));
}
