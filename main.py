tasks = []

while True:
    print("\n1. Добавить задачу")
    print("2. Показать задачи")
    print("3. Выйти")
    print("4. Очистить все задачи")
    print("5 удалить по номеру задачи")

    choice = input("Выбери действие: ")

    if choice == "1":
        task = input("Введите задачу: ")
        tasks.append(task)
        print("Задача добавлена!")

    elif choice == "2":
        if not tasks:
            print("Задач пока нет")
        else:
            for i, task in enumerate(tasks, 1):
                print(f"{i}. {task}")

    elif choice == "3":
        print("Пока 👋")
        break
    
    elif choice == "4":
        tasks.clear()
        print("Все задачи удалены")
    
    elif choice == "5":
        for i, task in enumerate(tasks,1):
            print (f"{i}. {task}")

        

    else:
        print("Неверный выбор")
