// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture15_Module_Plugin_Build/Lecture15_Module_Plugin_Build.h"

#include "ModulePerson.h"

void ULecture15_Module_Plugin_Build::Init()
{
	Super::Init();

	PersonAPI = NewObject<UModulePerson>();
	
	UE_LOG(LogTemp, Log, TEXT("모듈에서 받아온 Person 정보: 이름 %s, ID %d"), *PersonAPI->GetName(), PersonAPI->GetID());

	//아직 블루프린트라던지 사용법을 안 배워서 Plugin 모듈을 불러오는 방법은 잘 모르겠다...
	//대신 Edit-Plugins-Others에 가보면 플러그인이 잡히긴 함
}
