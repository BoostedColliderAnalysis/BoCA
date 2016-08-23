
#include "boca/latex/Graphic.hh"
#include "boca/generic/Options.hh"

namespace boca
{

namespace latex
{

Graphic::Graphic()
{
    Initialize();
}

Graphic::Graphic(const std::string& name, const String& caption, double width)
{
    Initialize();
    AddGraphic(name, width);
    if (!caption.empty()) AddCaption(caption);
}

Graphic::Graphic(const std::vector< std::string>& names, const String& caption, double width)
{
    Initialize();
    AddGraphic(names, caption, width);
}

void Graphic::Initialize()
{
    graphic_ << environment_.Begin() << Command("centering");
}

void Graphic::AddGraphic(const std::string& name, double width)
{
    graphic_ << Command("includegraphics", Optional(Options("width", std::to_string(width) + Command("textwidth").str())), "{{../" + name + "}}");
}

void Graphic::AddCaption(const String& caption)
{
    graphic_ << Caption(caption.str(Medium::latex));
}

void Graphic::AddGraphic(const std::vector< std::string>& names, const String& caption, double width)
{
    for (auto const & name : names) {
        AddGraphic(name, width);
        if (!caption.empty()) AddCaption(caption);
    }
}

std::string Graphic::str() const
{
    return graphic_.str() + environment_.End();
}

}

}
