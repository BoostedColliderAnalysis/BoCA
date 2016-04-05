#pragma once

#include <string>
#include "TTreeReaderArray.h"

class TTreeReader;
class TClass;
class TObject;

namespace boca
{

class TreeReaderArray : public ROOT::TTreeReaderArrayBase
{

public:

    struct Iterator:

        public std::iterator<std::input_iterator_tag, TObject, long> {

        Iterator();

        Iterator(size_t idx, TreeReaderArray* array);

        std::size_t index_;

        TreeReaderArray* array_;

        bool IsValid() const;

        bool operator==(const Iterator& iterator_) const;

        bool operator!=(const Iterator& iterator_) const;

        Iterator operator++(int);

        Iterator& operator++();

        TObject& operator*() const;
    };

    TreeReaderArray(TTreeReader& tr, std::string const& branchname, TClass& cl);

    TObject& At(size_t idx);

    TObject& operator[](size_t idx);

    typedef Iterator iterator;

    Iterator begin();

    Iterator end() const;

protected:

    virtual const char* GetDerivedTypeName() const;

};

}

