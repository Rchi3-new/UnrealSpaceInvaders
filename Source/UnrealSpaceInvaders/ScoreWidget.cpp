#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (ScoreText)
    {
        ScoreText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
    }
}

void UScoreWidget::UpdateScore(float NewScore)
{
    if (ScoreText)
    {
        const int32 IntScore = FMath::RoundToInt(NewScore);
        ScoreText->SetText(FText::AsNumber(IntScore));
    }
}
