# include "HTag.hh"
// # include "HTagPrivate.hh"

hanalysis::HTag::HTag()
// : TagPrivate(new HTagPrivate(this))
{
//     Print(HInformation, "Constructor");
//     TagPrivate->InitialValue = -10;
//     TagPrivate->Bdt = TagPrivate->InitialValue;
//     TagPrivate->Tag = TagPrivate->InitialValue;

    InitialValue = -10;
    BdtM = InitialValue;
    TagM = 0;
    FlagM = 0;

}
//
//
// hanalysis::HTag::HTag(hanalysis::HTagPrivate &Newd) : TagPrivate(&Newd)
// {
//     //     Print(HInformation, "Constructor");
//     TagPrivate->InitialValue = -10;
//     TagPrivate->Bdt = TagPrivate->InitialValue;
//     TagPrivate->Tag = TagPrivate->InitialValue;
//
// }

// hanalysis::HTag::HTag(const HTag &NewTag) : TagPrivate(new HTagPrivate(*NewTag.TagPrivate)) {}

// hanalysis::HTag::HTag(HTag && NewTag) : TagPrivate(std::move(NewTag.TagPrivate)) {}

// hanalysis::HTag &hanalysis::HTag::operator=(HTag NewTag) //note: pass by value and let compiler do the magics
// {
//     TagPrivate = std::move(NewTag.TagPrivate); //a now nullifyed, but that's ok, it's just a value
//     return *this;
// }


hanalysis::HTag::~HTag()
{
//     Print(HError, "Destructor");
}

void hanalysis::HTag::SetBdt(const float NewBdt)
{
//     TagPrivate->
    BdtM = NewBdt;
}

void hanalysis::HTag::SetBdt(const float NewBdt1, const float NewBdt2)
{
    //     TagPrivate->
    BdtM = (NewBdt1 + NewBdt2) / 2;
}

float hanalysis::HTag::Bdt() const
{
//     return TagPrivate->Bdt;
    return BdtM;
}

void hanalysis::HTag::SetTag(const int NewTag)
{
//     TagPrivate->
    TagM = NewTag;
}

void hanalysis::HTag::SetTag(const int NewTag1, const int NewTag2)
{
  //     TagPrivate->
  TagM = NewTag1 * NewTag2;
}

int hanalysis::HTag::Tag() const
{
//     return TagPrivate->Tag;
    return TagM;
}


void hanalysis::HTag::SetFlag(const bool NewFlag)
{
  //     FlagPrivate->
  FlagM = NewFlag;
}

void hanalysis::HTag::SetFlag(const bool NewFlag1, const bool NewFlag2)
{
  //     FlagPrivate->
  FlagM = NewFlag1 + NewFlag2;
}

int hanalysis::HTag::Flag() const
{
  //     return FlagPrivate->Flag;
  return FlagM;
}
