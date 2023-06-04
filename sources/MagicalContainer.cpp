//
// Created by Lara Abu Hamad on 5/24/23.
//

#include "MagicalContainer.hpp"

namespace ariel {
    MagicalContainer::MagicalContainer() : elements(), prime() {}

    size_t MagicalContainer::size() {
        return this->elements.size();
    }

    void MagicalContainer::addElement(int elem) {
        auto it = find(elements.begin(), elements.end(), elem);
        if(it != elements.end())
            return;
        if (isPrime(elem)) {
            sortElements(elem, prime);
        }
        sortElements(elem, elements);
    }

    void MagicalContainer::removeElement(int elem) {
        auto it = find(elements.begin(), elements.end(), elem);
        if (it == elements.end()) {
            throw runtime_error("Element not found in container");
        }
        elements.erase(it);
        if (isPrime(elem)) {
            it = find(prime.begin(), prime.end(), elem);
            prime.erase(it);
        }
    }

    void MagicalContainer::sortElements(int elem, vector<int> &elmnts) {
        if (elmnts.empty()) {
            elmnts.push_back(elem);
            return;
        }
        auto it = elmnts.begin();
        while (it != elmnts.end() && *it < elem) {
            ++it;
        }
        elmnts.insert(it, elem);
    }

    bool MagicalContainer::isPrime(int number) {
        if (number <= 1 || number % 2 == 0) {
            return number == 2;
        }

        for (int i = 3; i * i <= number; i += 2) {
            if (number % i == 0) {
                return false;
            }
        }

        return true;
    }

    vector<int> MagicalContainer::getElements() {
        return elements;
    }

