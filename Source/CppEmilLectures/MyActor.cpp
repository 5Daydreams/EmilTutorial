// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	AggroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AggroSphere"));
	AggroSphere->SetupAttachment(Root);

	AggroSphere->SetSphereRadius(500.0f);
	AggroSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::HandleAggroBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(AggroSphere);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Hell ye, prints and shit"));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ChaseTarget != nullptr)
	{
		FVector Direction = ChaseTarget->GetActorLocation() - this->GetActorLocation();
		Direction.Normalize();

		FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Direction);
		this->SetActorRotation(Rotation);

		AddActorWorldOffset(Direction * Speed * DeltaTime);
	}


}

void AMyActor::HandleAggroBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APawn>())
	{
		ChaseTarget = Cast<APawn>(OtherActor);
	}
}

void AMyActor::SuperCrazyFunction()
{
	AddActorLocalOffset(FVector::UpVector * 500.0f);
}