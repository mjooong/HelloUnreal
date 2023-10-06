// Fill out your copyright notice in the Description page of Project Settings.


#include "IStaff.h"
#include "Card.h"

UIStaff::UIStaff()
{
	Name = TEXT("김직원");
	Card->SetCardType(ECardType::Staff);
}
