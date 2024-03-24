uint32_t globalCount = 0;

bool globalBool = false;

TaskManager testTaskManager = TaskManager();

void setupTest()
{
    FuncTask *countFunc = new FuncTask([](FuncTask *task)
                                  {

    Serial.print("Task State: ");
    Task::State newState = task->getState();

    task->count = task->count + 1;

    if (task->count >= 5) {
        globalCount = globalCount + 1;
        newState = Task::State::done;
    }else {
        newState = Task::State::running;
    }

    switch (newState) {
      case FuncTask::State::none:
        Serial.println("NONE");
        break;
      case FuncTask::State::running:
        Serial.println("RUNNING");
        break;
      case FuncTask::State::done:
        Serial.println("DONE");
        task->count = 0;
        break;
    }
    return newState; });

    FuncTask *globalBoolFunc1 = new FuncTask([](FuncTask *task)
                                   {
        Serial.print("globalBool is: ");
        Serial.println(globalBool == true ? "-----------------true-----" : "-----------------false-----");
    
    return Task::State::done; });

    testTaskManager.addTask(globalBoolFunc1);
    testTaskManager.addTask(new WaitTask(1));

    testTaskManager.addTask(new ChangeBoolTask(&globalBool, true));

    FuncTask *globalBoolFunc2 = new FuncTask([](FuncTask *task)
                                   {
        Serial.print("globalBool is: ");
        Serial.println(globalBool == true ? "-----------------true-----" : "-----------------false-----");
    
    return Task::State::done; });

    testTaskManager.addTask(globalBoolFunc2);
    testTaskManager.addTask(new WaitTask(1));

    testTaskManager.addTask(new ChangeBoolTask(&globalBool, false));
}