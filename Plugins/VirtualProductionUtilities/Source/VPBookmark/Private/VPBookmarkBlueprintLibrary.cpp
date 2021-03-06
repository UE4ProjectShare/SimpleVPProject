// Copyright Epic Games, Inc. All Rights Reserved.

#include "VPBookmarkBlueprintLibrary.h"
#include "VPBookmark.h"
#include "VPBookmarkModule.h"

#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectHash.h"
#include "IVPBookmarkProvider.h"
#include "VPBookmarkModule.h"

PRAGMA_DISABLE_OPTIMIZATION

UVPBookmark* UVPBookmarkBlueprintLibrary::FindVPBookmark(const AActor* Actor)
{
	UVPBookmark* Result = nullptr;
	if (Actor)
	{
		if (UWorld* World = Actor->GetWorld())
		{
			if (AWorldSettings* WorldSettings = World->GetWorldSettings())
			{
				const TArray<UBookmarkBase*>& Bookmarks = WorldSettings->GetBookmarks();
				for (UBookmarkBase* Base : Bookmarks)
				{
					if (UVPBookmark* VPBookmark = Cast<UVPBookmark>(Base))
					{
						if (VPBookmark->OwnedActor.Get() == Actor)
						{
							Result = VPBookmark;
							break;
						}
					}
				}
			}
		}
	}
	return Result;
}


void UVPBookmarkBlueprintLibrary::GetAllVPBookmarkActors(const UObject* WorldContextObject, TArray<AActor*>& OutActors)
{
	OutActors.Reset();

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		AWorldSettings* WorldSettings = World->GetWorldSettings();
		if (WorldSettings != nullptr)
		{
			const TArray<UBookmarkBase*>& Bookmarks = WorldSettings->GetBookmarks();
			OutActors.Reset(Bookmarks.Num());
			for (UBookmarkBase* Base : Bookmarks)
			{
				if (UVPBookmark* Bookmark = Cast<UVPBookmark>(Base))
				{
					if (AActor* Actor = Bookmark->OwnedActor.Get())
					{
						//Checks the PendingKill flag to see if it is dead but memory still valid
						if (!Bookmark->IsPendingKill() && !Actor->IsPendingKill())
						{
							OutActors.Add(Actor);
						}
					}
				}
			}
		}
	}
}


void UVPBookmarkBlueprintLibrary::GetAllVPBookmark(const UObject* WorldContextObject, TArray<UVPBookmark*>& OutBookmarks)
{
	OutBookmarks.Reset();

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		AWorldSettings* WorldSettings = World->GetWorldSettings();
		if (WorldSettings != nullptr)
		{
			const TArray<UBookmarkBase*>& Bookmarks = WorldSettings->GetBookmarks();
			OutBookmarks.Reset(Bookmarks.Num());
			for (UBookmarkBase* Base : Bookmarks)
			{
				if (UVPBookmark* Bookmark = Cast<UVPBookmark>(Base))
				{
					if (!Bookmark->IsPendingKill())
					{
						OutBookmarks.Add(Bookmark);
					}
				}
			}
		}
	}
}

bool UVPBookmarkBlueprintLibrary::CreateVPBookmarkName(AActor* Bookmark, const FString& FormatString, FString& GeneratedNumber, FString& GeneratedLetter)
{
	if (Bookmark == nullptr)
	{
		UE_LOG(LogVPBookmark, Error, TEXT("UVPBookmarkBlueprintLibrary::CreateVPBookmarkName - No actor provided"));
		return false;
	}

	if (!Bookmark->GetClass()->ImplementsInterface(UVPBookmarkProvider::StaticClass()))
	{
		UE_LOG(LogVPBookmark, Warning, TEXT("UVPBookmarkBlueprintLibrary::CreateVPBookmarkName - Actor '%s' doesn't implement IVPBookmarkProvider"), *(Bookmark->GetClass()->GetName()));
		return false;
	}

	// ???????????????????????????"Bookmark 1", "Bookmark 2"??? 
	static const int32 InitialBookmarkIndex = 0;
	static FString NoPlaceholders(FormatString);
	NoPlaceholders = NoPlaceholders.Replace(TEXT("%l"), TEXT(""));
	NoPlaceholders = NoPlaceholders.Replace(TEXT("%n"), TEXT(""));
	NoPlaceholders.RemoveSpacesInline();

	if (!NoPlaceholders.IsEmpty())
	{
		int32 HighestBookmarkIndex = InitialBookmarkIndex;
		int32 NumBookmarks = 0;

		for (TActorIterator<AActor> It(Bookmark->GetWorld()); It; ++It)
		{
			const AActor* CurrentBookmark = *It;
			if (CurrentBookmark != Bookmark && CurrentBookmark->GetClass() == Bookmark->GetClass() && !CurrentBookmark->IsTemplate())
			{
				++NumBookmarks;

				/*int32 CurrentBookmarkIndex = InitialBookmarkIndex;
				if (ExtractBookmarkIndex(CurrentBookmark, CurrentBookmarkIndex) && CurrentBookmarkIndex > HighestBookmarkIndex)
				{
					HighestBookmarkIndex = CurrentBookmarkIndex;
				}*/
			}
		}
		GeneratedNumber = *FString::FromInt(++NumBookmarks);
		GeneratedLetter = *FString::Chr(NumBookmarks + 64);
		FString NewLabel = FormatString.Replace(TEXT("%n"), *GeneratedNumber);
		NewLabel = NewLabel.Replace(TEXT("%l"), *GeneratedLetter);

#if WITH_EDITOR
		Bookmark->SetActorLabel(NewLabel, false); // UED outliner label
#endif //WITH_EDITOR
	
		return true;
	}
	return false;
}


PRAGMA_ENABLE_OPTIMIZATION