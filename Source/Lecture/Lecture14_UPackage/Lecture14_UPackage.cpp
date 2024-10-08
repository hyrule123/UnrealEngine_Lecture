// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture14_UPackage/Lecture14_UPackage.h"

#include "Lecture14_UPackage/PackageExample.h"

//패키지 저장을 위해 필요한 헤더
#include "UObject/SavePackage.h"
//Game 폴더의 Student라는 파일 이름이 될 예정
constexpr const TCHAR* PackageName = TEXT("/Game/PackageExample");
constexpr const TCHAR* AssetName = TEXT("Package Asset");


void ULecture14_UPackage::Init()
{
	Super::Init();

	SavePackage();
	LoadPackage();
}

void ULecture14_UPackage::SavePackage() const
{
	//혹시나 이미 패키지가 있을 경우 로드한 후 다시 저장해야 안전하게 저장할 수 있다.
	UPackage* Pkg = ::LoadPackage(nullptr, PackageName, LOAD_None);
	if (Pkg)
	{
		Pkg->FullyLoad();
	}

	Pkg = CreatePackage(PackageName);
	//Public과 Standalone 두 값을 조합해서 사용하는 것이 일반적이다.
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	//NewObject에 인자를 지정하지 않으면 Transient Package에 자동으로 들어가게 됨.
	//인자를 지정할 경우 지정한 패키지로 넣어줄 수 있음.
	//첫 번째 인자는 지난 번 Subobject 때 배웠던 Outer 주소이다. Package 클래스를 주인 클래스로 넣어주는 것과 같음.
	UPackageExample* AssetObj = NewObject<UPackageExample>(Pkg, UPackageExample::StaticClass(), AssetName, ObjectFlag);
	
	AssetObj->Name = TEXT("패키지 테스트");
	AssetObj->ID = 36;

	constexpr int32 NumOfSubs = 10;
	for (int32 i = 1; i <= NumOfSubs; ++i)
	{
		FString SubObjectName = FString::Printf(TEXT("SubObject_%d"), i);

		//AssetObj를 Outer로 하는 서브오브젝트들 다수 생성
		UPackageExample* SubObj = NewObject<UPackageExample>(AssetObj, UPackageExample::StaticClass(), *SubObjectName, ObjectFlag);

		SubObj->Name = FString::Printf(TEXT("서브오브젝트_%d"), i);
		SubObj->ID = i;
	}

	//패키지 이름 + 언리얼에서 지정한 기본 Package 확장자를 더해서 파일명을 생성한다.
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	if (UPackage::SavePackage(Pkg, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("UPackage가 성공적으로 저장되었습니다."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UPackage 저장 실패."));
	}
}

void ULecture14_UPackage::LoadPackage() const
{
	UPackage* Pkg = ::LoadPackage(nullptr, PackageName, LOAD_None);
	check(Pkg);
	Pkg->FullyLoad();

	UPackageExample* Example = FindObject<UPackageExample>(Pkg, AssetName);
	UE_LOG(LogTemp, Log, TEXT("패키지 잘 로드됐나?: 이름: %s, ID: %d"), *Example->Name, Example->ID);
}
