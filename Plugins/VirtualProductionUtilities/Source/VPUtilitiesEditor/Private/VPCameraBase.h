// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraActor.h"
#include "VPCameraBase.generated.h"

class ACameraActor;
class UCameraComponent;


UCLASS()
class AVPCameraBase : public ACineCameraActor
{
	GENERATED_BODY()

public:
	AVPCameraBase(const FObjectInitializer& ObjectInitializer);

public:
	/** Remove the preview and clear the list of selected user. Another user may have the camera selected and will re-add it later. */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Editor Scripting | Camera")
	void ResetPreview();

public:
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginDestroy() override;

	/**
	* Presave function. Gets called once before an object gets serialized for saving. This function is necessary
	* for save time computation as Serialize gets called three times per object from within SavePackage.
	*
	* @warning: Objects created from within PreSave will NOT have PreSave called on them!!!
	*/
	virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;

private:
	void AddPreview();
	void RemovePreview();
	void AddUser();
	void RemoveUser(bool bForceRemovePreview);

	/** Contains the name of users in an MU session that have selected this */
	UPROPERTY()
	TArray<FGuid> SelectedByUsers;

	FGuid CurrentInstanceId;
};