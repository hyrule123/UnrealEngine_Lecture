// Fill out your copyright notice in the Description page of Project Settings.
#include "ModulePerson.h"

#include "PersonImpl.h"

UModulePerson::UModulePerson()
{
	PersonPrivate = CreateDefaultSubobject<UPersonImpl>(TEXT("FNAME_PersonImpl"));
	PersonPrivate->SetName(TEXT("Private Person"));
	PersonPrivate->SetID(1111);
}

const FString& UModulePerson::GetName() const
{
	return PersonPrivate->GetName();
}

int32 UModulePerson::GetID() const
{
	return PersonPrivate->GetID();
}
