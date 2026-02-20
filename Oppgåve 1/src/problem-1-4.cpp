#include "defines.h" 
#include "book-index.h"



void start_chapter(litindex::BookIndex b)
{
    std::cout << "start_chapter(litindex::BookIndex b)\n";

    b.next_chapter();
    b.out();  // print status
}


int main(int /*argc*/, char** /*argv*/) 
{
    std::ifstream i_file("bookindex.txt");
    if (!i_file) return 1;


    int count;
    i_file >> count;

    litindex::BookIndex index_list[count];

    for (int i = 0; i < count; ++i) {
        int arr[3];
        i_file >> arr[0] >> arr[1] >> arr[2];

        litindex::BookIndex idx(arr[0], arr[1], arr[2]);

        index_list[count] = idx;
        index_list[count].out();
    }

    i_file.close();


    std::cout << "\nBookIndex example:\n";
    litindex::BookIndex idx(1, 11, 24);
    
    // litindex::BookIndex* address = &idx;
    
    idx.out();  // print status
    start_chapter(idx);
    idx.out();  // print status

}