// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VPBookmarkBlueprintLibrary.generated.h"


class AActor;
class UVPBookmark;


UCLASS(meta=(ScriptName="VPBookmarkLibrary"))
class VPBOOKMARK_API UVPBookmarkBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//与World中的所有Bookmark进行比对查找
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	static UVPBookmark* FindVPBookmark(const AActor* Actor);

	//获得World中所有的Bookmark对应的Actor（意思是：Bookmark与之关联的有各种标记）
	UFUNCTION(BlueprintCallable, Category = "Bookmarks", meta = (WorldContext = "WorldContextObject"))
	static void GetAllVPBookmarkActors(const UObject* WorldContextObject, TArray<AActor*>& OutActors);

	//获得World中所有的Bookmark
	UFUNCTION(BlueprintCallable, Category = "Bookmarks", meta = (WorldContext = "WorldContextObject"))
	static void GetAllVPBookmark(const UObject* WorldContextObject, TArray<UVPBookmark*>& OutBookmarks);

	//创建新的书签
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	static bool CreateVPBookmarkName(AActor* Bookmark, const FString& FormatString, FString& GeneratedNumber, FString& GeneratedLetter);
};
