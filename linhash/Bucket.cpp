#include "Bucket.hpp"

#include <iostream>
#include <algorithm>

Bucket::Bucket() : overflowBucket(nullptr)
{

}

Bucket::~Bucket()
{
    if (overflowBucket)
    {
        delete overflowBucket;
    }
}

// Insert the key into the bucket, or one of its overflow buckets.
// Return true if an overflow bucket was used
bool Bucket::insert(std::string input)
{
    // Insert your code here
    // if bucket not dull, insert normally
    key_vec.push_back(input);
    if (keys.size() < MAX_BUCKET_SIZE) {
        keys.push_back(input);
        return false;
    } 
    else {
        if (overflowBucket == nullptr) {
            overflowBucket = new Bucket;
            overflowBucket->insert(input);
        }
        else {
            overflowBucket->insert(input);
        }
        return true;
    }
}

// DO NOT MODIFY THIS FUNCTION!
// 
// Print all keys in this bucket and all of its overflow buckets.
// Keys are separated by spaces, and buckets are separated by '|'.
void Bucket::print()
{
    std::cout << "| ";
    for (auto& key : keys)
    {
        std::cout << key << " ";
    }
    std::cout << "|";

    if (overflowBucket)
    {
        overflowBucket->print();
    }
}