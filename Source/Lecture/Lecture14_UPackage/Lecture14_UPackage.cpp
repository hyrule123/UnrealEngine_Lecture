// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture14_UPackage/Lecture14_UPackage.h"

#include "Lecture14_UPackage/PackageExample.h"

//패키지 저장을 위해 필요한 헤더
#include "UObject/SavePackage.h"
//Game 폴더의 Student라는 파일 이름이 될 예정
constexpr const TCHAR* PackageName = TEXT("/Game/PackageExample");
constexpr const TCHAR* AssetName = TEXT("Package Asset");


ULecture14_UPackage::ULecture14_UPackage()
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), PackageName, AssetName);

	//생성자에서 오브젝트를 로드할 경우, 게임 시작 시점에 모두 로드가 되어있어야 함을 의미한다.
	static ConstructorHelpers::FObjectFinder<UPackageExample> PreLoad(*TopSoftObjectPath);

	//만약 성공헀다면 아래 로그가 "두 번" 찍히게 된다.
	//첫 로딩 시 한번, 에디터에서 한 번
	//생성자에서 불러오는 것이기 때문에, 에셋이 있다는 것이 보장되어야 한다. 아니면 로딩 중에 막힘.
	if (PreLoad.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("FObjectFinder를 통한 생성자에서 로드 확인: 이름: %s, ID: %d"), *PreLoad.Object->Name, PreLoad.Object->ID);
	}
}

void ULecture14_UPackage::Init()
{
	Super::Init();

	//SavePackage();
	//LoadPackage();
	//LoadExampleObject();
	LoadExampleObjectAsync();
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

void ULecture14_UPackage::LoadExampleObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), PackageName, AssetName);
	
	UPackageExample* Example = LoadObject<UPackageExample>(nullptr, *TopSoftObjectPath);
	UE_LOG(LogTemp, Log, TEXT("LoadObject를 통한 로드 확인: 이름: %s, ID: %d"), *Example->Name, Example->ID);
}

void ULecture14_UPackage::LoadExampleObjectAsync()
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), PackageName, AssetName);

	//인자 1: 패키지 이름
	//인자 2: 로드 완료되면 호출할 콜백함수
	Handle = StreamableManager.RequestAsyncLoad(TopSoftObjectPath,
		[&]()
		{
			//Handle이 유효 + 로드 완료 되었을 시
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				//로드된 오브젝트를 캐스팅해서 가져온다.
				UPackageExample* TopObject = Cast<UPackageExample>(Handle->GetLoadedAsset());
				if (TopObject)
				{
					UE_LOG(LogTemp, Log, TEXT("FStreamableManager를 통한 로드 확인: 이름: %s, ID: %d"), *TopObject->Name, TopObject->ID);

					Handle->ReleaseHandle();
					Handle.Reset();
				}
			}
		}
		);
}
