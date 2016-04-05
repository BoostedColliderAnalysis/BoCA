#include "io/TreeReaderArray.hh"
// #define INFORMATION
#include "generic/DEBUG.hh"

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

bool TreeReaderArray::Iterator::operator==(const TreeReaderArray::Iterator& iterator) const
{
    // Compare two iterators as equal; follow C++14 requiring two past-end iterators to be equal.
    if (!IsValid() && !iterator.IsValid()) return true;
    return index_ == iterator.index_ && array_ == iterator.array_;
}

bool TreeReaderArray::Iterator::operator!=(const TreeReaderArray::Iterator& iterator) const
{
    return (*this == iterator);
}
TreeReaderArray::Iterator TreeReaderArray::Iterator::operator++(int)
{
    // Post-increment (it++).
    Iterator iterator = *this;
    this->operator++();
    return iterator;
}
TreeReaderArray::Iterator& TreeReaderArray::Iterator::operator++()
{
    // Pre-increment (++it).
    if (IsValid()) {
        ++index_;
        if (index_ >= array_->GetSize()) {
            // Remember that it's past-end.
            array_ = 0;
        }
    }
    return *this;
}

TObject& TreeReaderArray::Iterator::operator*() const
{
    // Get the referenced element.
    R__ASSERT(array_ && "invalid iterator!");
    return array_->At(index_);
}

TreeReaderArray::TreeReaderArray(TTreeReader& tr, const std::__cxx11::string& branchname, TClass& cl) :
    TTreeReaderArrayBase(&tr, branchname.c_str(), &cl)
{
    // Create an array reader of branch "branchname" for TTreeReader "tr".
}

TObject& TreeReaderArray::At(size_t idx)
{
    return *(TObject*)UntypedAt(idx);
}

TObject& TreeReaderArray::operator[](size_t idx)
{
    return At(idx);
}

TreeReaderArray::Iterator TreeReaderArray::begin()
{
    // Return an iterator to the 0th TTree entry or an empty iterator if the
    // array is empty.
    return IsEmpty() ? Iterator() : Iterator(0, this);
}

TreeReaderArray::Iterator TreeReaderArray::end() const
{
    return Iterator();
}

const char* TreeReaderArray::GetDerivedTypeName() const
{
    std::cout << GetBranchName() << std::endl;
    return GetBranchName();
}

}
