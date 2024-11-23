#include "FlipBookImage.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "Module2D/Utils/Utils2D.h"
#include "Engine/Engine.h"
#include "Tickable.h"

UFlipBookImage::UFlipBookImage()
{
    if (FTSTicker* Tiker = &FTSTicker::GetCoreTicker())
    {
        FTickerDelegate TikerDelegate;
        TikerDelegate.BindUObject(this, &UFlipBookImage::SetImageByTime);

        TickHandle = FTSTicker::GetCoreTicker().AddTicker(TikerDelegate);
    }
}

UFlipBookImage::~UFlipBookImage()
{
    if (TickHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
    }
}

bool UFlipBookImage::SetImageByTime(float Time)
{
    if (Sprite)
    {
        Timer += Time;
        SetBrush(UUtils2D::MakeBrushFromSprite(Sprite->GetSpriteAtTime(Timer, true), Size.X, Size.Y));

        if (IsLooping && Timer > Sprite->GetTotalDuration())
        {
            Timer = 0.0f;
        }
    }

    return true;
}