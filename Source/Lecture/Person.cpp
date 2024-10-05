// Fill out your copyright notice in the Description page of Project Settings.
#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	PersonName = TEXT("홍길동");
	Year = 1;

	//UObject가 들고있는 UObject의 경우에는 CreateDefaultSubobject라는 함수를 호출하여 생성한다.
	//인자로 FNAME이 필요한데, 해당 인자가 FNAME으로 변환되는것을 알려주기 위해서 문자열 앞에 'NAME_'이라는 접두사를 붙여준다.
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));

	
}

//void UPerson::DoLesson()
//{
//	UE_LOG(LogTemp, Log, TEXT("%s님이 수업에 참여했습니다."), *PersonName);
//}

const FString& UPerson::GetPersonName() const
{
	return PersonName;
}

void UPerson::SetPersonName(const FString& InName)
{
	PersonName = InName;
}
