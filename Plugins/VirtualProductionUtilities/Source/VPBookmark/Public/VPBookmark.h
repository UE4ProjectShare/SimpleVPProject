// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/BookmarkBase.h"
#include "VPBookmarkContext.h"
#include "VPBookmark.generated.h"


class AActor;


USTRUCT(BlueprintType)
struct VPBOOKMARK_API FVPBookmarkViewportData
{
	GENERATED_BODY()

public:
	FVPBookmarkViewportData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FVector JumpToOffsetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FRotator LookRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	float OrthoZoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")
	bool bFlattenRotation;
};


USTRUCT()
struct VPBOOKMARK_API FVPBookmarkJumpToSettings : public FBookmarkBaseJumpToSettings
{
	GENERATED_BODY()
};


UCLASS(BlueprintType, Category = Bookmark)
class VPBOOKMARK_API UVPBookmark : public UBookmarkBase
{
	GENERATED_BODY()

private:
	//DuplicateTransient表示变量值应在任意类型的重复过程中(复制/粘贴， 二进制文件复制等)被重置为类默认值
	//Transient属性是暂时的，这意味着它不会被保存或加载。以这种方式标记的属性在加载时将被填满
	UPROPERTY(DuplicateTransient, Transient)
	bool bIsActive;

public:
	UPROPERTY()
	TLazyObjectPtr<AActor> OwnedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")
	FVPBookmarkCreationContext CreationContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")
	FVPBookmarkViewportData CachedViewportData;

public:
	//判断是否激活
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	bool IsActive() const { return bIsActive; }

	//设置对应OwnedActor的激活状态
	void SetActive(bool bInActive);

	//获得Bookmark的索引
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	int32 GetBookmarkIndex() const;

	//获得对应OwnedActor
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	AActor* GetAssociatedBookmarkActor() const;

	//获得Bookmark的显示信息
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	FText GetDisplayName() const;

public:
 
	//~ Begin UObject Interface

	/**
	* Called after the C++ constructor and after the properties have been initialized, including those loaded from config.
	* This is called before any serialization or other setup has happened.
	*/
	virtual void PostInitProperties() override;

	/** 
	* Do any object-specific cleanup required immediately after loading an object.
	* This is not called for newly-created objects, and by default will always execute on the game thread.
	*/
	virtual void PostLoad() override;

	/**
	* Called before destroying the object.  This is called immediately upon deciding to destroy the object, to allow the object to begin an
	* asynchronous cleanup process.
	*/
	virtual void BeginDestroy() override;
	//~ End UObject Interface

	//~ Begin UBookmarkBase Interface
	virtual void OnCleared() override;
	//~ End UBookmarkBase Interface

private:
	//更换Bookmark
	void BookmarkChanged(AActor* OwnerPtr);
	
	//移除Bookmark
	void RemoveBookmark();

	void OnLevelActorAdded(AActor* NewActor);
	void OnLevelActorDeleted(AActor* DeletedActor);

#if WITH_EDITORONLY_DATA
	FDelegateHandle OnLevelActorAddedHandle;
	FDelegateHandle OnLevelActorDeletedHandle;
#endif
};
