#include "TTreeReader.h"
#include "boca/io/TreeReaderArray.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

TreeReaderArray::Iterator::Iterator():
    index_(0),
    array_(0) {}

TreeReaderArray::Iterator::Iterator(std::size_t index, TreeReaderArray* array):
    index_(index),
    array_(array) {}

bool TreeReaderArray::Iterator::IsValid() const
{
    return array_;
}

// Compare two iterators as equal; follow C++14 requiring two past-end iterators to be equal.
bool TreeReaderArray::Iterator::operator==(const Iterator& iter) const
{
    if (!IsValid() && !iter.IsValid()) return true;
    return index_ == iter.index_ && array_ == iter.array_;
}

bool TreeReaderArray::Iterator::operator!=(const Iterator& iter) const
{
    return !(*this == iter);
}
TreeReaderArray::Iterator TreeReaderArray::Iterator::operator++(int)
{
    // Post-increment (it++).
    auto iter= *this;
    this->operator++();
    return iter;
}
TreeReaderArray::Iterator& TreeReaderArray::Iterator::operator++()
{
    // Pre-increment (++it).
    if (!IsValid()) return *this;
    ++index_;
    // Remember that it's past-end.
    if (index_ >= array_->GetSize()) array_ = 0;
    return *this;
}

TObject& TreeReaderArray::Iterator::operator*() const
{
    // Get the referenced element.
    R__ASSERT(array_ && "invalid iterator!");
    return array_->At(index_);
}

// Create an array reader of branch "branchname" for TTreeReader "tr".
TreeReaderArray::TreeReaderArray(TTreeReader& tree_reader, std::string const& branch_name, TClass& cl) :
    TTreeReaderArrayBase(&tree_reader, branch_name.c_str(), &cl)
{}

TObject& TreeReaderArray::At(std::size_t index)
{
  return *static_cast<TObject*>(UntypedAt(index));
}

TObject& TreeReaderArray::operator[](std::size_t index)
{
    return At(index);
}

// Return an iterator to the 0th TTree entry or an empty iterator if the array is empty.
TreeReaderArray::Iterator TreeReaderArray::begin()
{
    return IsEmpty() ? Iterator() : Iterator(0, this);
}

TreeReaderArray::Iterator TreeReaderArray::end() const
{
    return Iterator();
}

char const* TreeReaderArray::GetDerivedTypeName() const
{
    return GetBranchName();
}

}
