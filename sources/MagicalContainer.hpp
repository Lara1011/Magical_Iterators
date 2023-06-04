//
// Created by Lara Abu Hamad on 5/24/23.
//

#ifndef CPP_HW5_MAGICALCONTAINER_HPP
#define CPP_HW5_MAGICALCONTAINER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;
namespace ariel {
    class MagicalContainer {
    private:
        vector<int> elements;
        vector<int> prime;

    public:
        MagicalContainer();

        void addElement(int elem);

        void removeElement(int elem);

        size_t size();

        vector<int> getElements();

        void sortElements(int elem, vector<int> &elmnts);

        static bool isPrime(int number);

        class Iterator {
        public:
            Iterator() = default;

            virtual ~Iterator() = default;

            Iterator(const Iterator &other) = default;

            Iterator(Iterator &&other) = default;

            Iterator &operator=(const Iterator &other) = default;

            Iterator& operator=(Iterator&& other) = default;

            virtual bool operator==(const Iterator& other) const = 0;

            virtual bool operator!=(const Iterator& other) const = 0;

            virtual bool operator>(const Iterator& other) const = 0;

            virtual bool operator<(const Iterator& other) const = 0;
        };

        class AscendingIterator : public Iterator{
        private:
            MagicalContainer *magc;
            int index;

        public:
            AscendingIterator();

            AscendingIterator(MagicalContainer &magc);

            AscendingIterator(const AscendingIterator &other);

            ~AscendingIterator() override = default;

            AscendingIterator(AscendingIterator &&other) noexcept
                    : magc(other.magc), index(other.index) {
                other.index = 0;
            }

            AscendingIterator &operator=(AscendingIterator &&other) noexcept {
                if (this != &other) {
                    magc = other.magc;
                    index = other.index;
                    other.index = 0;
                }
                return *this;
            }

            AscendingIterator &operator=(const AscendingIterator &other);

            bool operator==(const AscendingIterator &other) const;

            bool operator!=(const AscendingIterator &other) const;

            bool operator>(const AscendingIterator &other) const;

            bool operator<(const AscendingIterator &other) const;

            int operator*() const;

            AscendingIterator &operator++();

            AscendingIterator begin();

            AscendingIterator end();

            int getIndex();

            MagicalContainer getContainer();

            bool operator==(const Iterator &other) const override;

            bool operator!=(const Iterator &other) const override;

            bool operator>(const Iterator &other) const override;

            bool operator<(const Iterator &other) const override;
        };

        class SideCrossIterator : public Iterator{
        private:
            MagicalContainer *magc;
            int frontIndex;
            int backIndex;
        public:
            SideCrossIterator();

            SideCrossIterator(MagicalContainer &magc);

            SideCrossIterator(const SideCrossIterator &other);

            ~SideCrossIterator() override = default;

            SideCrossIterator(SideCrossIterator &&other) noexcept
                    : magc(other.magc), frontIndex(other.frontIndex), backIndex(other.backIndex) {
                other.frontIndex = 0;
                other.backIndex = 0;
            }

            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept {
                if (this != &other) {
                    magc = other.magc;
                    frontIndex = other.frontIndex;
                    backIndex = other.backIndex;
                    other.frontIndex = 0;
                    other.backIndex = 0;
                }
                return *this;
            }

            SideCrossIterator &operator=(const SideCrossIterator &other);

            bool operator==(const SideCrossIterator &other) const;

            bool operator!=(const SideCrossIterator &other) const;

            bool operator>(const SideCrossIterator &other) const;

            bool operator<(const SideCrossIterator &other) const;

            int operator*() const;

            SideCrossIterator &operator++();

            SideCrossIterator begin();

            SideCrossIterator end();

            int getFindex();

            int getBindex();

            MagicalContainer getContainer();

            bool operator==(const Iterator &other) const override;

            bool operator!=(const Iterator &other) const override;

            bool operator>(const Iterator &other) const override;

            bool operator<(const Iterator &other) const override;
        };

        class PrimeIterator : public Iterator{
        private:
            MagicalContainer *magc;
            int currIndex;

        public:
            PrimeIterator();

            PrimeIterator(MagicalContainer &mgc);

            PrimeIterator(const PrimeIterator &other);

            ~PrimeIterator() override = default;

            PrimeIterator(PrimeIterator &&other) noexcept
                    : magc(other.magc), currIndex(other.currIndex) {
                other.currIndex = 0;
            }

            PrimeIterator &operator=(PrimeIterator &&other) noexcept {
                if (this != &other) {
                    magc = other.magc;
                    currIndex = other.currIndex;
                    other.currIndex = 0;
                }
                return *this;
            }

            PrimeIterator &operator=(const PrimeIterator &other);

            bool operator==(const PrimeIterator &other) const;

            bool operator!=(const PrimeIterator &other) const;

            bool operator>(const PrimeIterator &other) const;

            bool operator<(const PrimeIterator &other) const;

            int operator*();

            PrimeIterator &operator++();

            PrimeIterator begin();

            PrimeIterator end();

            int getIndex();

            MagicalContainer getContainer();

            bool operator==(const Iterator &other) const override;

            bool operator!=(const Iterator &other) const override;

            bool operator>(const Iterator &other) const override;

            bool operator<(const Iterator &other) const override;
        };
    };
}
#endif //CPP_HW5_MAGICALCONTAINER_HPP
