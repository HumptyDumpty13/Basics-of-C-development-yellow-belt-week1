#include <iostream>
#include<vector>
#include<map>
#include <exception>
#include <string>
#include<tuple>
#include<ctime>


// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса


class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
        return workers.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const std::string& person) {
        ++workers[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const std::string& person, int task_count) {
        if (workers.count(person)) {
        int counter = 0;
        for (const auto& it : workers)
        {
            if (it.first == person) {
                for (const auto& x : it.second) {
                    if (x.first != TaskStatus::DONE) { counter += x.second; }
                }
            }
        }
        if (task_count > counter) { task_count = counter; }
        int in_prog = 0, test = 0, done = 0;
        TasksInfo t = workers[person]; 
        TasksInfo tmp;
            for (int i = 0; i < task_count; ++i) {
                if (workers[person][TaskStatus::NEW] > 0) {
                    --workers[person][TaskStatus::NEW];
                    ++tmp[TaskStatus::IN_PROGRESS];
                    ++in_prog;
                }
                else if (workers[person][TaskStatus::IN_PROGRESS] > 0) {
                    --workers[person][TaskStatus::IN_PROGRESS];
                    ++tmp[TaskStatus::TESTING];
                    ++test;
                }
                else if (workers[person][TaskStatus::TESTING] > 0) {
                    --workers[person][TaskStatus::TESTING];
                    ++tmp[TaskStatus::DONE];
                    ++done;
                }
            }
 
      
            int i = 0;
            /*for (const auto it : t) {
                if (it.first == TaskStatus::NEW) {
                    std::cout << 0 << " " << it.second << std::endl;
                }
                else if (it.first == TaskStatus::IN_PROGRESS) {
                    std::cout << 1 << " " << it.second << std::endl;
                }
                else if (it.first == TaskStatus::TESTING) {
                    std::cout << 2 << " " << it.second << std::endl;
                }
                else if (it.first == TaskStatus::DONE) {
                    std::cout << 3 << " " << it.second << std::endl;
                }
            }*/
            t[TaskStatus::NEW]-=in_prog;
            t[TaskStatus::IN_PROGRESS]-= test;
            t[TaskStatus::TESTING]-= done;
	    t.erase(TaskStatus::DONE);
            workers[person][TaskStatus::IN_PROGRESS] += tmp[TaskStatus::IN_PROGRESS];
            workers[person][TaskStatus::TESTING] += tmp[TaskStatus::TESTING];
            workers[person][TaskStatus::DONE] += tmp[TaskStatus::DONE];
            for (auto it = t.begin(); it != t.end();) {
                if (it->second == 0) {
                    it = t.erase(it);
                }
                else {
                    it++;
                }
            }
            for (auto it = tmp.begin(); it != tmp.end();) {
                if (it->second == 0) {
                    it = tmp.erase(it);
                }
                else {
                    it++;
                }
            }
 for (auto it = workers[person].begin(); it != workers[person].end();) {
                if (it->second == 0) {
                    it = workers[person].erase(it);
                }
                else {
                    it++;
                }
            }
            int y = 0;
            //std::cout << "---------------------------" << std::endl;
            /*for (const auto it : t) {
                std::cout << y << " " << it.second << std::endl;
                ++y;
            }*/
            std::tuple<TasksInfo, TasksInfo> result = std::tie(tmp, t);
            return result;
        }
        else {
            std::tuple<TasksInfo, TasksInfo> result;
            return result;
        }

    }
private:
    TasksInfo tasks;
    std::string person_;
    std::map<std::string, TasksInfo> workers;
    //std::map<TasksInfo, std::string> m;
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    std::cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    std::cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}