// Fill out your copyright notice in the Description page of Project Settings.

#include "PlateFormTrriger.h"
#include "MovingPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
APlateFormTrriger::APlateFormTrriger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlateFormTrriger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlateFormTrriger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlateFormTrriger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlateFormTrriger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlateFormTrriger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlatformToTrigger.Num() == 0)return;
	for (AMovingPlatform* Actor : PlatformToTrigger)
	{
		Actor->AddActiveTrigger();
	}
}

void APlateFormTrriger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlatformToTrigger.Num() == 0)return;
	for (AMovingPlatform* Actor : PlatformToTrigger)
	{
		Actor->RemoveActiveTrigger();
	}
}