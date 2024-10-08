// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PluginPerson.h"
#include "PluginPersonFactory.generated.h"

/**
 *	
 */
UCLASS()
class MODULEINPLUGIN_API UPluginPersonFactory : public UObject
{
	GENERATED_BODY()
public:
	IPluginPerson* CreatePluginPerson();
};
