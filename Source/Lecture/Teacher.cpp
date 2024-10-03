// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"


UTeacher::UTeacher()
{
	Super::PersonName = TEXT("이선생");
	Super::Year = 3;
}

void UTeacher::DoLesson()
{
	Super::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%d년차 선생님 %s님이 수업을 강의합니다."), Year, *Super::PersonName);
}
