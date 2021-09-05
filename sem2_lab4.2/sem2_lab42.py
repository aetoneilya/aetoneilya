import random

class number:
    value = 0
    place = 0 
    def __init__(self, value, place):
        self.value = value
        self.place = place
    
def first_digit(number):
    while number > 9:
        number //= 10
    return number

def nums_order(numbers, past_num, num_in_seq, size):
    numAdded = False

    i = 0
    for i in range(0,size):
        if (past_num == -1 or (numbers[i].place == -1 and first_digit(numbers[i].value) == past_num % 10)):
            numbers[i].place = num_in_seq
            nums_order(numbers, numbers[i].value, num_in_seq + 1, size)
            numbers[i].place = -1
            numAdded = True
        
        if (not numAdded and num_in_seq > 2):
            i = 0
            j = 0
            for i in range(0,num_in_seq):
                for j in range(0,size):
                    if numbers[j].place == i:
                        print(numbers[j].value, end = ' ')
            print('')

size = 10
numbers = []

print("Generated nums: ")
i = 0
for i in range(0,size):
    numbers.append(number(random.randint(0, 101),-1))
    print(numbers[i].value, end = " ")

print("")
print("Combinations: ")
nums_order(numbers, -1, 0, size)