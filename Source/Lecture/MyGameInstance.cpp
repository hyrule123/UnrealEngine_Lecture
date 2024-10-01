// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	//상위 클래스의 Init 함수를 반드시 호출한 후 내 코드를 호출해야 함
	Super::Init();

	//TCHAR: 언리얼 엔진에서 사용하는 문자 타입
	TCHAR LogCharArray[] = TEXT("Hello Unreal!");
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);
	//TCHAR ARRAY의 경우 Format 란에 직접 사용이 가능하다.
	UE_LOG(LogTemp, Log, LogCharArray);

	//FString TCHAR을 사용하는 문자열 클래스
	//* 연산자를 붙이면 안의 스트링 데이터의 포인터를 가져온다.
	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	const TCHAR* LogCharPtr = *LogCharString;
	
	//메모리에 직접 접근해서 사용하기
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharDataPtr);

	//저수준 문자열 복사
	TCHAR LogCharArrayWithSize[100];
	FCString::Strcpy(LogCharArrayWithSize, LogCharPtr);
	UE_LOG(LogTemp, Log, LogCharArrayWithSize);


	////////////유용한 함수들/////////////
	
	//문자열 포함여부 및 찾기 - 대소문자 구분 또는 무시 여부를 선택 가능
	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		int32 idx = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
		FString cut = LogCharString.Mid(idx);
		UE_LOG(LogTemp, Log, TEXT("Find Test: %s"), *cut);
	}

	if (false == LogCharString.Contains(TEXT("unreal"), ESearchCase::CaseSensitive))
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("case-sensitive \"unreal\" text NOT found"));
	}


	//문자열 나누기
	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right)) 
	{
		//참고 - 한글의 경우 유니코드 형태로 저장해주어야 언리얼에서 출력이 된다.
		UE_LOG(LogTemp, Log, TEXT("Split Test: %s 와 %s"), *Left, *Right);
	}

	//각종 숫자를 문자열로 변환하기
	int32 IntValue = 32;
	float FloatValue = 3.141592f;

	FString FloatIntString = FString::Printf(TEXT("Int:%d Float: %f"), IntValue, FloatValue);
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Int: %s, Float: %s"), *IntString, *FloatString);

	//문자열을 도로 숫자로 변환하기(로우 레벨)
	int32 ReversedInt = FCString::Atoi(*IntString);
	float ReversedFloat = FCString::Atof(*FloatString);
	UE_LOG(LogTemp, Log, TEXT("Reversed Int: %d, Reversed Float: %f"), ReversedInt, ReversedFloat);


	/////////////// FNAME 클래스 /////////////////
	FName Key1(TEXT("PELVIS"));
	FName Key2(TEXT("pelvis"));
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"),
		Key1 == Key2 ?
		TEXT("FName Key1 == FName Key2") : TEXT("FName Key1 != FName Key2")
	);

	//FName 사용 시 주의할 점
	for (int i = 0; i < 10000; ++i) {
		//FName은 생성자 호출 시, 들어온 문자열이 FName pool에 있는지 여부를 조사한다.
		//루프마다 반복하게 되면 심각한 오버헤드가 발생하므로 아래 작업은 반드시 지양할 것.
		FName SearchInNamePool = FName(TEXT("pelvis"));

		//아래와 같이 static을 활용해 한 번만 조사하도록 해줄 것
		const static FName StaticOnlyOnce = FName(TEXT("pelvis"));
	}
}
