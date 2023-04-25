#ifndef UNIQUEVECTOREDLIST_SORTEDUNIQUEVECTOREDLIST_H
#define UNIQUEVECTOREDLIST_SORTEDUNIQUEVECTOREDLIST_H

#include <cstddef>
#include <string>

class SortedUniqueVectoredList
{
public:

    struct Bucket;

    SortedUniqueVectoredList() = default;
    SortedUniqueVectoredList(const SortedUniqueVectoredList& source);
    SortedUniqueVectoredList(SortedUniqueVectoredList&& source);
    ~SortedUniqueVectoredList();

    SortedUniqueVectoredList& operator=(const SortedUniqueVectoredList& another);
    SortedUniqueVectoredList& operator=(SortedUniqueVectoredList&& another);

    auto size() const
    {
        return size_;
    }

    auto capacity() const
    {
        return capacity_;
    }

    auto bucket_count() const
    {
        return bucketCount_;
    }

    void insert(const std::string& value);
    std::string& operator[](size_t index);
    const std::string& operator[](size_t index) const;
    SortedUniqueVectoredList operator-(const SortedUniqueVectoredList& another) const;
    SortedUniqueVectoredList& operator*=(const size_t howManyTimesMultiply);

    explicit operator std::string() const;

    void erase(const std::string& value);

    friend std::ostream& operator<<(std::ostream& stream, const SortedUniqueVectoredList& container);

protected:
    void allocate_new_bucket();
    void free();
    void move(SortedUniqueVectoredList&& another);
    void copy(const SortedUniqueVectoredList& other);
    bool contains(const std::string& value) const;


private:
    Bucket *head = nullptr, *tail = nullptr;

    size_t bucketCount_{}, size_{}, capacity_{};
};




























#endif //UNIQUEVECTOREDLIST_SORTEDUNIQUEVECTOREDLIST_H
