// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializationTest.h"

void USerializationTest::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar << Name;
}
