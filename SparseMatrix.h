#pragma once

#include <string>
#include <vector>
struct SPNode{
    int r,c;
    int v=0;
    SPNode(int m,int n,int v){
        r=m;
        c=n;
        this->v=v;
    };
};
class SparseMatrix {
private:
    int _row=0;
    int _col=0;
    int _num=0;
    /* TODO: Add any necessary data structure here. */
    std::vector<SPNode> data;

public:
    SparseMatrix() = default;
    ~SparseMatrix(){
        data.clear();
    }
    SparseMatrix(const std::string input_file);

    void to_file(const std::string output_file);

    SparseMatrix operator*(SparseMatrix &right);
};
