// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture15_Module_Plugin_Build/Lecture15_Module_Plugin_Build.h"

#include "ModulePerson.h"

void ULecture15_Module_Plugin_Build::Init()
{
	Super::Init();

	PersonAPI = NewObject<UModulePerson>();
	
	UE_LOG(LogTemp, Log, TEXT("모듈에서 받아온 Person 정보: 이름 %s, ID %d"), *PersonAPI->GetName(), PersonAPI->GetID());
}
