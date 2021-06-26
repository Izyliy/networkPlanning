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
    int buff;

    std::cout << "Begin typing task info (to stop, enter \"0\" when asked to type next task duration):\n";

    for (int i=0; ; i++){                   //Цикл для задач

        task newTask;
        std::cout << "\nTask #" << i << " info:\n";
        std::cout << "Duration:\n";
        std::cin >> buff;

        if (buff<1 && i==0){
            return 0;                       //При введении 0 на первом элементе, программа прекращает работу
        } else if (buff<1){
            break;                          //Выход из цикла
        }

        newTask.duration=buff;

        std::cout << "Type ID of required tasks one by one (to stop, enter \"-1\"):\n";
        for (int j=0; ; j++){               //Цикл для введения зависимостей от задач

            std::cin >> buff;

            if (buff<0){
                buff = 999999;              //Для того, чтобы при начале введения следующей задачи buff было больше нуля
                                            //В случае, если 999999 - реальное число, которое вохможно встретить при
                                            //введении данного поля можно изменить условия выхода из цикла или создать
                                            //отдельный буфер для данных вводов
                break;                      //Выход из цикла
            } else if (buff>=i){
                std::cout << "ID of required task must be less than ID of a current task!\n";
                //Номер родительской задачи должен быть меньше тк сортировка по рангам проводиться не будет

                continue;
            }

            newTask.required.push_back(buff);               //При необходимости добавить проверку на содержание
            tasks[buff].next.push_back(tasks.size());

        }

        tasks.push_back(newTask);
    }

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
