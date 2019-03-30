#include "Bucket.hpp"

Bucket::Bucket() {}

void Bucket::add_left_rel_page(unsigned int page_id) {
    this->left_rel.push_back(page_id);
}

void Bucket::add_right_rel_page(unsigned int page_id) {
    this->right_rel.push_back(page_id);
}

vector<unsigned int> Bucket::get_left_rel() {
    return this->left_rel;
}

vector<unsigned int> Bucket::get_right_rel() {
    return this->right_rel;
}