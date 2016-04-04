#pragma once
#include "TTreeReaderArray.h"

namespace boca
{

class TreeReaderArray : public ROOT::TTreeReaderArrayBase
{

public:

    // Iterator through the indices of a TTreeReaderArray.
    struct Iterator:
        public std::iterator<std::input_iterator_tag, TBranch, long> {
        // Default initialized, past-end iterator.
        Iterator() :
            fIndex(0), fArray(0) {}

        // Initialize with an array and index.
        Iterator(size_t idx, TreeReaderArray* array) :
            fIndex(idx), fArray(array) {}

        size_t fIndex; // Current index in the array.
        TreeReaderArray* fArray; // The array iterated over; 0 if invalid / end.

        bool IsValid() const {
            return fArray;
        }

        bool operator==(const Iterator& lhs) const {
            // Compare two iterators as equal; follow C++14 requiring two past-end
            // iterators to be equal.
            if (!IsValid() && !lhs.IsValid()) {
                return true;
            }
            return fIndex == lhs.fIndex && fArray == lhs.fArray;
        }

        bool operator!=(const Iterator& lhs) const {
            // Compare not equal.
            return !(*this == lhs);
        }

        Iterator operator++(int) {
            // Post-increment (it++).
            Iterator ret = *this;
            this->operator++();
            return ret;
        }

        Iterator& operator++() {
            // Pre-increment (++it).
            if (IsValid()) {
                ++fIndex;
                if (fIndex >= fArray->GetSize()) {
                    // Remember that it's past-end.
                    fArray = 0;
                }
            }
            return *this;
        }

        TObject& operator*() const {
            // Get the referenced element.
            R__ASSERT(fArray && "invalid iterator!");
            return fArray->At(fIndex);
        }
    };

    TreeReaderArray(TTreeReader& tr, std::string const& branchname, TClass& cl):
        TTreeReaderArrayBase(&tr, branchname.c_str(), &cl) {
        // Create an array reader of branch "branchname" for TTreeReader "tr".
    }

    TObject& At(size_t idx) {
        return *(TObject*)UntypedAt(idx);
    }
    TObject& operator[](size_t idx) {
        return At(idx);
    }

    typedef Iterator iterator;

    Iterator begin() {
        // Return an iterator to the 0th TTree entry or an empty iterator if the
        // array is empty.
        return IsEmpty() ? Iterator() : Iterator(0, this);
    }
    Iterator end() const {
        return Iterator();
    }

protected:
// #define R__TreeReaderArray_TypeString(T) #T
    virtual const char* GetDerivedTypeName() const {
       std::cout << GetBranchName() << std::endl;
        return GetBranchName();
    }
// #undef R__TreeReaderArray_TypeString
    // FIXME: re-introduce once we have ClassDefTInline!
    //ClassDefT(TreeReaderArray, 0);//Accessor to member of an object stored in a collection
};

}
