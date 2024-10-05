// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	UPerson::PersonName = TEXT("이학생");
	UPerson::Year = 1;
	StudentID = 1;

	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	//다중상속의 경우 Super를 사용할 수 없으므로 정확히 지정
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%d학년 %d번 %s님이 수업을 듣습니다."), Year, StudentID, *Super::PersonName);
}
