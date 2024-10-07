// Fill out your copyright notice in the Description page of Project Settings.


#include "Lecture11_UStruct_and_TMap.h"

FName MakeRandomName()
{
	constexpr TCHAR FirstName[] = TEXT("김이박최");
	constexpr TCHAR MiddleName[] = TEXT("상혜지성");
	constexpr TCHAR LastName[] = TEXT("수은원연");

	TArray<TCHAR> ret;
	ret.SetNum(3);
	
	ret[0] = FirstName[FMath::RandRange(0, 3)];
	ret[1] = MiddleName[FMath::RandRange(0, 3)];
	ret[2] = LastName[FMath::RandRange(0, 3)];

	return ret.GetData();
}

constexpr int32 StudentsCount = 300;

void ULecture11_UStruct_and_TMap::Init()
{
	Super::Init();

	CreateRandomStudentsData();
	Algo_Transform_Example();
	TSet_TMap_Example();
	TMultiMap_MultiFind_Example();
	Custom_Struct_Key_Example();
}

void ULecture11_UStruct_and_TMap::CreateRandomStudentsData()
{
	//300명의 랜덤한 학생 이름을 저장한다.
	StudentsData.Reserve(StudentsCount);
	for (int32 i = 1; i <= StudentsCount; ++i)
	{
		FStudentData Data;
		Data.Name = MakeRandomName();
		Data.ID = i;

		StudentsData.Add(Data);
	}
}

void ULecture11_UStruct_and_TMap::Algo_Transform_Example()
{
	//Algo::Transform 함수 예시(원하는 데이터만 뽑아와서 집어넣을 수 있다)
	TArray<FName> AllStudentsName;
	Algo::Transform(StudentsData, AllStudentsName,
		[](const FStudentData& InData)->FName
		{
			return InData.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("* 모든 학생 수: %d"), AllStudentsName.Num());
}

void ULecture11_UStruct_and_TMap::TSet_TMap_Example()
{
	TSet<FName> UniqueStudentsName;
	Algo::Transform(StudentsData, UniqueStudentsName,
		[](const FStudentData& InData)->FName
		{
			return InData.Name;
		}
	);
	UE_LOG(LogTemp, Log, TEXT("* 중복 없는 학생 이름 수: %d"), UniqueStudentsName.Num());


	//TMap by ID
	TMap<int32, FName> StudentsMapByID;
	Algo::Transform(StudentsData, StudentsMapByID,
		//TPair를 반환해주면 된다.
		[](const FStudentData& InData)->TPair<int32, FName>
		{
			return TPair<int32, FName>(InData.ID, InData.Name);
		}
	);
	UE_LOG(LogTemp, Log, TEXT("* ID에 따른 학생 맵의 레코드 수: %d"), StudentsMapByID.Num());

	//TMap by Name
	TMap<FName, int32> StudentsMapByName;
	Algo::Transform(StudentsData, StudentsMapByName,
		//TPair를 반환해주면 된다.
		[](const FStudentData& InData)->TPair<FName, int32>
		{
			return TPair<FName, int32>(InData.Name, InData.ID);
		}
	);
	UE_LOG(LogTemp, Log, TEXT("* 이름에 따른 학생 맵의 레코드 수: %d"), StudentsMapByName.Num());

	UE_LOG(LogTemp, Log, TEXT("===== 중복 제외 학생 이름 리스트 ====="));
	for (const auto& Student : StudentsMapByName)
	{
		UE_LOG(LogTemp, Log, TEXT("이름: %s, ID: %d"), *Student.Key.ToString(), Student.Value);
	}
	UE_LOG(LogTemp, Log, TEXT("=============================="));
}

void ULecture11_UStruct_and_TMap::TMultiMap_MultiFind_Example()
{
	//TMultiMap by Name
	TMultiMap<FName, int32> StudentsMultiMapByName;
	Algo::Transform(StudentsData, StudentsMultiMapByName,
		//TPair를 반환해주면 된다.
		[](const FStudentData& InData)->TPair<FName, int32>
		{
			return TPair<FName, int32>(InData.Name, InData.ID);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("* 이름에 따른 학생 멀티맵의 레코드 수: %d"), StudentsMultiMapByName.Num());

	//특정 이름이 있는지 찾아보기
	FName FindKey = TEXT("이혜은"); //이름 조합 중 하나
	TArray<int32> Results;
	StudentsMultiMapByName.MultiFind(FindKey, Results);
	UE_LOG(LogTemp, Log, TEXT("===== 이름이 \"이혜은\" 인 학생들의 ID 목록 ====="));
	for (int32 ID : Results)
	{
		UE_LOG(LogTemp, Log, TEXT("%d"), ID);
	}
}

void ULecture11_UStruct_and_TMap::Custom_Struct_Key_Example()
{
	TSet<FStudentData> StudentDataSet;
	Algo::Transform(StudentsData, StudentDataSet,
		[](const FStudentData& InData)->const FStudentData&
		{
			return InData;
		}
		);

	UE_LOG(LogTemp, Log, TEXT("===== 커스텀 구조체를 키값으로 사용한 결과 ====="));
	UE_LOG(LogTemp, Log, TEXT("Elements Numbers: %d"), StudentDataSet.Num());
	UE_LOG(LogTemp, Log, TEXT("===== 커스텀 구조체 Set 중복 제외 학생 이름 리스트 ====="));
	for (const auto& Student : StudentDataSet)
	{
		UE_LOG(LogTemp, Log, TEXT("이름: %s, ID: %d"), *Student.Name.ToString(), Student.ID);
	}
	UE_LOG(LogTemp, Log, TEXT("=============================="));
}
