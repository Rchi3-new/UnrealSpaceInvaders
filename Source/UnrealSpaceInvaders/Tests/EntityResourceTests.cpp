#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Components/EntityResource.h"
#include "UObject/Package.h"
#include "UObject/UnrealType.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEntityResourceTests, "UnrealSpaceInvaders.EntityResource.Basic", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FEntityResourceTests::RunTest(const FString& Parameters)
{
    UEntityResourceComponent* Resource = NewObject<UEntityResourceComponent>(GetTransientPackage());
    TestNotNull(TEXT("Resource component created"), Resource);

    float LastValue = -1.f;
    int32 ValueChangeCount = 0;
    int32 DepletedCount = 0;
    int32 MaxedCount = 0;

    Resource->OnResourceValueChanged.AddLambda([&](float NewValue)
    {
        LastValue = NewValue;
        ++ValueChangeCount;
    });

    Resource->OnResourceDepleted.AddLambda([&]()
    {
        ++DepletedCount;
    });

    Resource->OnResourceMaxedOut.AddLambda([&]()
    {
        ++MaxedCount;
    });

    const FFloatProperty* CurrentValueProp = FindFProperty<FFloatProperty>(Resource->GetClass(), TEXT("CurrentValue"));
    TestNotNull(TEXT("CurrentValue property"), CurrentValueProp);

    Resource->IncreaseValue(50.f);
    float Cur = CurrentValueProp->GetPropertyValue_InContainer(Resource);
    TestEqual(TEXT("IncreaseValue clamps to MaxValue"), Cur, 100.f);
    TestEqual(TEXT("ValueChanged after increase"), LastValue, 100.f);
    TestEqual(TEXT("Value change count"), ValueChangeCount, 1);
    TestEqual(TEXT("MaxedOut event fired"), MaxedCount, 1);
    TestEqual(TEXT("Depleted event not fired"), DepletedCount, 0);

    Resource->DecreaseValue(150.f);
    Cur = CurrentValueProp->GetPropertyValue_InContainer(Resource);
    TestEqual(TEXT("DecreaseValue clamps at zero"), Cur, 0.f);
    TestEqual(TEXT("ValueChanged after decrease"), LastValue, 0.f);
    TestEqual(TEXT("Value change count after decrease"), ValueChangeCount, 2);
    TestEqual(TEXT("Depleted event fired"), DepletedCount, 1);

    Resource->ResetValue();
    Cur = CurrentValueProp->GetPropertyValue_InContainer(Resource);
    TestEqual(TEXT("ResetValue sets to initial"), Cur, 100.f);
    TestEqual(TEXT("ValueChanged after reset"), LastValue, 100.f);
    TestEqual(TEXT("Value change count after reset"), ValueChangeCount, 3);
    TestEqual(TEXT("MaxedOut event fired again"), MaxedCount, 2);

    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS
