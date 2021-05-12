// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "VPBookmarkContext.generated.h"


USTRUCT(BlueprintType)
struct VPBOOKMARK_API FVPBookmarkCreationContext
{
	GENERATED_BODY()

public:
	/** 创建此书签的客户端的用户名 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FString ConcertCreator;

	/** 书签的分类 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FName CategoryName;

	/** 书签的名字 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FString DisplayName;
};

