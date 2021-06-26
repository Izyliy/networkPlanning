#include <iostream>
#include <vector>

class task{
public:
    int duration;                           //Длительность
    std::vector<int> required;              //Зависимости
    std::vector<int> next;                  //Задания, зависимые от данного

    int RN = 0;                                 //Раннее начало
    int RK = 0;                                 //Ранний конец
    int PN = 0;                                 //Позднее начало
    int PK = 999999;                            //Поздний конец
    int PR = 0;                                 //Полный резерв
    int SR = 0;                                 //Свободный резерв

    void RnAndRkCount(std::vector<task> taskList){

        if (required.empty()){
            RN = 0;
        } else {
            RN = taskList[required[0]].RK;
            for (int i=1; i < required.size(); i++){
                if (taskList[required[i]].RK > RN){
                    RN = taskList[required[i]].RK;
                }
            }
        }
        RK = RN + duration;
    }

    void PnAndPkCount(std::vector<task> taskList){


        if(next.empty()) {
            for (int i = 0; i < taskList.size(); i++){
                if (taskList[i].next.empty()){
                    if (taskList[i].RK > RK){
                        PK = taskList[i].RK;
                    } else {
                        PK = RK;
                    }
                }
            }
        } else {
            for (int i = 0; i < next.size(); i++) {
                if (taskList[next[i]].PN < PK) {
                    PK = taskList[next[i]].PN;
                }
            }

        }
        PN = PK - duration;
    }

    void PrAndSrCount(std::vector<task> taskList){
        PR=PN-RN;
        if (PR==0){
            SR = 0;
            return;
        }

        int minRN=999999;

        if (next.empty()){
            SR=PK-RK;
            return;
        }

        for (int i = 0; i < next.size(); i++) {
            if (taskList[next[i]].RN < minRN) {
                minRN = taskList[next[i]].RN;
            }
        }

        SR = minRN - RK;
    }
};

void showAllTasks(std::vector<task> taskList){

    for (int i=0; i < taskList.size(); i++){
        std::cout << std::endl << i << " task:\n";

        std::cout << "Duration: " << taskList[i].duration << std::endl;

        std::cout << "Required: ";
        for (auto req : taskList[i].required){
            std::cout << req << " ";
        }

        std::cout << "\nNext: ";
        for (auto next : taskList[i].next){
            std::cout << next << " ";
        }

        std::cout << "\nRN = " << taskList[i].RN << " and RK = " << taskList[i].RK;

        std::cout << "\nPN = " << taskList[i].PN << " and PK = " << taskList[i].PK;

        std::cout << "\nPR = " << taskList[i].PR << " and SR = " << taskList[i].SR;

        std::cout << std::endl;
    }
}

int main() {

    //Переменные
    std::vector<task> tasks;                //Список всех заданий

    for (int i=0; i < 9; i++){                   //Цикл для автоматического введения задач

        int masDur[9] = {2, 4, 7, 6, 5, 2, 3, 2, 6};

        task newTask;

        newTask.duration = masDur[i];

        tasks.push_back(newTask);
    }
/////////////////////////////////////////////////////////////////////////////
    tasks[2].required.push_back(0);
    tasks[2].required.push_back(1);

    tasks[3].required.push_back(1);

    tasks[4].required.push_back(3);

    tasks[5].required.push_back(1);
    tasks[5].required.push_back(3);

    tasks[6].required.push_back(2);
    tasks[6].required.push_back(4);
    tasks[6].required.push_back(5);

    tasks[7].required.push_back(5);

    tasks[8].required.push_back(4);
    tasks[8].required.push_back(7);
///////////////////////////////////////////////////////////////////////////
    tasks[0].next.push_back(2);

    tasks[1].next.push_back(2);
    tasks[1].next.push_back(3);
    tasks[1].next.push_back(5);

    tasks[2].next.push_back(6);

    tasks[3].next.push_back(4);
    tasks[3].next.push_back(5);

    tasks[4].next.push_back(6);
    tasks[4].next.push_back(8);

    tasks[5].next.push_back(6);
    tasks[5].next.push_back(7);

    tasks[7].next.push_back(8);

    for (int i=0; i < tasks.size(); i++){                             //Подсчет РН и РК
        tasks[i].RnAndRkCount(tasks);
    }

    for (int i=tasks.size()-1; i >= 0; i--){                          //Подсчет ПН и ПК
        tasks[i].PnAndPkCount(tasks);
    }

    for (int i=0; i < tasks.size(); i++){                             //Подсчет ПР и СР
        tasks[i].PrAndSrCount(tasks);
    }

    showAllTasks(tasks);
}
