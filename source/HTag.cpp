# include "HTag.hh"

// # include <memory>
// # include "HTagPrivate.hh"

hanalysis::HTag::HTag()
// : TagPrivate(new HTagPrivate(this))
{
//     Print(HInformation, "Constructor");
//     TagPrivate->InitialValue = -10;
//     TagPrivate->Bdt = TagPrivate->InitialValue;
//     TagPrivate->Tag = TagPrivate->InitialValue;

    initial_value_ = -10;
    bdt_ = initial_value_;
    tag_ = 0;
    flag_ = false;
    degenerate_ = false;

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
    bdt_ = NewBdt;
}

void hanalysis::HTag::SetBdt(const float NewBdt1, const float NewBdt2)
{
    //     TagPrivate->
    bdt_ = (NewBdt1 + NewBdt2) / 2;
}

float hanalysis::HTag::Bdt() const
{
//     return TagPrivate->Bdt;
    return bdt_;
}

void hanalysis::HTag::SetTag(const int NewTag)
{
//     TagPrivate->
    tag_ = NewTag;
}

void hanalysis::HTag::SetTag(const int NewTag1, const int NewTag2)
{
  //     TagPrivate->
  tag_ = NewTag1 * NewTag2;
}

int hanalysis::HTag::Tag() const
{
//     return TagPrivate->Tag;
    return tag_;
}


void hanalysis::HTag::SetFlag(const bool NewFlag)
{
  //     FlagPrivate->
  flag_ = NewFlag;
}

void hanalysis::HTag::SetFlag(const bool NewFlag1, const bool NewFlag2)
{
  //     FlagPrivate->
  flag_ = NewFlag1 + NewFlag2;
}

bool hanalysis::HTag::Flag() const
{
  //     return FlagPrivate->Flag;
  return flag_;
}
