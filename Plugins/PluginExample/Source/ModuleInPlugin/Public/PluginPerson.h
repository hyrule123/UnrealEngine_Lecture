// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PluginPerson.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPluginPerson : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MODULEINPLUGIN_API IPluginPerson
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual const FString& GetPersonName() const = 0;
	virtual int32 GetPersonID() const = 0;
};
