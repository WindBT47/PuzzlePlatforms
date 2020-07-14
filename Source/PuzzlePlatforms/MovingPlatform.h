// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(const float DeltaTime) override;

	void AddActiveTrigger();

	void RemoveActiveTrigger();

private:

	UPROPERTY(EditAnywhere, category = "Moving")
	float Speed = 20;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true), category = "Moving")
	FVector TargetLocation;

	FVector GlobalTargetLocation;

	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggers = 1;
};
