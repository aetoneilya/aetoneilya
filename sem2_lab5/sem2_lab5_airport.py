class plane:
    def __init__(self, name):
        self.name = name
        self.towns = []
        
    def print_towns(self):
        for town in self.towns:
            print(town,end = ' ')
            
    def haha(self):
        print('haha')

    def add_town(self, town):
        self.towns.append(town)
    
class town:
    def __init__(self, name):
        self.name = name
        self.planes = []

    def print_planes(self):
        for plane in self.planes:
            print(plane,end = ' ')
    
    def add_plane(self,plane):
        self.planes.append(plane)
    

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


planes = []
towns = []

while True:
    line = single_words(input())
    command = line[0]

    if command == "CREATE_PLANE":

        #create new plane object
        planeName = line[1]
        planes.append(plane(planeName))
        last_plane_in = len(planes) - 1
        #add towns for plane
        for planeTown in line[2:]:
            planes[last_plane_in].add_town(planeTown)
            #add plane to town
            townExist = False
            for i in range(0, len(towns)):
                if (towns[i].name == planeTown):
                    towns[i].add_plane(planeName)
                    townExist = True
            if not townExist: 
                towns.append(town(planeTown))
                towns[len(towns) - 1].add_plane(planeName)
        
    elif command == "PLANES_FOR_TOWN":
        townName = line[1]
        for item in towns:
            if item.name == townName:
                print("Planes for " + townName + " are ",end=' ')
                item.print_planes()
                print('')   
    elif command == "TOWNS_FOR_PLANE":
        planeName = line[1]
        for plane in planes:
            if plane.name == planeName:
                print("Towns for " + planeName + " are ",end = '')
                plane.print_towns()
                print('')
                for townName in plane.towns:
                    print("Planes for " + townName + ': ',end = '')
                    for townV in towns:
                        if townName == townV.name:
                            for planeNameTown in townV.planes:
                                if planeNameTown != planeName:
                                    print(planeNameTown)
                    print('')
    elif command == "PLANES":
        for plane in planes:
            print('Plane: ',end = ' ')
            print(plane.name,end = '\t')
            print("Towns :", end = ' ')
            plane.print_towns()
            print('')
    elif command == "EXIT":
        quit()
    

