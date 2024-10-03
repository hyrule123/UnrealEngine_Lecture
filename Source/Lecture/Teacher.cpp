// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"


UTeacher::UTeacher()
{
	//다중상속을 한 경우 Super을 사용할 수 없다.
	UPerson::PersonName = TEXT("이선생");
	UPerson::Year = 3;
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%d년차 선생님 %s님이 수업을 강의합니다."), Year, *UPerson::PersonName);
}
