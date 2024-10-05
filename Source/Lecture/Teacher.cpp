// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"
#include "Card.h"

UTeacher::UTeacher()
{
	//다중상속을 한 경우 Super을 사용할 수 없다.
	UPerson::PersonName = TEXT("이선생");
	UPerson::Year = 3;

	//부모 생성자에서 CreateDefaultSubobject를 호출했으므로,
	//여기선 내부 데이터만 변경해 주면 된다.
	Card->SetCardType(ECardType::Teacher);
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%d년차 선생님 %s님이 수업을 강의합니다."), Year, *UPerson::PersonName);
}
