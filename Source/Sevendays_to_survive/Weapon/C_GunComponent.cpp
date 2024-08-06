// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/C_GunComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "Player/Global/C_PlayerEnum.h"

UC_GunComponent::UC_GunComponent()
{
	// Default offset from the character location for projectiles to spawn
	//MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UC_GunComponent::AttachWeapon(AC_GlobalPlayer* _TargetCharacter, ESkeletalItemSlot _GunWeapon)
{
    Character = _TargetCharacter;

    // Check that the character is valid, and has no rifle yet
    if (Character == nullptr /*|| Character->GetHasRifle()*/)
    {
        return;
    }

    switch (_GunWeapon)
    {
    case ESkeletalItemSlot::RRifle:
        Character->SetPlayerCurState(EWeaponUseState::Rifle);
        break;
    case ESkeletalItemSlot::RRifle2:
        Character->SetPlayerCurState(EWeaponUseState::Rifle2);
        break;
    case ESkeletalItemSlot::RPistol:
        Character->SetPlayerCurState(EWeaponUseState::Pistol);
        break;
    case ESkeletalItemSlot::RPistol2:
        Character->SetPlayerCurState(EWeaponUseState::Pistol2);
        break;
    case ESkeletalItemSlot::RShotgun:
        Character->SetPlayerCurState(EWeaponUseState::Shotgun);
        break;
    default:
        break;
    }

    // Attach the weapon to the First Person Character
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

    if (Character->GetSkeletalItemMesh()[static_cast<uint8>(_GunWeapon)]->GetSkinnedAsset() == nullptr)
    {
        Character->GetSkeletalItemMesh()[static_cast<uint8>(_GunWeapon)]->SetSkinnedAsset(GetSkinnedAsset());

        UEnum* Enum = StaticEnum<ESkeletalItemSlot>();
        FString Name = Enum->GetNameStringByValue(static_cast<uint8>(_GunWeapon));
        AttachToComponent(Character->GetSkeletalItemMesh()[static_cast<uint8>(_GunWeapon)], AttachmentRules, *Name);
    }
}

