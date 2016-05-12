#pragma once

#include <string>

#include "TTreeReaderArray.h"

class TTreeReader;
class TClass;
class TObject;

namespace boca
{

class TreeReaderArray : public ROOT::Internal::TTreeReaderArrayBase
{

public:

    class Iterator : public std::iterator<std::input_iterator_tag, TObject, long>
    {

    public:

        Iterator();

        Iterator(std::size_t index, TreeReaderArray* array);

        bool IsValid() const;

        bool operator==(const Iterator& iter) const;

        bool operator!=(const Iterator& iter) const;

        Iterator operator++(int);

        Iterator& operator++();

        TObject& operator*() const;

    private:

        std::size_t index_;

        TreeReaderArray* array_;

    };

    TreeReaderArray(TTreeReader& tree_reader, std::string const& branch_name, TClass& cl);

    TObject& At(std::size_t index);

    TObject& operator[](std::size_t index);

    using iterator = Iterator;

    Iterator begin();

    Iterator end() const;

protected:

    virtual char const* GetDerivedTypeName() const;

};

}

