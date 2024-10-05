// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture10_UCL.h"

//Algo == <algorithm> 헤더가 모여있는 폴더
#include "Algo/Accumulate.h"

constexpr int32 ArrayNum = 10;

void ULecture10_UCL::Init()
{
	Super::Init();

	TArray_Example();
	TSet_Example();
}

void ULecture10_UCL::TArray_Example()
{
	
	TArray<int32> Int32Array;

	//추가
	for (int32 i = 1; i <= ArrayNum; ++i)
	{
		Int32Array.Add(i);// == push_back
		//Int32Array.Emplace(i);// == emplace_back
	}

	//std::erase_if
	Int32Array.RemoveAll(
		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	);

	Int32Array += { 2, 4, 6, 8, 10 };

	UE_LOG(LogTemp, Log, TEXT("TArray 순회 결과"));
	FString LogOutput = TEXT("-> ");
	for (const auto& elem : Int32Array)
	{
		LogOutput += FString::FromInt(elem);
		LogOutput += TEXT(", ");
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogOutput);

	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

	//resize, 대신 값 초기화 없이 쓰레기값이 들어감
	Int32ArrayCompare.AddUninitialized(ArrayNum);

	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	//== 연산자 지원
	ensure(Int32Array == Int32ArrayCompare);

	int32 Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}

	ensure(Sum == 55);

	//알고리즘 라이브러리 사용
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);

	ensure(Sum == SumByAlgo);
}

void ULecture10_UCL::TSet_Example()
{
	TSet<int32> Int32Set;

	//추가
	for (int32 i = 1; i <= ArrayNum; ++i)
	{
		Int32Set.Add(i);
		//Int32Array.Emplace(i);
	}

	//제거 및 뒤에 다시 추가 후 어떻게 달라지는지 확인.
	//디버그 모드에서 중단점을 걸고 확인하면 Remove된 원소들이 Invalid로 전환되는 것을 알 수 있다.
	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);
	//이 시점에서 2, 4, 6, 8, 10이 있던 자리는 Invalid가 됨
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	UE_LOG(LogTemp, Log, TEXT("TSet 순회 결과"));
	FString LogOutput = TEXT("-> ");
	for (const auto& elem : Int32Set)
	{
		LogOutput += FString::FromInt(elem);
		LogOutput += TEXT(", ");
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogOutput);
}
