#include "Object.hh"

namespace analysis
{
  
Object::Object()
{
//   debug_level_ = Severity::information;
    debug_level_ = Severity::notification;
    //     debug_level_ = Severity::error;
    //     debug_level_ = Severity::debug;
//     Print(Severity::debug, "Constructor");
}

void Object::Printer(const std::string &Description) const
{
    const char Separator = ' ';
    const int NameSpaceWidth = 12;
    const int ClassWidth = 21;
    const int FunctionWidth = 25;
    std::cout << std::left << std::setw(NameSpaceWidth) << std::setfill(Separator) << NameSpaceName();
    std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << ClassName();
//     std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << func;
//     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
    std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Description;
}

void Object::Print(const Severity severity, const std::string &description) const
{
    if (severity > debug_level_) return;
    Printer(description);
    std::cout << std::endl;
}

// void Object::Print(const Severity severity, const std::string &description,const std::string class_name,const std::string method_name) const
// {
//   if (severity > debug_level_) return;
//   Printer(class_name, method_name,description);
//   std::cout << std::endl;
// }

void Object::Print(const Severity severity, const std::string &description, const fastjet::PseudoJet &Jet) const
{
    if (severity > debug_level_) return;
    Print(severity, description, Jet.e(), Jet.px(), Jet.py(), Jet.pz());
}

void Object::Print(const Severity severity, const std::string &description, float momentum[]) const
{
    if (severity > debug_level_) return;
    Print(severity, description, momentum[0], momentum[1], momentum[2], momentum[3]);
}

void Object::Printer(const std::string &name_space_name, const std::string &class_name, const std::string &Description) const
{
  const char Separator = ' ';
  const int NameSpaceWidth = 12;
  const int ClassWidth = 21;
  const int FunctionWidth = 25;
  std::cout << std::left << std::setw(NameSpaceWidth) << std::setfill(Separator) << name_space_name;
  std::cout << std::left << std::setw(ClassWidth) << std::setfill(Separator) << class_name;
  //     std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << func;
  //     cout << left << setw(ClassWidth) << setfill(Separator) << this->n; //  Class_Name();
  std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Description;
}

}
