// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializationGameInstance.h"
#include "SerializationStudent.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

const FString USerializationGameInstance::PackageName = TEXT("/Game/Student");
const FString USerializationGameInstance::AssetName = TEXT("TopStudent");

void printStudentInfo(const USerializationStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] 이름 %s 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

USerializationGameInstance::USerializationGameInstance()
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	static ConstructorHelpers::FObjectFinder<USerializationStudent> UASSET_TopStudent(*TopSoftObjectPath);
	if (UASSET_TopStudent.Succeeded())
	{
		printStudentInfo(UASSET_TopStudent.Object, TEXT("Constructor"));
	}

}

void USerializationGameInstance::Init()
{
	Super::Init();

	FStudentData RawDataSrc(16, TEXT("유재석"));

	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더 : %s"), *SavedDir);

	{
		const FString RawDataFileName(TEXT("RawData.bin"));
		FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로 : %s"), *RawDataAbsolutePath);
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("변경할 파일 전체 경로 : %s"), *RawDataAbsolutePath);

		FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
		if (nullptr != RawFileWriterAr)
		{
			*RawFileWriterAr << RawDataSrc;
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
		if (nullptr != RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %s 순번 %d"), *RawDataDest.Name, RawDataDest.Order);
		}
	}

	StudentSrc = NewObject<USerializationStudent>();
	StudentSrc->SetName(TEXT("하하"));
	StudentSrc->SetOrder(59);

	{
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSrc->Serialize(MemoryWriterAr);

		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
		{
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}

		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
		{
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();
		}

		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		USerializationStudent* StudentDest = NewObject<USerializationStudent>();
		StudentDest->Serialize(MemoryReaderAr);
		printStudentInfo(StudentDest, TEXT("ObjectData"));
	}

	{
		FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
		FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc);

		FString JsonOutString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
		if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath);
		}

		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);

		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			USerializationStudent* JsonStudentDest = NewObject<USerializationStudent>();
			if(FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				printStudentInfo(JsonStudentDest, TEXT("JsonData"));
			}
		}

	}

	SaveStudentPackage();
	//LoadStudentPackage();
	//LoadStudentObject();

	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	Handle = StreamableManaget.RequestAsyncLoad(TopSoftObjectPath,
		[&]()
		{
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				USerializationStudent* TopStudent = Cast<USerializationStudent>(Handle->GetLoadedAsset());
				if (TopStudent)
				{
					printStudentInfo(TopStudent, TEXT("AsyncLoad"));
					Handle->ReleaseHandle();
					Handle.Reset();
				}
			}
		});

}

void USerializationGameInstance::SaveStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}

	StudentPackage = CreatePackage(*PackageName);
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	USerializationStudent* TopStudent = NewObject<USerializationStudent>(StudentPackage, USerializationStudent::StaticClass(), *AssetName, ObjectFlag);
	TopStudent->SetName(TEXT("이이경"));
	TopStudent->SetOrder(36);

	const int32 NumofSubs = 10;
	for (int32 ix = 1; ix <= NumofSubs; ++ix)
	{
		FString SubObjectName = FString::Printf(TEXT("Student%d"), ix);
		USerializationStudent* SubStudent = NewObject< USerializationStudent>(TopStudent, USerializationStudent::StaticClass(), *SubObjectName, ObjectFlag);
		SubStudent->SetName(FString::Printf(TEXT("학생%d"), ix));
		SubStudent->SetOrder(ix);
	}

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지가 성공적으로 저장되었습니다"));
	}

}

void USerializationGameInstance::LoadStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (nullptr == StudentPackage)
	{
		UE_LOG(LogTemp, Warning, TEXT("패키지를 찾을 수 없습니다"));
		return;
	}

	StudentPackage->FullyLoad();

	USerializationStudent* TopStudent = FindObject<USerializationStudent>(StudentPackage, *AssetName);
	printStudentInfo(TopStudent, TEXT("FindObject Asset	"));
}

void USerializationGameInstance::LoadStudentObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	USerializationStudent* TopStudent = LoadObject<USerializationStudent>(nullptr, *TopSoftObjectPath);
	printStudentInfo(TopStudent, TEXT("LoadObject Asset"));
}
