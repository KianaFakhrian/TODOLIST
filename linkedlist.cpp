#include "linkedlist.h"
#include "task.h"
linkedList::linkedList()
{

}

void linkedList::pushFront(Task task)
{
    Task* New_Task = new Task ;
    New_Task->set_task_info(task);
    New_Task->next = head ;
    head = New_Task ;
}
void linkedList::init()
{
    head = nullptr ;
}
