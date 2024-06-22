#include <iostream>
#include <cstring>

#define MAX_DEX_SIZE 300

using namespace std;

class Content {
protected:
    char *title;
    char description[MAX_DEX_SIZE];

    void copy(const Content &r) {
        delete [] title;
        title = new char[strlen(r.title) + 1];
        strcpy(title, r.title);
        strcpy(description, r.description);
    }

public:
    Content(const char *title = "NO_TITLE_YET", const char *description = "NO_DESC")
            : title(new char[strlen(title) + 1]) {
        strcpy(this->title, title);
        strcpy(this->description, description);
    }

    ~Content() {
        delete[]title;
    }

    Content(const Content &other) {
        title = nullptr;
        copy(other);
    }

    Content &operator=(const Content &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    char *getTitle() const {
        return title;
    }

    const char *getDescription() const {
        return description;
    }

    virtual void print(ostream &os) const {
        os << "Title: " << title << ", Description: " << description;
    }

    friend bool operator==(const Content &o1, const Content &o2) {
        return strcmp(o1.getTitle(), o2.getTitle()) == 0 && strcmp(o1.getDescription(), o2.getDescription()) == 0;
    }

};

class ShortFormContent : public Content {
private:
    char *category;
public:
    ShortFormContent(const char *title = "NO_TITLE_YET", const char *description = "NO_DESC",
                     const char *category = "NO_CATEGORY")
            : Content(title, description), category(new char[strlen(category) + 1]) {
        strcpy(this->category, category);
    }

    ShortFormContent(const ShortFormContent &other) :
            Content(other), category(new char[strlen(other.category) + 1]) {
        strcpy(category, other.category);
    }

    ShortFormContent &operator=(const ShortFormContent &other) {
        if (this != &other) {
            Content::operator=(other);
            delete[]category;
            category = new char[strlen(other.category) + 1];
            strcpy(category, other.category);
        }
        return *this;
    }

    char *getCategory() const {
        return category;
    }

    ~ShortFormContent() {
        delete[]category;
    }

    void print(ostream &os) const override {
        Content::print(os);
        os << ", Category: " << category << endl;
    }

};

class LongFormContent : public Content {
private:
    int lengthInMinutes;
    char *playlist;

    void copy(const LongFormContent &r) {
        delete [] playlist;
        lengthInMinutes = r.lengthInMinutes;
        playlist = new char[strlen(r.playlist) + 1];
        strcpy(playlist, r.playlist);
    }

public:
    LongFormContent(const char *title = "NO_TITLE_YET", const char *description = "NO_DESC",
                    const int lengthInMinutes = -1, const char *playlist = "NO_PLAYLIST") :
            Content(title, description), lengthInMinutes(lengthInMinutes), playlist(new char[strlen(playlist) + 1]) {
        strcpy(this->playlist, playlist);
    }

    ~LongFormContent() {
        delete[] playlist;
    }

    LongFormContent(const LongFormContent &other)
            : Content(other), playlist(new char[strlen(other.playlist) + 1]), lengthInMinutes(other.lengthInMinutes) {
        strcpy(this->playlist, other.playlist);
    }

    LongFormContent &operator=(const LongFormContent &other) {
        if (this != &other) {
            Content::operator=(other);
            copy(other);
        }
        return *this;
    }

    int getLengthInMinutes() const {
        return lengthInMinutes;
    }

    void print(ostream &os) const override {
        Content::print(os);
        os << ", Length in minutes: " << lengthInMinutes << ", Playlist: " << playlist << endl;
    }
};

ostream &operator<<(ostream &os, const Content &obj) {
    obj.print(os);
    return os;
}


#define MAX_CHANNEL_NAME 30
#define MAX_IN_COLLECTION 30

class Channel {
private:
    char channelName[MAX_CHANNEL_NAME] = "INITIAL_NAME_NEEDED";
    Content* *contentCollection = nullptr;
    int numInCollection = 0;
    void copy(const Channel &other){
        for (int i = 0; i < numInCollection; ++i) {
            delete contentCollection[i];
        }
        delete[] contentCollection;
        numInCollection = other.numInCollection;
        contentCollection = new Content*[other.numInCollection];
        for (int i = 0; i < numInCollection; ++i) {
            ShortFormContent* check = dynamic_cast<ShortFormContent*>(other.contentCollection[i]);
            if (check != nullptr){
                contentCollection[i]= new ShortFormContent(*check);
            } else{
                LongFormContent* check2 = dynamic_cast<LongFormContent*>(other.contentCollection[i]);
                contentCollection[i] = new LongFormContent(*check2);
            }

        }
        strcpy(channelName, other.channelName);
    }
public:
    Channel(const char *channelName = "NO_NAME") {
        strcpy(this->channelName, channelName);
        numInCollection = 0;
        contentCollection = nullptr;
    }

    Channel(const Channel &other){
        copy(other);
    }

