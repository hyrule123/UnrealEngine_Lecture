// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture13_Serialization.h"

#include "../StudentData.h"
#include "SerializationTest_Derived.h"

//Json으로 직렬화하기 위해 필요한 헤더.
//기본값으로는 라이브러리가 링크되어 있지 않기 때문에, 
//(프로젝트명).Build.cs 라는 파일에서 라이브러리를 링크시켜주어야 한다.
#include "JsonObjectConverter.h"

ULecture13_Serialization::ULecture13_Serialization()
{
	SerSrc = CreateDefaultSubobject<USerializationTest_Derived>(TEXT("FNAME_SerializaerSrc"));
}

void ULecture13_Serialization::Init()
{
	Super::Init();

	SerSrc->Name = TEXT("Serialize Test");
	SerSrc->ID = 1234;

	//ProjectDir()은 상대 경로를 통해 드라이브 루트까지 이동한 후 다시 들어오는 방식이라
	//문자열이 좀 복잡하다.

	//FPath::Combine()을 사용하면 경로를 붙일 수 있다.
	FString SavedDir = 
		FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));

	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더 상대 경로 : %s"), *SavedDir);

	//아래 함수를 통해 경로를 드라이브 루트로부터 시작되는 절대 경로로 바꿔줄 수 있다.
	FPaths::MakeStandardFilename(SavedDir);
	UE_LOG(LogTemp, Log, TEXT(" 파일 전체 절대 경로 : %s"), *SavedDir);


	//구조체를 저장할 파일명 만들기
	const FString RawDataFileName = TEXT("RawData.bin");
	FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 상대 경로 : %s"), *RawDataAbsolutePath);
	Serialize_Struct(RawDataAbsolutePath);
	Deserialize_Struct(RawDataAbsolutePath);


	//UStudent를 저장할 파일명 만들기
	constexpr const TCHAR* ObjectDataFileName = TEXT("ObjectData.bin");
	FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, ObjectDataFileName);
	Serialize_UObject(ObjectDataAbsolutePath);
	Deserialize_UObject(ObjectDataAbsolutePath);

	constexpr const TCHAR* JsonDataFileName(TEXT("SerializeJsonData.txt"));
	FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, JsonDataFileName);
	Serialize_Json(JsonDataAbsolutePath);
	DeSerialize_Json(JsonDataAbsolutePath);
}

void ULecture13_Serialization::Serialize_Struct(const FString& FilePath)
{
	FStudentData RawDataSrc = { TEXT("이게 출력되면 성공한거임"), 123 };

	//정확히 생성되는 클래스는 FArchiveFileReaderGeneric 임
	TUniquePtr<FArchive> RawFileWriterAr(IFileManager::Get().CreateFileWriter(*FilePath));
	if (nullptr != RawFileWriterAr)
	{
		//저장방법 1: 직접 변수를 serializer에 집어 넣기
		FString SaveStr = RawDataSrc.Name.ToString();
		*RawFileWriterAr << SaveStr;

		*RawFileWriterAr << RawDataSrc.ID;


		//저장방법 2: struct 본체에서 << 연산자를 오버라이드 하기
		*RawFileWriterAr << RawDataSrc;
	}
	//FArchiveFileReaderGeneric 클래스는 Close()를 소멸자에서 호출함.
	RawFileWriterAr = nullptr;
}

void ULecture13_Serialization::Deserialize_Struct(const FString& FilePath)
{
	//if문 안에서 바로 생성해서 사용하면 블록 벗어났을 때 바로 할당이 해제됨
	if (TUniquePtr<FArchive> RawFileReaderAr =
		TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*FilePath)))
	{
		FStudentData Data1;
		FString Name;
		*RawFileReaderAr << Name;
		Data1.Name = *Name;
		*RawFileReaderAr << Data1.ID;
		UE_LOG(LogTemp, Log, TEXT("Data1 잘 저장됐나? 이름: %s, ID: %d"), *Data1.Name.ToString(), Data1.ID);

		FStudentData Data2;
		*RawFileReaderAr << Data2;
		UE_LOG(LogTemp, Log, TEXT("Data2 잘 저장됐나? 이름: %s, ID: %d"), *Data2.Name.ToString(), Data2.ID);
	}
}

void ULecture13_Serialization::Serialize_UObject(const FString& FilePath)
{	
	//메모리에 저장해보자
	TArray<uint8> BufferArray;

	//생성자에 자체 버퍼를 인자로 전달하면 된다
	FMemoryWriter MemoryWriterAr(BufferArray);

	//마찬가지로 Serialize할때도 MemoryWriter를 전달하면 된다.(FArchive의 자식 클래스임)
	SerSrc->Serialize(MemoryWriterAr);

	//이걸 다시 파일로 저장해보자
	if (TUniquePtr<FArchive> FileWriterAr = 
		TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*FilePath)))
	{
		//버퍼 배열을 바로 << 연산자로 밀어넣어주면 된다.
		*FileWriterAr << BufferArray;
	}
}

void ULecture13_Serialization::Deserialize_UObject(const FString& FilePath)
{
	//메모리 버퍼와 Reader 만들어주고
	TArray<uint8> BufferArrayFromFile;
	FMemoryReader MemoryReaderAr(BufferArrayFromFile);

	if (TUniquePtr<FArchive> FileReaderAr =
		TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*FilePath)))
	{
		//메모리로 파일에서 읽어온 내용을 작성한 후
		*FileReaderAr << BufferArrayFromFile;

		//해당 메모리 버퍼를 시리얼라이저에 넘겨준다.
		USerializationTest_Derived* SerDest = NewObject<USerializationTest_Derived>();
		SerDest->Serialize(MemoryReaderAr);

		UE_LOG(LogTemp, Log, TEXT("USerializerTest_Derived Deserialize 결과: 이름 %s ID %d"), *SerDest->Name, SerDest->ID);
	}
}

void ULecture13_Serialization::Serialize_Json(const FString& FilePath)
{
	//TSharedRef로 생성한다.
	TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();

	//1. UObject -> JsonObject 형태로 변환
	//UClass 정보와, 포인터 주소, JsonObject 주소를 넘겨주면 자동으로 변환해준다.
	FJsonObjectConverter::UStructToJsonObject(SerSrc->GetClass(), SerSrc, JsonObjectSrc);

	//Json 문자열을 담을 FString 버퍼
	FString JsonOutString;

	//TCHAR 인코딩으로 저장하는 JsonWriter에 만든 버퍼를 연동시킨다.
	TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
	if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
	{
		FFileHelper::SaveStringToFile(JsonOutString, *FilePath);
	}
}

void ULecture13_Serialization::DeSerialize_Json(const FString& FilePath)
{
	//문자열 버퍼 만들고 거기에다 파일에서 불러온 값을 집어넣는다.
	FString JsonInString;
	FFileHelper::LoadFileToString(JsonInString, *FilePath);

	//버퍼를 Json reader 클래스와 연동한다.
	TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

	//불러온 데이터를 Deserialze하여 JsonObject로 만든다.
	TSharedPtr<FJsonObject> JsonObjectDest;
	if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
	{
		USerializationTest_Derived* JsonSerDest = NewObject<USerializationTest_Derived>();

		//Json Object -> UStruct(UObject)
		if (FJsonObjectConverter::JsonObjectToUStruct(
			JsonObjectDest.ToSharedRef(),
			JsonSerDest->GetClass(),
			JsonSerDest))
		{
			UE_LOG(LogTemp, Log,
				TEXT("Json Deserialize Result: 이름 %s, ID %d"),
				*JsonSerDest->Name, JsonSerDest->ID);
		}
	}
}
