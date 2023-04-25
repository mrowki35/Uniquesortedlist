#include <stdexcept> // std::out_of_range
#include <utility>   // std::exchange
#include <array>
#include <limits>
#include <algorithm>
#include <string>
#include "SortedUniqueVectoredList.h"

struct SortedUniqueVectoredList::Bucket
{
    constexpr static size_t BUCKET_SIZE = 10;

    std::array<std::string, BUCKET_SIZE> values;
    size_t size{};

    Bucket* next = nullptr;
    Bucket* previous = nullptr;
};

SortedUniqueVectoredList::SortedUniqueVectoredList(const SortedUniqueVectoredList &source):head(nullptr), tail(nullptr), bucketCount_(0), size_(0), capacity_(0)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym
    copy(source);

}

SortedUniqueVectoredList::SortedUniqueVectoredList(SortedUniqueVectoredList &&another)
{
    this->move(std::move(another));
}

SortedUniqueVectoredList::~SortedUniqueVectoredList()
{
    free();
}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(SortedUniqueVectoredList &&another)
{
    std::swap(head, another.head);
    std::swap(tail, another.tail);
    std::swap(bucketCount_, another.bucketCount_);
    std::swap(size_, another.size_);
    std::swap(capacity_, another.capacity_);
    return *this;
}

void SortedUniqueVectoredList::insert(const std::string &value)
{
    if (contains(value)) {
        return;
    }
    if (tail == nullptr || tail->size == Bucket::BUCKET_SIZE) {
        allocate_new_bucket();
    }
    auto new_value = new char[value.size() + 1];
    std::copy(value.begin(), value.end(), new_value);
    new_value[value.size()] = '\0';
    tail->values[tail->size++] = new_value;
    ++size_;

}



void SortedUniqueVectoredList::erase(const std::string &value)
{
    if (!contains(value))
    {
        return;
    }

    Bucket* currentBucket = head;
    while (currentBucket != nullptr) {
        for (size_t i = 0; i < currentBucket->size; i++) {
            if (currentBucket->values[i] == value) {
                currentBucket->size--;
                for (size_t j = i; j < currentBucket->size; j++) {
                    currentBucket->values[j] = currentBucket->values[j + 1];
                }
                currentBucket->values[currentBucket->size].~basic_string();
                --size_;
                return;
            }
        }
        currentBucket = currentBucket->next;
    }
}



SortedUniqueVectoredList::operator std::string() const
{
    std::string result;
    for (Bucket* bucket_ptr = head; bucket_ptr != nullptr; bucket_ptr = bucket_ptr->next) {
        for (const auto& text : bucket_ptr->values) {
            if (!text.empty()) {
                result += text;
            }
        }
    }
    return result;
}

void SortedUniqueVectoredList::allocate_new_bucket()
{
    auto* newBucket = new Bucket;

    newBucket->previous = tail;
    if (tail != nullptr)
    {
        tail->next = newBucket;
    }

    tail = newBucket;

    if (head == nullptr)
    {
        head = newBucket;
    }


    capacity_ += Bucket::BUCKET_SIZE;
    bucketCount_++;
}

void SortedUniqueVectoredList::free()
{
    Bucket* currentBucket = head;
    while (currentBucket != nullptr)
    {
        Bucket* nextBucket = currentBucket->next;
        delete currentBucket;
        currentBucket = nextBucket;
    }

    head = nullptr;
    tail = nullptr;

    bucketCount_ = 0;
    size_ = 0;
    capacity_ = 0;
}


void SortedUniqueVectoredList::move(SortedUniqueVectoredList &&another)
{
    free();

    head = std::exchange(another.head, nullptr);
    tail = std::exchange(another.tail, nullptr);
    capacity_ = std::exchange(another.capacity_, 0);
    size_ = std::exchange(another.size_, 0);
    bucketCount_ = std::exchange(another.bucketCount_, 0);


}

void SortedUniqueVectoredList::copy(const SortedUniqueVectoredList &other)
{
    free();

    for (Bucket* currentBucket = other.head; currentBucket != nullptr; currentBucket = currentBucket->next)
    {
        Bucket* newBucket = new Bucket;
        std::copy(currentBucket->values.begin(), currentBucket->values.begin() + currentBucket->size, newBucket->values.begin());
        newBucket->size = currentBucket->size;
        if (tail != nullptr)
        {
            tail->next = newBucket;
        }
        newBucket->previous = tail;
        tail = newBucket;
        if (head == nullptr)
        {
            head = newBucket;
        }
    }


    bucketCount_ = other.bucketCount_;
    size_ = other.size_;
    capacity_ = other.capacity_;
}



bool SortedUniqueVectoredList::contains(const std::string &value) const
{
    for (Bucket* currentBucket = head; currentBucket != nullptr; currentBucket = currentBucket->next) {
        for (size_t i = 0; i < currentBucket->size; i++) {
            if (currentBucket->values[i] == value) {
                return true;
            }
        }
    }
    return false;
}

SortedUniqueVectoredList SortedUniqueVectoredList::operator-(const SortedUniqueVectoredList &another) const
{


    SortedUniqueVectoredList result;
    for (Bucket* currentBucket = head; currentBucket != nullptr; currentBucket = currentBucket->next)
    {
        for (size_t i = 0; i < currentBucket->size; i++)
        {
            const std::string& value = currentBucket->values[i];
            if (!another.contains(value))
            {
                result.insert(value);
            }
        }
    }

    return result;

}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator*=(const size_t howManyTimesMultiply)
{

    for (Bucket* currentBucket = head; currentBucket != nullptr; currentBucket = currentBucket->next)
    {
        for (size_t i = 0; i < currentBucket->size; ++i)
        {
            std::string& text = currentBucket->values[i];
            std::string multipliedText;
            for (size_t j = 0; j < howManyTimesMultiply; ++j)
            {
                multipliedText += text;
            }
            text = multipliedText;
        }
    }
    return *this;
}

string &SortedUniqueVectoredList::operator[](size_t index)
{

    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    size_t bucketIndex = index / Bucket::BUCKET_SIZE;
    size_t valueIndex = index % Bucket::BUCKET_SIZE;

    if (index == 0) {
        return head->values[0];
    }

    Bucket* currentBucket = head;
    for (size_t i = 0; i < bucketIndex; ++i) {
        currentBucket = currentBucket->next;
    }


    return currentBucket->values[valueIndex];
}

const string& SortedUniqueVectoredList::operator[](size_t index) const
{


    if (index >= size_) {
        throw std::out_of_range("Index out of range.");
    }

    Bucket* currentBucket = head;
    size_t i = index;
    while (i >= currentBucket->size)
    {
        i -= currentBucket->size;
        currentBucket = currentBucket->next;
    }

    return currentBucket->values[i];
}


SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(const SortedUniqueVectoredList &another)
{
    if (&another != this) {
        SortedUniqueVectoredList tmp(another);
        *this = std::move(tmp);
    }
    return *this;
}