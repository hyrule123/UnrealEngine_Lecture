// Fill out your copyright notice in the Description page of Project Settings.


#include "Lecture8_Composition.h"

#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"

void ULecture8_Composition::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("=========================="));

	TArray<UPerson*> Persons = 
	{
		NewObject<UStudent>(),
		NewObject<UTeacher>(),
		NewObject<UStaff>()
	};

	for (const auto* Person : Persons)
	{
		UCard* Card = Person->GetCard();
		check(Card);
		ECardType CardType = Card->GetCardType();
		UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 번호: %d"), *Person->GetPersonName(), CardType);

		//ECardType에 UMETA()로 작성했던 메타데이터 가져오는 방법

		// /Script/ 경로 안의 (프로젝트 이름).(타입 이름)
		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/Lecture.ECardType"));
		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();

			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 이름: %s"), *Person->GetPersonName(), *CardMetaData);
		}
	}



	UE_LOG(LogTemp, Log, TEXT("=========================="));
}