    MagicalContainer::AscendingIterator::AscendingIterator() : index(0), magc(new MagicalContainer()) {}

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &magc) : magc(&magc), index(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : magc(other.magc) {}

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        AscendingIterator beginIterator(*magc);
        return beginIterator;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        AscendingIterator endIterator(*magc);
        endIterator.index = static_cast<int>(magc->size());
        return endIterator;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
        if (magc != other.magc) {
            throw std::runtime_error("Cannot compare iterators from different containers");
        }
        if (*this == other)
            return false;
        return index > other.index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
        if (magc != other.magc) {
            throw std::runtime_error("Cannot compare iterators from different containers");
        }
        if (*this == other)
            return false;
        return index < other.index;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
        return (magc == other.magc && index == other.index);
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
        return !(*this == other);
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        if (index < magc->size()) {
            return magc->getElements()[static_cast<size_t >(index)];
        } else {
            throw runtime_error("Iterator out of range");
        }
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (magc && index < magc->size()) {
            ++index;
        } else {
            throw runtime_error("Iterator out of range");
        }
        return *this;
    }

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
        if (this != &other) {
            if (magc != other.magc) {
                throw std::runtime_error("Assignment of iterators pointing to different containers");
            }
            index = other.index;
        }
        return *this;
    }

    int MagicalContainer::AscendingIterator::getIndex() {
        return index;
    }

    MagicalContainer MagicalContainer::AscendingIterator::getContainer() {
        return *magc;
    }

    bool MagicalContainer::AscendingIterator::operator==(const ariel::MagicalContainer::Iterator &other) const {
        const AscendingIterator *other_ascending = dynamic_cast<const AscendingIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this == *other_ascending;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const ariel::MagicalContainer::Iterator &other) const {
        const AscendingIterator *other_ascending = dynamic_cast<const AscendingIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this != *other_ascending;
    }

    bool MagicalContainer::AscendingIterator::operator>(const ariel::MagicalContainer::Iterator &other) const {
        const AscendingIterator *other_ascending = dynamic_cast<const AscendingIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this > *other_ascending;
    }

    bool MagicalContainer::AscendingIterator::operator<(const ariel::MagicalContainer::Iterator &other) const {
        const AscendingIterator *other_ascending = dynamic_cast<const AscendingIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this < *other_ascending;
    }

    MagicalContainer::PrimeIterator::PrimeIterator() : magc(new MagicalContainer()), currIndex(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &magc) : magc(&magc), currIndex(0){}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : magc(other.magc) {}

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        PrimeIterator beginIterator(*magc);
        return beginIterator;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        PrimeIterator endIterator(*magc);
        endIterator.currIndex = static_cast<int>(magc->prime.size());
        return endIterator;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
        if (magc != other.magc) {
            throw std::runtime_error("Cannot compare iterators from different containers");
        }
        if (*this == other)
            return false;
        return currIndex > other.currIndex;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
        if (magc != other.magc) {
            throw std::runtime_error("Cannot compare iterators from different containers");
        }
        if (*this == other)
            return false;
        return currIndex < other.currIndex;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
        return (magc == other.magc && currIndex == other.currIndex);
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
        return !(*this == other);
    }

    int MagicalContainer::PrimeIterator::operator*() {
        if (magc && currIndex < magc->prime.size()) {
            return magc->prime[static_cast<size_t>(currIndex)];
        }
        throw runtime_error("Iterator out of range");
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (magc && currIndex < magc->prime.size()) {
            ++currIndex;
        } else {
            throw runtime_error("Iterator out of range");
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
        if (this != &other) {
            if (magc != other.magc) {
                throw std::runtime_error("Iterators have different containers");
            }
            currIndex = other.currIndex;
        }
        return *this;
    }

    int MagicalContainer::PrimeIterator::getIndex() {
        return currIndex;
    }

    MagicalContainer MagicalContainer::PrimeIterator::getContainer() {
        return *magc;
    }

    bool MagicalContainer::PrimeIterator::operator==(const ariel::MagicalContainer::Iterator &other) const {
        const PrimeIterator *other_ascending = dynamic_cast<const PrimeIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this == *other_ascending;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const ariel::MagicalContainer::Iterator &other) const {
        const PrimeIterator *other_ascending = dynamic_cast<const PrimeIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this != *other_ascending;
    }

    bool MagicalContainer::PrimeIterator::operator>(const ariel::MagicalContainer::Iterator &other) const {
        const PrimeIterator *other_ascending = dynamic_cast<const PrimeIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this > *other_ascending;
    }

    bool MagicalContainer::PrimeIterator::operator<(const ariel::MagicalContainer::Iterator &other) const {
        const PrimeIterator *other_ascending = dynamic_cast<const PrimeIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this < *other_ascending;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator() : magc(new MagicalContainer()), frontIndex(0), backIndex(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &magc) : magc(&magc), frontIndex(0), backIndex(magc.size() - 1) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : magc(other.magc) {}

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        SideCrossIterator beginIterator(*magc);
        beginIterator.frontIndex = 0;
        beginIterator.backIndex = magc->size() - 1;
        return beginIterator;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        SideCrossIterator endIterator(*magc);
        endIterator.frontIndex = static_cast<int>(magc->size());
        endIterator.backIndex = static_cast<int>(magc->size());
        return endIterator;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
        if (magc != other.magc) {
            throw std::runtime_error("Cannot compare iterators from different containers");
        }
        if (*this == other)
            return false;
        return (frontIndex > other.frontIndex && backIndex >= other.backIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
        if (magc != other.magc) {
            throw std::runtime_error("Cannot compare iterators from different containers");
        }
        if (*this == other)
            return false;
        return (frontIndex < other.frontIndex && backIndex < other.backIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
        if (magc != other.magc) {
            throw std::runtime_error("Cannot compare iterators from different containers");
        }
        if (magc->getElements().empty()) {
            return true;
        }
        return (magc == other.magc && frontIndex == other.frontIndex && backIndex == other.backIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
        return !(*this == other);
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        if (frontIndex <= backIndex) {
            if ((frontIndex % 2 == 0 && (backIndex % 2 == (magc->size() - 1) % 2)) ||
                (frontIndex % 2 != 0 && (backIndex % 2 != (magc->size() - 1) % 2))) {
                return magc->getElements()[static_cast<size_t >(frontIndex)];
            } else {
                return magc->getElements()[static_cast<size_t >(backIndex)];
            }
        }
        return 0;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if (frontIndex <= backIndex) {
            if ((frontIndex % 2 == 0 && (backIndex % 2 == (magc->size() - 1) % 2)) ||
                (frontIndex % 2 != 0 && (backIndex % 2 != (magc->size() - 1) % 2))) {
                ++frontIndex;
                if(frontIndex > magc->size())
                    throw runtime_error("Iterator out of range");
            } else {
                --backIndex;
                if(backIndex < 0)
                    throw runtime_error("Iterator out of range");
            }
        }
        if (frontIndex > backIndex) {
            frontIndex = backIndex = static_cast<int >(magc->size());
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
        if (this != &other) {
            if (magc != other.magc)
                throw runtime_error("Iterators have different containers");
            frontIndex = other.frontIndex;
            backIndex = other.backIndex;
        }
        return *this;
    }

    int MagicalContainer::SideCrossIterator::getBindex() {
        return backIndex;
    }

    int MagicalContainer::SideCrossIterator::getFindex() {
        return frontIndex;
    }

    MagicalContainer MagicalContainer::SideCrossIterator::getContainer() {
        return *magc;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const ariel::MagicalContainer::Iterator &other) const {
        const SideCrossIterator *other_ascending = dynamic_cast<const SideCrossIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this == *other_ascending;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const ariel::MagicalContainer::Iterator &other) const {
        const SideCrossIterator *other_ascending = dynamic_cast<const SideCrossIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this != *other_ascending;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const ariel::MagicalContainer::Iterator &other) const {
        const SideCrossIterator *other_ascending = dynamic_cast<const SideCrossIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this > *other_ascending;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const ariel::MagicalContainer::Iterator &other) const {
        const SideCrossIterator *other_ascending = dynamic_cast<const SideCrossIterator*>(&other);
        if (!other_ascending)
            throw runtime_error("Iterators have different types");
        return *this < *other_ascending;
    }
}