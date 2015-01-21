# include "HTag.hh"
# include "HTagPrivate.hh"

hanalysis::HTag::HTag() : TagPrivate(new HTagPrivate(this))
{
//     Print(HInformation, "Constructor");
  TagPrivate->InitialValue = -10;
  TagPrivate->Bdt = TagPrivate->InitialValue;
  TagPrivate->Tag = TagPrivate->InitialValue;

}


hanalysis::HTag::HTag(hanalysis::HTagPrivate& NewTagPrivate) : TagPrivate(&NewTagPrivate)
{
  //     Print(HInformation, "Constructor");
  TagPrivate->InitialValue = -10;
  TagPrivate->Bdt = TagPrivate->InitialValue;
  TagPrivate->Tag = TagPrivate->InitialValue;

}

hanalysis::HTag::~HTag()
{

//     Print(HInformation, "Destructor");
// delete TagPrivate; // FIXME why cant i delete the private class
}

void hanalysis::HTag::SetBdt(const float NewBdt) {
  TagPrivate->Bdt = NewBdt;
}

float hanalysis::HTag::Bdt() const {
  return TagPrivate->Bdt;
}

void hanalysis::HTag::SetTag(const int NewTag) {
  TagPrivate->Tag = NewTag;
}

int hanalysis::HTag::Tag() const {
  return TagPrivate->Tag;
}
