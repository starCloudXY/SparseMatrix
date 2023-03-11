
#include "SparseMatrix.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;
#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(const std::string input_file) {
    /* TODO: Your code here. */
    ifstream infile(input_file);

    infile>>_row>>_col;
    int r,c,n;
    while(infile>>r>>c>>n){
        data.emplace_back(r,c,n);
        _num++;
    }
    infile.close();
}


void SparseMatrix::to_file(const std::string output_file) {
    /* TODO: Your code here. */
    ofstream outfile(output_file);
    outfile<<_row<<" "<<_col<<endl;
    for (auto & iter : data)
    {
        outfile<< iter.r<< " "<< iter.c<<" "<<iter.v<< endl;

    }
    outfile.close();
    return;
}

SparseMatrix SparseMatrix::operator*( SparseMatrix &right) {
    SparseMatrix result;
    if(_col!=right._row)throw domain_error("wrong size.");
    result._row = _row;
    result._col = right._col;
    vector<SPNode>*help=new vector<SPNode>[right._col];
    for (auto & iter : right.data)
    {
        help[iter.c].push_back(iter);
    }

    /* TODO: Your code here. */
    if(_num!=0&&right._num!=0){
        for(int i = 0;i < _num;i++){
            int tmp=data[i].r;
            int j=i;
            while(j<_num&&data[j].r==tmp)j++;
            for(int k=0;k<right._col;k++){
                int mul=0;
                int h=i;
                for (auto & iter : help[k])
                {
                    while (h<j){
                        if(iter.r==data[h].c){
                            mul+=data[h].v*iter.v;
                            h++;
                            continue;}
                        if(iter.r>data[h].c)h++;
                        else break;
                    }
                }
                if(mul){
                    result.data.emplace_back(tmp,k,mul);
                }
            }
            i=j-1;
        }
    }
    for(int i=0;i<right._col;i++)help[i].clear();
    delete []help;
    return result;
}