    Channel& operator = (const Channel &other){
        if (this != &other){
            copy(other);
        }
        return *this;
    }

    ~Channel() {
        for (int i = 0; i < numInCollection; ++i) {
            delete contentCollection[i];
        }
        delete[] contentCollection;
    }

    Channel& operator +=(Content &toAdd) {
        auto *temp = new Content*[numInCollection + 1];
        for (int i = 0; i < numInCollection; ++i) {
            temp[i] = contentCollection[i];
        }
        ShortFormContent* check = dynamic_cast<ShortFormContent*>(&toAdd);

        if (check){
            temp[numInCollection++] = new ShortFormContent(*check);
        } else{
            LongFormContent * check2 = dynamic_cast<LongFormContent*>(&toAdd);
            temp[numInCollection++] = new LongFormContent(*check2);
        }
        delete [] contentCollection;
        contentCollection = temp;
        return *this;
    }

    const char *getChannelName() const {
        return channelName;
    }

    const Content &operator[](int index) const {
        if (index < 0 || index >= numInCollection) {
            throw out_of_range("Index out of range");
        }
        return *contentCollection[index];
    }

    friend ostream &operator<<(ostream &os, const Channel &obj) {
        os << "List of content by " << obj.getChannelName() << endl;
        for (int i = 0; i < obj.numInCollection; ++i) {
            os << obj[i];
        }
        return os;
    }
};


int main() {

    /* Задача: Имаме задача да искористиме се што учевме до сега
     *  за да имплементираме CMS (Content Management System).
     *  Треба да се имплементира функционалност за еден Channel.
     *  Каналот може чува низа од максимум 30 елементи, име и бројот
     *  на содржини кои ги има.
     *  -
     *  Има два типа на содржини (Content). Во продолжение описи за
     *  класите:
     *  ShortFormContent:
     *      - title: динамички алоцирана низа од карактери
     *      - description: низа од 300 карактери
     *      - category: динамички алоцирана низа од карактери
     *  LongFormContent:
     *      - title: динамички алоцирана низа од карактери
     *      - description: низа од 300 карактери
     *      - lenghtInMinutes:int
     *      - playlist: динамички алоцирана низа од карактери
     *  За секоја од класите да се дефинираат конструктор, деструктор,
     *  copy-конструктор и преоптоварување на = оператор.
     *  -
     *  Дополнително да се преоптовари << операторот за сите класи, а
     *  за класите на содржини да се преоптовари == операторот (две
     *  класи се еднакви акко имаат ист title и description.
     *  -
     *  Да се преоптовари операторот за += на класата Channel т.ш.
     *  ќе може да се додавам нов содржини користејќи го него.
     *  -
     *  Форматот за печатење треба да изгледа вака:
     *
     *  FORMAT - ShortFormContent: Title: [title], Description: [description], Category: [category]\n
     *
     *  FORMAT - LongFormContent: Title: [title], Description: [description], Length in minutes: [lengthInMinutes], Playlist: [playlist]\n
     *
     *  FORMAT - Channel: List of content by [channelName]\n: [every piece of content on the Channel]
     *  */

    int test = 0;

    while (test < 7){
        if (test == 1) {
            cout << test << endl;
            cout << "=======Testing constructors w and w/o arguments=======" << endl;

            ShortFormContent sfc1;
            LongFormContent lfc1;
            Channel channel1;

            ShortFormContent sfc2("YTShort1", "Desc1", "Comedy");
            LongFormContent lfc2("YTVideo1", "Desc2", 10, "OOP in C++");
            Channel channel2("Marko Georgiev");


            cout << "WORKING FINE" << endl;
        }
        else if (test == 2) {
            cout << test << endl;
            cout << "=======Testing COPY constructor and = operator=======" << endl;

            ShortFormContent sfc1("YTShort1", "Desc1", "Comedy");
            LongFormContent lfc1("YTVideo1", "Desc2", 10, "OOP in C++");
            Channel channel1("Marko Georgiev");

            ShortFormContent sfc2 = sfc1;
            LongFormContent lfc2 = lfc1;
            Channel channel2 = channel1;

            if (strcmp(sfc1.getTitle(), sfc2.getTitle()) != 0 || strcmp(sfc1.getCategory(), sfc2.getCategory()) != 0) {
                throw runtime_error("ShortFormContent = is not working");
            }

            if (strcmp(lfc1.getTitle(), lfc2.getTitle()) != 0 || lfc1.getLengthInMinutes() != lfc2.getLengthInMinutes()) {
                throw runtime_error("LongFormContent = is not working");
            }

            if (strcmp(channel1.getChannelName(), channel2.getChannelName()) != 0) {
                throw runtime_error("Channel = is not working");
            }

            ShortFormContent sfc3(sfc1);
            LongFormContent lfc3(lfc1);
            Channel channel3(channel1);

            if (strcmp(sfc1.getTitle(), sfc3.getTitle()) != 0 || strcmp(sfc1.getCategory(), sfc3.getCategory()) != 0) {
                throw runtime_error("ShortFormContent = is not working");
            }

            if (strcmp(lfc1.getTitle(), lfc3.getTitle()) != 0 || lfc1.getLengthInMinutes() != lfc3.getLengthInMinutes()) {
                throw runtime_error("LongFormContent = is not working");
            }

            if (strcmp(channel1.getChannelName(), channel3.getChannelName()) != 0) {
                throw runtime_error("Channel = is not working");
            }

            cout << "WORKING FINE" << endl;
        }
        else if (test == 3) {
            cout << test << endl;
            cout << "=======Testing << operator for all classes=======" << endl;

            ShortFormContent sfc1("YTShort1", "Desc1", "Comedy");
            LongFormContent lfc1("YTVideo1", "Desc2", 10, "OOP in C++");
            Channel channel1("Marko Georgiev");

            cout << sfc1;
            cout << lfc1;
            cout << channel1;

            cout << "WORKING FINE" << endl;
        }
        else if (test == 4) {
            cout << test << endl;
            cout << "=======Testing Channel += operator =======" << endl;

            Channel channel1("Marko Georgiev");

            LongFormContent lfc1("What is static casting in C++",
                                 "For some reasons two pieces of content have the same description", 10, "C++ Tutorials");
            LongFormContent lfc2("Static casting in C++",
                                 "This is video is not the same as \"What is static casting in C++\", it's better", 10,
                                 "Better C++ Playlist");
            LongFormContent lfc3("Understanding Polymorphism in C++",
                                 "A deep dive into polymorphic behavior in object-oriented programming", 15,
                                 "C++ Tutorials");

            ShortFormContent sfc1("What is static casting in C++",
                                  "For some reasons two pieces of content have the same description", "Educational");
            ShortFormContent sfc2("Should you program games in C++?",
                                  "C++ is known for being the go-to place for game devs", "Entertainment");
            ShortFormContent sfc3("Understanding Memory Management in C++",
                                  "A guide to memory in C++ effectively", "Technical");

            channel1 += lfc1;
            channel1 += lfc2;
            channel1 += lfc3;
            channel1 += sfc1;
            channel1 += sfc2;
            channel1 += sfc3;

            cout << channel1 << endl;

            cout << "WORKING FINE" << endl;
        }
        else if (test == 5) {
            cout << test << endl;
            cout << "=======Testing == operator =======" << endl;

            LongFormContent lfc1("What is static casting in C++",
                                 "For some reasons two pieces of content have the same description", 10, "C++ Tutorials");
            ShortFormContent sfc1("What is static casting in C++",
                                  "For some reasons two pieces of content have the same description", "Educational");
            LongFormContent lfc2("Static casting in C++",
                                 "This is video is not the same as \"What is static casting in C++\", it's better", 10,
                                 "Better C++ Playlist");


            if (lfc1 == sfc1) {
                cout << "== works fine for lfc1 == sfc1" << endl;
            } else {
                throw runtime_error("== operator is not working 1");
            }

            if (!(lfc2 == sfc1)) {
                cout << "== works fine for lfc2 == sfc1" << endl;
            } else {
                throw runtime_error("== operator is not working 2");
            }

            if (!(lfc1 == lfc2)) {
                cout << "== works fine for lfc1 == lfc2" << endl;
            } else {
                throw runtime_error("== operator is not working 3");
            }
            cout << "WORKING FINE" << endl;
        }
        else if (test == 6) {
            cout << test << endl;
            cout << "=======Testing everything accept == operator =======" << endl;

            Channel channel1("Marko Georgiev");

            LongFormContent lfc1("What is static casting in C++",
                                 "For some reasons two pieces of content have the same description", 10, "C++ Tutorials");
            LongFormContent lfc2("Static casting in C++",
                                 "This is video is not the same as \"What is static casting in C++\", it's better", 10,
                                 "Better C++ Playlist");
            LongFormContent lfc3("Understanding Polymorphism in C++",
                                 "A deep dive into polymorphic behavior in object-oriented programming", 15,
                                 "C++ Tutorials");

            ShortFormContent sfc1("What is static casting in C++",
                                  "For some reasons two pieces of content have the same description", "Educational");
            ShortFormContent sfc2("Should you program games in C++?",
                                  "C++ is known for being the go-to place for game devs", "Entertainment");
            ShortFormContent sfc3("Understanding Memory Management in C++",
                                  "A guide to memory in C++ effectively", "Technical");

            channel1 += lfc1;
            channel1 += lfc2;
            channel1 += lfc3;
            channel1 += sfc1;
            channel1 += sfc2;
            channel1 += sfc3;

            Channel channel2 = channel1;
            Channel channel3(channel1);

            cout << "channel2:\n";
            cout << channel2;

            cout << "channel3:\n";
            cout << channel3;

            cout << "WORKING FINE" << endl;
        }
        test++;
    }

}


