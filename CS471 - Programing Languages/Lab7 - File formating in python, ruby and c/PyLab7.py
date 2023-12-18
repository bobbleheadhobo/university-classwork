import csv

# Name: Joey Troyer
# Date: 10/20/22
# input: file "ConvertCSVinput.txt"
# output: write to a file to formatted output from the input file
# problem: Read in a txt with each word seperated by a coma and format it and write it to a different file

with open('ConvertCSVinput.txt') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    out = []
    a = ".jpg"
    for row in csv_reader:

        #check for no middle name
        #if none move row[1] to row[2] and make row[1] empty
        if any(a in word for word in row[:2]):
            row.append(row[1])
            row[1] = ""

        #check if row[1] is empty or not
        if(row[1]):
            out.append(f"{row[0]},{row[1]},{row[2]} ; {row[0].capitalize()} ; {row[1].capitalize()} ; {row[2].removesuffix('.jpg').capitalize()} ;")
        else:
            out.append(f"{row[0]},{row[2]} ; {row[0].capitalize()} ; {row[2].removesuffix('.jpg').capitalize()} ;")

csv_file.close()

#write ti file formated output
with open('output.txt','w') as output:
    for item in out: 
        output.write(f"{item}\n")

output.close()
    
