#pragma once

namespace boca
{

template <template <typename> class Container_, template <typename> class SubContainer_, typename Value_>
class Iterator2
{
public:
    Iterator2(Container_<Value_>* container, int position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (Iterator2 const& iterator) const {
        return position_ != iterator.position_;
    }

    SubContainer_<Value_>& operator*() {
        return (*container_)(position_);
    }

    Iterator2 const& operator++ () {
        ++position_;
        return *this;
    }

private:
    int position_;
    Container_<Value_>* container_;
};

template <template <typename> class Container_, template <typename> class SubContainer_, typename Value_>
class ConstIterator2
{
public:
    ConstIterator2(Container_<Value_> const* container, int position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (ConstIterator2 const& iterator) const {
        return position_ != iterator.position_;
    }

    SubContainer_<Value_> operator*() const {
        return (*container_)(position_);
    }

    ConstIterator2 const& operator++ () {
        ++position_;
        return *this;
    }

private:
    int position_;
    Container_<Value_> const* container_;
};

template <template <typename> class Container_, typename Value_>
class Iterator
{
public:
    Iterator(Container_<Value_>* container, int position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (Iterator& iterator) const {
        return position_ != iterator.position_;
    }

    Value_& operator*() {
        return (*container_)(position_);
    }

    Iterator const& operator++ () {
        ++position_;
        return *this;
    }

private:
    int position_;
    Container_<Value_>* container_;
};

template <template <typename> class Container_, typename Value_>
class ConstIterator
{
public:
    ConstIterator(Container_<Value_> const* container, int position) :
        position_(position),
        container_(container)
    {}

    bool operator!= (ConstIterator const& iterator) const {
        return position_ != iterator.position_;
    }

    Value_ operator*() const {
        return (*container_)(position_);
    }

    ConstIterator const& operator++ () {
        ++position_;
        return *this;
    }

private:
    int position_;
    Container_<Value_> const* container_;
};

}
