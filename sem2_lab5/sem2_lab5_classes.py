class class_:
    def __init__(self, name, date):
        self.name = name
        self.currentDate = date
        self.globalDate = date

    def new_current_date(self, new_date):
        self.currentDate = new_date

def single_words(sentence):
    word_vector = []
    result_word = ''
    sentence += ' '
    for char  in sentence:
        if char == ' ' and len(result_word) != 0:
            word_vector.append(result_word)
            result_word = ''
        elif char != ' ':
            result_word += char
    return word_vector

classes = []
month = 0
monthDays = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

while True:
    line = single_words(input())
    command = line[0]

    if command == "CLASS":
        date = int(line[1])
        name = line[2]
        classes.append(class_(name, date))

    elif command == "NEXT":
        month = (month + 1) % 12
        print("Next month number is " + str(month + 1),end = ' ')
        print("it has " + str(monthDays[month]) + " in it")
        i = 0 
        for i in range(len(classes)):
            if classes[i].globalDate > monthDays[month]:
                classes[i].new_current_date(monthDays[month] - 1)

    elif command == "VIEW":
        viewDate = int(line[1])
        classNames = []
        for oneClass in classes:
            if oneClass.currentDate == viewDate:
                classNames.append(oneClass.name)
    
        print("In " + str(viewDate) + " day " + str(len(classNames)),end = ' ')
        print("classes in univercity ", end = ' ')
        for one_class in classNames:
            print(one_class,end=' ')
        print('')

    elif command == "EXIT":
        quit()
    