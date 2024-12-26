// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundMixModifier.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"

void USoundMixModifier::SetVolume(USoundClass* SoundClass, USoundMix* SoundMix, float NewVolume)
{
    if (SoundMix && SoundClass)
    {
        SoundClass->Properties.Volume = NewVolume;
        SoundClass->MarkPackageDirty();
    }
}