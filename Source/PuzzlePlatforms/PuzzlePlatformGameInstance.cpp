// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "PlateFormTrriger.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class!=nullptr)) return;
	MenuClass = MainMenuBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	MainMenu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(MainMenu != nullptr)) return;
	MainMenu->SetUp();
	MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformGameInstance::Host()
{
	if (MainMenu!=nullptr)
	{
		MainMenu->TearDown();
	}
	UEngine* Engine = GetEngine();
	if (Engine == nullptr)return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	if (MainMenu != nullptr)
	{
		MainMenu->TearDown();
	}
	UEngine* Engine = GetEngine();
	if (Engine == nullptr)return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
}
