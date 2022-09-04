// Copyright (c) 2022 zhengzhibing All rights reserved.
// Description: 双向Map，严格保证左右值唯一

#ifndef TOY_BIMAP_H
#define TOY_BIMAP_H
#include <type_traits>
#include <map>
namespace Utility {
enum ViewDir {
    L,  // left
    R   // right
};

template<class LType, class RType>
class BiMap {
public:
    using LViewCIter = typename std::map<LType, RType>::const_iterator;
    using LViewCRIter = typename std::map<LType, RType>::const_reverse_iterator;
    using RViewCIter = typename std::map<RType, LType>::const_iterator;
    using RViewCRIter = typename std::map<RType, LType>::const_reverse_iterator;

public:
    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCIter> Begin() const noexcept
    {
        return leftMapView.begin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCIter> CBegin() const noexcept
    {
        return leftMapView.cbegin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCIter> Begin() const noexcept
    {
        return rightMapView.begin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCIter> CBegin() const noexcept
    {
        return rightMapView.cbegin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCIter> End() const noexcept
    {
        return leftMapView.end();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCIter> CEnd() const noexcept
    {
        return leftMapView.cend();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCIter> End() const noexcept
    {
        return rightMapView.end();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCIter> CEnd() const noexcept
    {
        return rightMapView.cend();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCRIter> RBegin() const noexcept
    {
        return leftMapView.rbegin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCRIter> CRBegin() const noexcept
    {
        return leftMapView.crbegin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCRIter> RBegin() const noexcept
    {
        return rightMapView.rbegin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCRIter> CRBegin() const noexcept
    {
        return rightMapView.crbegin();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCRIter> REnd() const noexcept
    {
        return leftMapView.rend();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCRIter> CREnd() const noexcept
    {
        return leftMapView.crend();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCRIter> REnd() const noexcept
    {
        return rightMapView.rend();
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCRIter> CREnd() const noexcept
    {
        return rightMapView.crend();
    }

    template<ViewDir DIR>
    const std::enable_if_t<DIR == L, RType>& At(const LType& left)
    {
        return rightMapView[left];
    }

    template<ViewDir DIR>
    const std::enable_if_t<DIR == L, RType>& At(LType&& left)
    {
        return leftMapView[left];
    }

    template<ViewDir DIR>
    const std::enable_if_t<DIR == R, LType>& At(const RType& right)
    {
        return rightMapView[right];
    }

    template<ViewDir DIR>
    const std::enable_if_t<DIR == R, LType>& At(RType&& right)
    {
        return rightMapView[right];
    }

    bool Insert(const LType& left, const RType& right)
    {
        if (leftMapView.find(left) != leftMapView.end()) {
            return false;
        }
        if (rightMapView.find(right) != rightMapView.end()) {
            return false;
        }
        leftMapView[left] = right;
        rightMapView[right] = left;
        return true;
    }

    bool Insert(LType&& left, RType&& right)
    {
        if (leftMapView.find(left) != leftMapView.end()) {
            return false;
        }
        if (rightMapView.find(right) != rightMapView.end()) {
            return false;
        }
        leftMapView[left] = right;
        rightMapView[right] = left;
        return true;
    }

    // insert force
    void InsertF(const LType& left, const RType& right)
    {
        auto leftIter = leftMapView.find(left);
        if (leftIter != leftMapView.end()) {
            rightMapView.erase(leftIter->second);
        }

        auto rightIter = rightMapView.find(right);
        if (rightIter != rightMapView.end()) {
            leftMapView.erase(rightIter->second);
        }
        leftMapView[left] = right;
        rightMapView[right] = left;
    }

    // insert force
    void InsertF(LType&& left, RType&& right)
    {
        auto leftIter = leftMapView.find(left);
        if (leftIter != leftMapView.end()) {
            rightMapView.erase(leftIter->second);
        }

        auto rightIter = rightMapView.find(right);
        if (rightIter != rightMapView.end()) {
            leftMapView.erase(rightIter->second);
        }

        leftMapView[left] = right;
        rightMapView[right] = left;
    }

    template<ViewDir DIR>
    void Erase(const std::enable_if_t<DIR == L, LType>& left)
    {
        auto leftIter = leftMapView.find(left);
        if (leftIter != leftMapView.end()) {
            rightMapView.erase(leftIter->second);
        }
        leftMapView.erase(leftIter);
    }

    template<ViewDir DIR>
    void Erase(const std::enable_if_t<DIR == R, RType>& right)
    {
        auto rightIter = rightMapView.find(right);
        if (rightIter != rightMapView.end()) {
            leftMapView.erase(rightIter->second);
        }
        rightMapView.erase(rightIter);
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == L, LViewCIter> Find(const std::enable_if_t<DIR == L, LType>& left) const
    {
        return leftMapView.find(left);
    }

    template<ViewDir DIR>
    std::enable_if_t<DIR == R, RViewCIter> Find(const std::enable_if_t<DIR == R, RType>& right) const
    {
        return rightMapView.find(right);
    }

    bool Empty() const { return leftMapView.empty(); };

    size_t Size() const { return leftMapView.size(); }

    void Clear()
    {
        leftMapView.clear();
        rightMapView.clear();
    }

private:
    std::map<LType, RType> leftMapView;
    std::map<RType, LType> rightMapView;
};
}  // namespace Utility
#endif  // TOY_BIMAP_H
