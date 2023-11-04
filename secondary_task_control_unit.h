#pragma once

#ifndef SECONDARY_TASK_COMTROL_UNIT
#define SECONDARY_TASK_COMTROL_UNIT

/*
Абстрактный класс для реализации групп классов
для создания дополнительных задач.
*/

class SecondaryTaskControlUnit {
 public:
	 virtual void completingTask() = 0;
	 virtual ~SecondaryTaskControlUnit() {}
};

#endif //SECONDARY_TASK_COMTROL_UNIT

