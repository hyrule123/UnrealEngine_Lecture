// Fill out your copyright notice in the Description page of Project Settings.


#include "Staff.h"
#include "Card.h"

UStaff::UStaff()
{
	PersonName = TEXT("이직원");
	Card->SetCardType(ECardType::Staff);
}

