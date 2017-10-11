#include <iostream>
#include <string>
#include <functional>
using namespace std;

class ListException {
public:
    string what;
    ListException(string s) {
        this->what = s + "\n";
    }
};

template <class T>
struct SingleList {
    SingleList *rear = nullptr;
    T data;
    
    void insert(int index, T data) {
        SingleList *slideWindow = this;
        for (int p = 0; p < index; ++p) {
            if (slideWindow->rear == nullptr) {
                SingleList *node = new SingleList;
                node->rear = slideWindow->rear;
                slideWindow->rear = node;
            }
            slideWindow = slideWindow->rear;
        }
        
        if (this->isObjAtIndex(index)) {
            slideWindow->data = data;
        } else {
            SingleList *node = new SingleList;
            node->data = data;
            node->rear = slideWindow->rear;
            slideWindow->rear = node;
        }
    }
    
    T& operator[](int i) {
        SingleList *slideWindow = this;
        for (int p = 0; p < i; ++p) {
            slideWindow = slideWindow->rear;
            if (slideWindow == nullptr) {
                throw ListException("index over range");
            }
        }
        return slideWindow->data;
    }
    void remove(int index) {
        SingleList *slideWindow = this;
        SingleList *frontSlideWindow = nullptr;
        SingleList *rearSlideWindows = slideWindow->rear;
        for (int p = 0; p < index; ++p) {
            if (slideWindow->rear == nullptr) {
                throw ListException("index over range");
            }
            frontSlideWindow = slideWindow;
            slideWindow = slideWindow->rear;
            rearSlideWindows = slideWindow->rear;
        }
        
        if (frontSlideWindow == nullptr) {
            this->rear = rearSlideWindows;
            slideWindow->rear = nullptr;
            delete slideWindow;
        } else if (rearSlideWindows == nullptr) {
            frontSlideWindow->rear = nullptr;
            delete slideWindow;
        } else {
            frontSlideWindow->rear = rearSlideWindows;
            slideWindow->rear = nullptr;
            delete slideWindow;
        }
        
    }
    
    void empty() {
        delete this->rear;
        this->rear = nullptr;
    }
    bool isObjAtIndex(int index) {
        SingleList *slideWindow = this;
        for (int p = 0; p < index; ++p) {
            if (slideWindow == nullptr) {
                return false;
            }
            slideWindow = slideWindow->rear;
        }
        return true;
    }
    
    int size() {
        SingleList *slideWindow = this;
        int p = 0;
        for (; ; ++p) {
            slideWindow = slideWindow->rear;
            if (slideWindow == nullptr) break;
        }
        return p + 1;
    }
    
    void enumObjWithLamda(function<void(T data)> func) {
        auto size = this->size();
        SingleList *slideWindow = this;
        for (int p = 0; p < size; ++p) {
            func(slideWindow->data);
            slideWindow = slideWindow->rear;
            if (slideWindow == nullptr) return;
        }
    }
    
    
    ~SingleList() {
        if (this->rear != nullptr) {
            delete this->rear;
        }
        cout<<"release"<<this->data<<endl;
    }
};

int main(int argc, char* argv[]) {
    
    auto list = new SingleList<int>;
    for (int i = 0; i < 100; ++i) {
        list->insert(i, i * 2);
    }
    int pp = 0;
    list->enumObjWithLamda([&](int data){
        
        cout<<pp++<<": "<<data<<endl;
    });
    
    list->remove(4);
    auto d = (*list)[4];
    cout<<"use operator: "<<d<<endl;
    list->empty();
    list->enumObjWithLamda([&](int data){
        
        cout<<pp++<<": "<<data<<endl;
    });
    
    delete list;
    while (1);
    return 0;
}
