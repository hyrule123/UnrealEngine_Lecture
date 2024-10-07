// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializationTest_Derived.h"

void USerializationTest_Derived::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar << ID;
}
