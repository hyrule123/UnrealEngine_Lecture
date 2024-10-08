// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PluginPerson.h"
#include "PluginPerson_Impl.generated.h"

/**
 * 
 */
UCLASS()
class UPluginPerson_Impl : public UObject, public IPluginPerson
{
	GENERATED_BODY()
public:
	UPluginPerson_Impl();

	virtual const FString& GetPersonName() const final { return PersonName; }
	virtual int32 GetPersonID() const final { return PersonID; }

private:
	FString PersonName;
	int32 PersonID;
};
