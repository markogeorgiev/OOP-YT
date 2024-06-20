#include <iostream>
#include <cstring>

#define MAX_DESC_SIZE 201

using namespace std;

class Project {
private:
    char *clientName;
    char projectDesc[MAX_DESC_SIZE];
    int daysDue;
    float ratingOfClient;
public:
    Project(const char *clientName, const char *projectDesc, const int daysDue, const float ratingOfClient)
            : clientName(new char[strlen(clientName) + 1]), daysDue(daysDue), ratingOfClient(ratingOfClient) {
        strcpy(this->clientName, clientName);
        strcpy(this->projectDesc, projectDesc);
    }

    virtual float getTotalProfit() {
        return -3333333.0;
    }

    virtual void showProjectInfo() {
        printf(" project from %s (%.2f), is due in %d.\n"
               " Description: %s\n"
               " Due to be paid: ", clientName, ratingOfClient ,daysDue, projectDesc);
    }
};

class FixedPriceProject : public Project {
private:
    float fixedPrice;
public:
    FixedPriceProject(const char *clientName, const char *projectDesc, const int daysDue, const float ratingOfClient, const float fixedPrice)
            : Project(clientName, projectDesc, daysDue, ratingOfClient), fixedPrice(fixedPrice) {
    }

    float getTotalProfit() override {
        return fixedPrice;
    }

    void showProjectInfo() override{
        cout << "Fixed price";
        Project::showProjectInfo();
        cout << getTotalProfit() << endl << endl;
    }
};


class HourlyProject : public Project{
private:
    int hoursWorked;
    float hourlyRate;
public:
    HourlyProject(const char *clientName, const char *projectDesc, const int daysDue, const float ratingOfClient, const int hoursWorked,
                  float hourlyRate) : Project(clientName, projectDesc, daysDue, ratingOfClient),
                                      hoursWorked(hoursWorked), hourlyRate(hourlyRate) {
    }

    float getTotalProfit() override {
        return (float) hoursWorked * hourlyRate;
    }

    void showProjectInfo() override{
        cout << "Hourly rate";
        Project::showProjectInfo();
        cout << getTotalProfit() << endl << endl;
    }
};


int main() {
    /** Задача:
     *     Дефинирајте класа што ќе опишува проекти. Има два типа на проекти,
     *     FixedPriceProject и HourlyProject. Двете ги делат следниве карактеристики:
     *         - Име на клиентот: динамички алоцирана низа од карактери.
     *         - Опис на работата: низа од max 200 каратери.
     *         - Број на денови за да се заврши: int
     *         - Рејтинг на клиентот (1.0 - 5.0): float
     *     Дополнително класите ги имаат следниве истоимени методи:
     *         - getTotalProfit():float Го враќа целиот профит, за FixedPriceProject е
     *         цена договорена однапред, а за HourlyProject е однпаред договорената
     *         плата по час * бројот на часови сработени.
     *         - showProjectInfo(): Ги печат информациите за проектот во следниот формат:
     *         За FixedPriceProject(i) и за HourlyProject(ii):
     *
     *         FORMAT i:  Fixed price project from [clientName] (clientRating), is due in [numDays].
     *                    Description:[projectDescription]
     *                    Due to be paid: [getTotalProfit()]
     *
     *         FORMAT ii: Hourly rate project from [clientName] (clientRating), is due in [numDays].
     *                    Description:[projectDescription]
     *                    Due to be paid: [getTotalProfit()]
     * */

    Project* *projects = new Project *[6];
    projects[0] = new FixedPriceProject("Gilbert",
                                        "I need you to teach people why inheritance is the best",
                                        7, 5.0, 1000);

    projects[1] = new HourlyProject("Diana",
                                    "I need help with Java, what is a lambda???",
                                    1, 4.1, 5, 7);

    projects[2] = new FixedPriceProject("Avery",
                                        "Develop a course on the importance of encapsulation",
                                        10, 3.7, 1200);

    projects[3] = new HourlyProject("James",
                                    "Explain polymorphism in C++ with examples",
                                    2, 1.5, 6, 4.3);

    projects[4] = new FixedPriceProject("Morgan",
                                        "Create a workshop on design patterns in software engineering",
                                        5, 2.9, 1500);

    projects[5] = new HourlyProject("Taylor",
                                    "Guide on setting up a continuous integration pipeline",
                                    3, 3.8, 1, 15);

    for (int i = 0; i < 6; ++i) {
        projects[i]->showProjectInfo();
    }

    for (int i = 0; i < 6; i++) delete projects[i];
    delete[] projects;
}


